#!/usr/bin/env python3

import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from wheel_robot_teleop.UltrasonicSense import UltrasonicSense

import RPi.GPIO as GPIO
GPIO.setwarnings(False)


TRIG = 17
ECHO = 18

#set GPIO direction (IN / OUT)


def distance():
    # set Trigger to HIGH
    GPIO.output(TRIG, True)
 
    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(TRIG, False)
 
    StartTime = time.time()
    StopTime = time.time()
 
    # save StartTime
    while GPIO.input(ECHO) == 0:
        StartTime = time.time()
 
    # save time of arrival
    while GPIO.input(ECHO) == 1:
        StopTime = time.time()
 
    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = round((TimeElapsed * 34300) / 2,2)
 
    return distance


def main(args=None):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(TRIG, GPIO.OUT)
    GPIO.setup(ECHO, GPIO.IN)
    
    rclpy.init(args=args)
    mobot_ultrasonic = UltrasonicSense()

    message=Float32()

    try:
        while True:
            message.data = distance()
            print ("Measured Distance = %.1f cm" % message.data)
            #time.sleep(1)
 
            mobot_ultrasonic.publisher_.publish(message)
            time.sleep(0.2)

        # Reset by pressing CTRL + C
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        GPIO.cleanup()

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    mobot_ultrasonic.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()