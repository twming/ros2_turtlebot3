#!/usr/bin/env python3

import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from btwheelrobot.UltrasonicSenseClass import UltrasonicSenseClass
import btwheelrobot.Common as gPin
import RPi.GPIO as GPIO
GPIO.setwarnings(False)


def distance():
    # set Trigger to HIGH
    GPIO.output(gPin.TRIG, True)
 
    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(gPin.TRIG, False)
 
    StartTime = time.time()
    StopTime = time.time()
 
    # save StartTime
    while GPIO.input(gPin.ECHO) == 0:
        StartTime = time.time()
 
    # save time of arrival
    while GPIO.input(gPin.ECHO) == 1:
        StopTime = time.time()
 
    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = round((TimeElapsed * 34300) / 2,2)
 
    return distance


def main(args=None):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(gPin.TRIG, GPIO.OUT)
    GPIO.setup(gPin.ECHO, GPIO.IN)
    
    rclpy.init(args=args)
    mobot_ultrasonic = UltrasonicSenseClass()

    message=Float32()

    try:
        while True:
            message.data = distance()
            print ("Measured Distance = %.1f cm" % message.data)
            #time.sleep(1)
 
            mobot_ultrasonic.publisher_.publish(message)
            time.sleep(0.1)

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