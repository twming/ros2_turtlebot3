#!/usr/bin/env python3

import time
import rclpy
from rclpy.node import Node
from btwheelrobot.MotorDriverClass import MotorDriverClass
import btwheelrobot.Common
import RPi.GPIO as GPIO
GPIO.setwarnings(False)

def main(args=None):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(M1, GPIO.OUT)
    GPIO.setup(M2, GPIO.OUT)
    GPIO.setup(M3, GPIO.OUT)
    GPIO.setup(M4, GPIO.OUT)
    GPIO.setup(LED,GPIO.OUT)
    GPIO.setup(BUT,GPIO.IN)

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
