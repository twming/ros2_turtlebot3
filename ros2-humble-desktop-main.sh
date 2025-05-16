#!/usr/bin/env bash
set -eu

CHOOSE_ROS_DISTRO=humble
INSTALL_PACKAGE=ros-base
TARGET_OS=jammy

# Check OS version
if ! which lsb_release > /dev/null ; then
	sudo apt-get update
	sudo apt-get install -y curl lsb-release
fi

if ! dpkg --print-architecture | grep -q 64; then
	printf '\033[1;31m%s\033[m\n' "=================================================="
	printf '\033[1;31m%s\033[m\n' "ERROR: This architecture ($(dpkg --print-architecture)) is not supported"
	printf '\033[1;31m%s\033[m\n' "See https://www.ros.org/reps/rep-2000.html"
	printf '\033[1;31m%s\033[m\n' "=================================================="
	exit 1
fi

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Update Ubuntu 22.05                  |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 8)                  |"
printf '\033[1;32m%s\033[m\n' "=================================================="

locale
sudo apt update && sudo apt install locales -y
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
locale

sudo apt install -y software-properties-common
sudo add-apt-repository -y universe

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Get ROS Humble key                   |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 8)                  |"
printf '\033[1;32m%s\033[m\n' "=================================================="

sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Install ROS Humble                   |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 8)                  |"
printf '\033[1;32m%s\033[m\n' "=================================================="

sudo apt update
sudo apt upgrade -y
sudo apt install -y ros-humble-desktop
sudo apt install -y ros-dev-tools
sudo apt install -y ros-humble-xacro ros-humble-turtlebot3 ros-humble-turtlebot3-simulations ros-humble-joint-state-publisher-gui 

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Update ROS Environment Variables     |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 9)                  |"
printf '\033[1;32m%s\033[m\n' "=================================================="

echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc
echo 'source /usr/share/gazebo/setup.sh' >> ~/.bashrc
echo 'export ROS_DOMAIN_ID=30' >> ~/.bashrc
echo 'export TURTLEBOT3_MODEL=burger' >> ~/.bashrc


printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           ROS Installation Complete            |"
printf '\033[1;32m%s\033[m\n' "=================================================="

source ~/.bashrc

