cmake_minimum_required(VERSION 3.8)
project(swChallenge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
 
  set(ament_cmake_copyright_FOUND TRUE)
  
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(turtleControl src/comp1.cpp)
ament_target_dependencies(turtleControl rclcpp)


include_directories(rclcpp)
target_link_libraries(swChallenge rclcpp)


install(TARGETS
  turtleControl
  DESTINATION lib/swChallenge
 )

install(DIRECTORY
  launch
  DESTINATION share/swChallenge/
)

ament_package()

find_package(rclcpp REQUIRED)