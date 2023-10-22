#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Char



class BluetoothClass(Node):

    def __init__(self):
        super().__init__('bluetooth_node')
        self.publisher_ = self.create_publisher(Char, 'key_out', 10)

