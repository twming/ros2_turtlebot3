cmake_minimum_required(VERSION 3.8)
project(wheel_robot_teleop)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)


#include cpp in <include> directory
include_directories(include)

#create cpp executables and its dependencies
set(dependencies 
  rclcpp
  std_msgs
)
add_executable(key_send src/KeyBoardSendNode.cpp)
ament_target_dependencies(key_send ${dependencies})

#install cpp executables
install(TARGETS
  key_send
  DESTINATION lib/${PROJECT_NAME}
)

#----------#
#install py modues, similar to cpp include directory
ament_python_install_package(${PROJECT_NAME})

#install py executables
install(PROGRAMS
  scripts/MobotReceiveNode.py
  scripts/MobotBluetoothPublishNode.py
  DESTINATION lib/${PROJECT_NAME}
)

install (
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/

)

ament_package()
