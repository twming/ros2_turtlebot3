FROM ubuntu:jammy

ENV ROS_DISTRO=humble
ENV AMENT_PREFIX_PATH=/opt/ros/${ROS_DISTRO}
ENV COLCON_PREFIX_PATH=/opt/ros/${ROS_DISTRO}
ENV LD_LIBRARY_PATH=/opt/ros/${ROS_DISTRO}/lib
ENV PATH=/opt/ros/${ROS_DISTRO}/bin:$PATH
ENV PYTHONPATH=/opt/ros/${ROS_DISTRO}/lib/python3.10/site-packages
ENV ROS_PYTHON_VERSION=3
ENV ROS_VERSION=2

ENV TZ=Asia/Singapore

RUN apt update && apt install curl -y
RUN apt install -y --no-install-recommends tzdata
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

RUN apt update && apt upgrade -y

RUN apt install -y ros-humble-desktop
RUN apt install -y ros-dev-tools
RUN apt install -y ros-humble-xacro ros-humble-turtlesim ros-humble-joint-state-publisher-gui ros-humble-turtlebot3 ros-humble-turtlebot3-simulations ros-humble-rqt-graph ros-humble-rqt


RUN echo "export DISPLAY=host.docker.internal:0.0" >> ~/.bashrc
RUN echo "export TURTLEBOT3_MODEL=burger" >> ~/.bashrc
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
RUN echo "source /usr/share/gazebo/setup.sh" >> ~/.bashrc
RUN echo "source /root/dev_ws/install/setup.bash" >> ~/.bashrc

RUN echo "echo '------------------------------------------------'" >> ~/.bashrc
RUN echo "echo '| MAKE SURE IN dev_ws BEFORE colcon build:     |'" >> ~/.bashrc
RUN echo "echo '|   cd ~/dev_ws                                |'" >> ~/.bashrc
RUN echo "echo '|   colcon build                               |'" >> ~/.bashrc
RUN echo "echo '| AFTER BUILT, MAKE SURE source THE setup.bash |'" >> ~/.bashrc
RUN echo "echo '|   source ~/dev_ws/install/setup.bash         |'" >> ~/.bashrc
RUN echo "echo '------------------------------------------------'" >> ~/.bashrc

WORKDIR /root
