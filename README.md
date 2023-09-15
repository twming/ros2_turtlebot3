# 3 steps to install ROS2 and turtlebot3
* Ubuntu Jammy Jellyfish version 22.04 (required)
* Install ROS2 humble (compatible with Ubuntu 22.04)
* Setup Turtlebot3 


# Install ROS2 foxy
Check and set the locale of your computer
```
locale  # check for UTF-8
sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
locale  # verify settings
```

Download the ROS2 key and setup the key. Upload the key into the Authentication Library in Ubuntu. Setup the RO2 download repository
```
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

Install RO2 from the official repository and its development tools
```
sudo apt update
sudo apt upgrade
sudo apt install ros-humble-desktop
sudo apt install ros-dev-tools
```
Environment setup
```
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
```

Install Gazebo
```
sudo apt install gazebo
```

# Setup Turtlebot3 
Install the dependency
```
sudo apt install gazebo11
sudo apt install ros-humble-gazebo-ros-pkgs
sudo apt install ros-humble-cartographer 
sudo apt install ros-humble-cartographer-ros
sudo apt install ros-humble-navigation2 
sudo apt install ros-humble-nav2-bringup
```
Download Turtlebots package and setup [https://github.com/ROBOTIS-GIT/turtlebot3]
```
sudo mkdir -p ~/turtlebot3_ws/src
git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git -b humble-devel
git clone https://github.com/ROBOTIS-GIT/turtlebot3.git -b humble-devel
git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git -b humble-devel
git clone https://github.com/ROBOTIS-GIT/DynamixelSDK.git -b humble-devel
cd ~/turtlebot3_ws
colcon build --symlink-install
```
Setup the turtlebot3 environement
```
echo "export TURTLEBOT3_MODEL=waffle_pi" >> ~/.bashrc
echo "export GAZEBO_MODEL_PATH=/home/twm/turtlebot3_ws/src/turtlebot3_simulations/turtlebot3_gazebo/models:/usr/share/gazebo-11/models:$GAZEBO_MODEL_PATH" >> ~/.bashrc
echo "source ~/turtlebot3_ws/install/setup.bash" >> ~/.bashrc
```
Testing your turtlebot3 in ROS2. Others package needed ros-foxy-gazebo-ros-pkgs, ros-foxy-slam-toolbox and nav2_bringup.

```
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
Above let you teleop and move your turtlebot3 around. Below is to SLAM and navigate your turtlebot3.
```
ros2 launch slam_toolbox online_async_launch.py
ros2 run nav2_map_server map_saver_cli -f ~/my_map
ros2 launch nav2_bringup bringup_launch.py use_sim_time:=True autostart:=True map:=/path/to/my_map.yaml
ros2 run rviz2 rviz2 -d $(ros2 pkg prefix nav2_bringup)/share/nav2_bringup/rviz/nav2_default_view.rviz

```
# Testing your own robot (my_robot)
Display your robot in rviz2
```
ros2 run robot_state_publisher robot_state_publisher --ros-args -p robot_description:="$(xacro my_robot.xacro)"
ros2 run joint_state_publisher_gui joint_state_publisher_gui
ros2 run rviz2 rviz2
rqt_graph
```
# Create your own robot package
```
mkdir -p ros2_ws/src
cd ros_ws
colcon build
cd src
ros2 pkg create my_robot_description
```
Goto CMakeList.txt, add the install folder
```
install (
	DIRECTORY urdf
	DESTINATION share/${PROJECT_NAME}/
)
```
# Spawn your robot in Gazebo
```
ros2 run robot_state_publisher robot_state_publisher --ros-args -p robot_description:="$(xacro my_robot.xacro)"
ros2 launch gazebo_ros gazebo_launch.py
ros2 run gazebo_ros spawn_entity.py -topic robot_description -entity my_robot
```
# Publish topic to your robot
```
ros2 topic pub -1 /cmd_vel geometry_msgs/msg/Twist "{linear:{x: 0.0,y: 0.0,z: 0.0},angular:{x: 0.0,y: 0.0,z: 0.0}}"
ros2 topic pub -1 /set_joint_trajectory trajectory_msgs/msg/JointTrajectory '{header:{frame_id: base_footprint_link}, joint_names: [arm_base_forearm_joint, forearm_hand_joint],points: [ {positions: {0.0, 0.0}} ]}'
```

Arduino IDE setup:
```
http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup
https://github.com/ohlr/braccio_arduino_ros_rviz/tree/master
https://github.com/klintan/ros2_usb_camera
```
