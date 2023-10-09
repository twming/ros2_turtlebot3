#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Char



class BluetoothKey(Node):

    def __init__(self):
        super().__init__('mobot_bt_publish')
        self.publisher_ = self.create_publisher(Char, 'key_out', 10)

