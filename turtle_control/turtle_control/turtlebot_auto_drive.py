#!/usr/bin/env python3

import rclpy
import math
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry


class TurtleDriveNode(Node):
    def __init__(self):
        super().__init__('turtle_drive')
        qos_policy = rclpy.qos.QoSProfile(reliability=rclpy.qos.ReliabilityPolicy.BEST_EFFORT,
                                          history=rclpy.qos.HistoryPolicy.KEEP_LAST,
                                          depth=1)
        self.laser_scan_sub=self.create_subscription(LaserScan,'/scan',self.laser_scan_callback,qos_profile=qos_policy)
        self.odom_sub=self.create_subscription(Odometry,'/odom',self.odom_callback,qos_profile=qos_policy)
        self.cmd_vel_pub=self.create_publisher(Twist,'/cmd_vel',10)

        self.move=Twist()
        self.turtle_state=0 # 0 : Forward, 1 : Turn
        self.turtle_pose=0.0
        self.turtle_prev_pose=0.0
        self.move.linear.x=0.0
        self.move.angular.z=0.0
    
    def laser_scan_callback(self,scan:LaserScan):
        #if ( not (scan.ranges[0]<0.3) and self.turtle_state==0):
        check_scan=[2.5,2.5,2.5]

        if (scan.ranges[15]==0):
            check_scan[0]=2.5
        else:
            check_scan[0]=scan.ranges[15]

        if (scan.ranges[0]==0):
            check_scan[1]=2.5
        else:
            check_scan[1]=scan.ranges[0]

        if (scan.ranges[345]==0):
            check_scan[2]=2.5
        else:
            check_scan[2]=scan.ranges[345]


        if ( not (check_scan[0]<0.3 or check_scan[1]<0.3 or check_scan[2]<0.3) and self.turtle_state==0):
            self.turtle_state=0
            self.move.linear.x=0.05
            self.move.angular.z=0.0
        else:
            if (self.turtle_state==0):
                self.turtle_prev_pose=self.turtle_pose
                self.turtle_state=1

                # Decide the turning direction
                if (check_scan[0]>check_scan[2]):
                    self.move.linear.x=0.0
                    self.move.angular.z=0.3
                else:
                    self.move.linear.x=0.0
                    self.move.angular.z=-0.3
                
            if (abs(self.turtle_pose - self.turtle_prev_pose)>0.17 and not (check_scan[0]<0.3 or check_scan[1]<0.3 or check_scan[2]<0.3) ):
                self.turtle_state=0
        #self.get_logger().info("Actual Distance: "+str(round(scan.ranges[15],2))+", "+str(round(scan.ranges[0],2))+", "+str(round(scan.ranges[345],2))+"--> x: "+str(self.move.linear.x)+", z: "+str(self.move.angular.z))        
        self.get_logger().info("Distance: "+str(round(check_scan[0],2))+", "+str(round(check_scan[1],2))+", "+str(round(check_scan[2],2))+"--> x: "+str(self.move.linear.x)+", z: "+str(self.move.angular.z))
        self.get_logger().info("Pose Diff: "+str(round(abs(self.turtle_pose - self.turtle_prev_pose)))+", State = "+str(self.turtle_state))
        self.cmd_vel_pub.publish(self.move)

    def odom_callback(self,odom:Odometry):
        sin_y= 2 * ( odom.pose.pose.orientation.w * odom.pose.pose.orientation.z + odom.pose.pose.orientation.x * odom.pose.pose.orientation.y )
        cos_y= 1.0 - 2.0 * (odom.pose.pose.orientation.y * odom.pose.pose.orientation.y + odom.pose.pose.orientation.z * odom.pose.pose.orientation.z )
        self.turtle_pose = math.atan2(sin_y,cos_y)
        #self.get_logger().info("Pose: "+str(self.turtle_pose))
        

    def __del__(self):
        self.move.linear.x=0.0
        self.move.angular.z=0.0
        self.cmd_vel_pub.publish(self.move)   

def main(args=None):
    rclpy.init(args=args)
    node=TurtleDriveNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__=='__main__':
    main()
