#!/usr/bin/env python3

import time
import serial
import rclpy
from rclpy.node import Node
from std_msgs.msg import Char
from btwheelrobot.BluetoothClass import BluetoothClass
import btwheelrobot.Common
import RPi.GPIO as GPIO
GPIO.setwarnings(False)

def main(args=None):
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(STATUS,GPIO.OUT)
    GPIO.setup(BUT,GPIO.IN) # STATUS Check
    GPIO.output(STATUS,GPIO.HIGH) # BT Control
    ser=serial.Serial(port="/dev/ttyAMA0",baudrate=9600)
    
    rclpy.init(args=args)
    mobot_bluetooth = BluetoothClass()

    message=Char()

    while(rclpy.ok()):
        received_data=ser.read()
        time.sleep(0.03)
        data_left=ser.inWaiting()
        received_data+=ser.read(data_left)
        print("mobot receive : "+received_data.decode('utf-8'))

        key1=received_data.decode('utf-8')[0]
        key2=received_data.decode('utf-8')[1]

        match key1:
            case 'N': # FORWARD key w
                message.data=119
                print('mobot move : FORWARD')

            case 'S': # BACKWARD key x
                message.data=120
                print('mobot move : BACKWARD')

            case 'E': # RIGHT key d
                message.data=100
                print('mobot move : RIGHT')
                
            case 'W': # LEFT key a
                message.data=97
                print('mobot move : LEFT')

            case 'A': # NORTH RIGHT key e
                message.data=101
                print('mobot move : NORTH RIGHT')

            case 'B': # SOUTH RIGHT key c
                message.data=99
                print('mobot move : SOUTH RIGHT')

            case 'C': # SOUTH LEFT key z
                message.data=122
                print('mobot move : SOUTH LEFT')
                
            case 'D': # NORTH LEFT key q
                message.data=113
                print('mobot move : NORTH LEFT')
            
            case '0': # Check Key 2
                if (key2=='4'):
                    if (GPIO.input(BUT)):
                        GPIO.output(STATUS,GPIO.LOW)
                        print('mobot STATE : Keyboard Control OFF')
                    else:
                        GPIO.output(STATUS,GPIO.HIGH)
                        print('mobot STATE : Keyboard Control ON')
                elif (key2=='3'):
                    if (GPIO.input(BUT)):
                        GPIO.output(STATUS,GPIO.LOW)
                        print('mobot STATE : Keyboard Control OFF')
                    else:
                        GPIO.output(STATUS,GPIO.HIGH)
                        print('mobot STATE : Keyboard Control ON')
                continue

            case _:
                continue

        mobot_bluetooth.publisher_.publish(message)
        time.sleep(0.08)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    mobot_bluetooth.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
