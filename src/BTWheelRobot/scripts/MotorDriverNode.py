#!/usr/bin/env python3

import time
import rclpy
from rclpy.node import Node
from btwheelrobot.MotorDriverClass import MotorDriverClass
import btwheelrobot.Common as gPin
import RPi.GPIO as GPIO
GPIO.setwarnings(False)

def main(args=None):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(gPin.M1, GPIO.OUT)
    GPIO.setup(gPin.M2, GPIO.OUT)
    GPIO.setup(gPin.M3, GPIO.OUT)
    GPIO.setup(gPin.M4, GPIO.OUT)
    GPIO.setup(gPin.LED,GPIO.OUT)
    GPIO.setup(gPin.BUT,GPIO.IN)

    rclpy.init(args=args)
    mobot_receive = MotorDriverClass()

    rclpy.spin(mobot_receive)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    mobot_receive.destroy_node()
    rclpy.shutdown()
    GPIO.cleanup()


if __name__ == '__main__':
    main()
