#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Char
import time
import RPi.GPIO as GPIO
GPIO.setwarnings(False)


M1 = 7
M2 = 8
M3 = 9
M4 = 10
LED = 5
BUT = 6

def setMotor(S1,S2,S3,S4,timeInMs):
    GPIO.output(M1,S1)
    GPIO.output(M2,S2)
    GPIO.output(M3,S3)
    GPIO.output(M4,S4)
    time.sleep(timeInMs)

class RobotReceiveKey(Node):

    def __init__(self):
        super().__init__('mobot_receive')
        self.subscription = self.create_subscription(
            Char,
            'key_out',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('mobot receive : "%c"' % msg.data)

        GPIO.output(LED,GPIO.HIGH)

        match msg.data:
            case 119: # Key W
                self.get_logger().info('mobot move : FORWARD')
                setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.025)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)
                
            case 120: # Key x
                self.get_logger().info('mobot move : BACKWARD')
                setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.025)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)

            case 97: # Key a
                self.get_logger().info('mobot move : LEFT')
                setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.025)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)
                
            case 100: # Key d
                self.get_logger().info('mobot move : RIGHT')
                setMotor(GPIO.LOW,GPIO.HIGH,GPIO.HIGH,GPIO.LOW,0.025)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.025)

            case 101: # Key e
                self.get_logger().info('mobot move : NORTH RIGHT')
                setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.010)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.030)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)
                
            case 113: # Key q
                self.get_logger().info('mobot move : NORTH LEFT')
                setMotor(GPIO.HIGH,GPIO.LOW,GPIO.HIGH,GPIO.LOW,0.010)
                setMotor(GPIO.HIGH,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.030)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

            case 99: # Key c
                self.get_logger().info('mobot move : SOUTH RIGHT')
                setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.010)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.HIGH,0.030)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

            case 122: # Key z
                self.get_logger().info('mobot move : SOUTH LEFT')
                setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.HIGH,0.010)
                setMotor(GPIO.LOW,GPIO.HIGH,GPIO.LOW,GPIO.LOW,0.030)
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

            case 115: # Key x
                self.get_logger().info('mobot move : STOP')
                setMotor(GPIO.LOW,GPIO.LOW,GPIO.LOW,GPIO.LOW,0.010)

        GPIO.output(LED,GPIO.LOW)
