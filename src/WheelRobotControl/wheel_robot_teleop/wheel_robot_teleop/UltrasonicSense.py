#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32

class UltrasonicSense(Node):

    def __init__(self):
        super().__init__('mobot_ultrasonic_publish')
        self.publisher_ = self.create_publisher(Float32, 'ultrasonic_out', 10)
