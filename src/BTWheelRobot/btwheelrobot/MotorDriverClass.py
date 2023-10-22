#!/usr/bin/env python3

import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import Char
import btwheelrobot.Common
import RPi.GPIO as GPIO
GPIO.setwarnings(False)

def setMotor(S1,S2,S3,S4,timeInMs):
    GPIO.output(M1,S1)
    GPIO.output(M2,S2)
    GPIO.output(M3,S3)
    GPIO.output(M4,S4)
    time.sleep(timeInMs)

class MotorDriverClass(Node):

    def __init__(self):
        super().__init__('motor_driver_node')
        self.subscription = self.create_subscription(
            Char,
            'key_out',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('mobot receive : "%c"' % msg.data)

        if (GPIO.input(BUT)):
            GPIO.output(LED,GPIO.HIGH)

            match msg.data:
                case 119: # Key w
                    self.get_logger().info('mobot move : FORWARD')
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.070)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)
                    
                case 120: # Key x
                    self.get_logger().info('mobot move : BACKWARD')
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.070)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

                case 97: # Key a
                    self.get_logger().info('mobot move : LEFT')
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.HIGH,GPIO.LOW,0.070)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)
                    
                case 100: # Key d
                    self.get_logger().info('mobot move : RIGHT')
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.070)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)

                case 101: # Key e
                    self.get_logger().info('mobot move : NORTH RIGHT')
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.020)
                    setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.040)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)
                    
                case 113: # Key q
                    self.get_logger().info('mobot move : NORTH LEFT')
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.HIGH,GPIO.LOW,0.020)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.040)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)

                case 99: # Key c
                    self.get_logger().info('mobot move : SOUTH RIGHT')
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.020)
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.LOW,0.040)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)

                case 122: # Key z
                    self.get_logger().info('mobot move : SOUTH LEFT')
                    setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.020)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.040)
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.01)

                case 115: # Key s
                    self.get_logger().info('mobot move : STOP')
                    setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

            GPIO.output(LED,GPIO.LOW)

        else:
            self.get_logger().info('Please turn ON Keyboard Control')
