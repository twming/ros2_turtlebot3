cmake_minimum_required(VERSION 3.8)
project(bumpgo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(dependencies
  rclcpp
  sensor_msgs
  geometry_msgs
)

include_directories(include)

add_executable(bumpgo
  src/BumpGoNode.cpp
  src/bumpgo_main.cpp
)
ament_target_dependencies(bumpgo ${dependencies})

install(TARGETS
  bumpgo
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install (
  DIRECTORY src
  DESTINATION share/${PROJECT_NAME}
)
ament_package()
