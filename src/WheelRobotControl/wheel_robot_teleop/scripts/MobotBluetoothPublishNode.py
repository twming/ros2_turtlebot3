#!/usr/bin/env python3

import time
import serial
import rclpy
from rclpy.node import Node
from std_msgs.msg import Char
from wheel_robot_teleop.BluetoothKey import BluetoothKey


def main(args=None):
    ser=serial.Serial(port="/dev/ttyAMA0",baudrate=9600)
    
    rclpy.init(args=args)
    mobot_bluetooth = BluetoothKey()

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
            case 'N': # FORWARD
                message.data=119
                print('mobot move : FORWARD')

            case 'S': # BACKWARD
                message.data=120
                print('mobot move : BACKWARD')

            case 'E': # RIGHT
                message.data=100
                print('mobot move : RIGHT')
                
            case 'W': # LEFT
                message.data=97
                print('mobot move : LEFT')

            case 'A': # FORWARD
                message.data=101
                print('mobot move : NORTH RIGHT')

            case 'B': # BACKWARD
                message.data=99
                print('mobot move : SOUTH RIGHT')

            case 'C': # RIGHT
                message.data=122
                print('mobot move : SOUTH LEFT')
                
            case 'D': # LEFT
                message.data=113
                print('mobot move : NORTH LEFT')
            
            case _:
                continue

        mobot_bluetooth.publisher_.publish(message)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    mobot_bluetooth.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
