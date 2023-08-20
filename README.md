# 3 steps to install ROS2 and turtlebot3
* Ubuntu focal version 20.04 (required)
* Install ROS2 foxy (compatible with Ubuntu 20.04)
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
cd ~/Downloads
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg # may need to run on writable folder
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

Install RO2 from the official repository and its development tools
```
sudo apt update
sudo apt upgrade
sudo apt install ros-foxy-desktop python3-argcomplete
sudo apt install ros-dev-tools
```
Environment setup
```
echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc
```

# Setup Turtlebot3 
Download Turtlebots package and setup
```
sudo mkdir -p ~/turtlebot3/src
vcs import . < turtlebot3.repos
colcon build --symlink-install
```

