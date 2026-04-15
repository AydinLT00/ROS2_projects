cmake_minimum_required(VERSION 3.8)
project(robot_pkg_1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SetVelocity.srv"
  DEPENDENCIES geometry_msgs std_msgs)
  
add_executable(sensor_publisher src/sensor_pub.cpp)
ament_target_dependencies(sensor_publisher rclcpp geometry_msgs std_msgs)
# Link the generated interface library
rosidl_target_interfaces(sensor_publisher ${PROJECT_NAME} "rosidl_typesupport_cpp")



add_executable(testNode src/testNode.cpp)
ament_target_dependencies(testNode rclcpp geometry_msgs)

add_executable(subscriber_node src/subscriberNode.cpp)
ament_target_dependencies(subscriber_node rclcpp geometry_msgs)



 

install(TARGETS
  sensor_publisher
  testNode
  subscriber_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY srv
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
