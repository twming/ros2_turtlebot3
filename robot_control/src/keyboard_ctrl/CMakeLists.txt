cmake_minimum_required(VERSION 3.8)
project(keyboard_ctrl)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

set(dependencies 
  rclcpp
  std_msgs
)

add_executable(keyboard_receive src/KeyBoardReceiveNode.cpp)
ament_target_dependencies(keyboard_receive ${dependencies})

add_executable(keyboard_send src/KeyBoardSendNode.cpp)
ament_target_dependencies(keyboard_send ${dependencies})

install(TARGETS
  keyboard_receive
  keyboard_send
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install (
  DIRECTORY src launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
