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
	printf '\033[1;32m%s\033[m\n' "=================================================="
	printf '\033[1;32m%s\033[m\n' "ERROR: This architecture ($(dpkg --print-architecture)) is not supported"
	printf '\033[1;32m%s\033[m\n' "See https://www.ros.org/reps/rep-2000.html"
	printf '\033[1;32m%s\033[m\n' "=================================================="
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
sudo apt install -y ros-humble-ros-base
sudo apt install -y ros-humble-turtlebot3-bringup

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Update ROS Environment Variables     |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 9)                  |"
printf '\033[1;32m%s\033[m\n' "=================================================="

echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc
echo 'export ROS_DOMAIN_ID=30' >> ~/.bashrc
echo 'export TURTLEBOT3_MODEL=burger' >> ~/.bashrc
echo 'export LDS_MODEL=LDS-01' >> ~/.bashrc

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Install OpenCR firmware dependencies |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 10)                 |"
printf '\033[1;32m%s\033[m\n' "=================================================="

sudo dpkg --add-architecture armhf
sudo apt-get update  
sudo apt-get install -y libc6:armhf

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           Download OpenCR firmware             |"
printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 11)                 |"
printf '\033[1;32m%s\033[m\n' "=================================================="

cd ~
wget https://github.com/ROBOTIS-GIT/OpenCR-Binaries/raw/master/turtlebot3/ROS2/latest/opencr_update.tar.bz2   
tar -xvf opencr_update.tar.bz2

printf '\033[1;32m%s\033[m\n' "=================================================="
printf '\033[1;32m%s\033[m\n' "|           ROS Installation Complete            |"
printf '\033[1;32m%s\033[m\n' "=================================================="

#. ~/.bashrc

#printf '\033[1;32m%s\033[m\n' "=================================================="
#printf '\033[1;32m%s\033[m\n' "|           Install LDS-02 Driver                |"
#printf '\033[1;32m%s\033[m\n' "|           TODO: HERE (Step 8)                  |"
#printf '\033[1;32m%s\033[m\n' "=================================================="

#sudo apt install -y python3-argcomplete python3-colcon-common-extensions libboost-system-dev build-essential
#sudo apt install -y libudev-dev
#mkdir -p ~/turtlebot3_ws/src && cd ~/turtlebot3_ws/src
#git clone -b humble https://github.com/ROBOTIS-GIT/ld08_driver.git
#cd ~/turtlebot3_ws/
#colcon build
#echo 'source ~/turtlebot3_ws/install/setup.bash' >> ~/.bashrc



