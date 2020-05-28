cmake_minimum_required(VERSION 3.5)
project(Team109)

set(CMAKE_CXX_STANDARD 14)

# custom by your environment this can make your IDE like clion support intellisense
include_directories(/opt/ros/kinetic/include)
include_directories(/usr/include/pcl-1.7)

add_executable(Team109 main.cpp)

# this will added at my local which make clion support intellisense
add_executable(main_controller ros_ws/src/my_pkg/src/main_controller.cpp)
include_directories(ros_ws/src/my_pkg/include)
add_library(utils ros_ws/src/my_pkg/src/utils.cpp ros_ws/src/my_pkg/include/utils.h)
target_link_libraries(main_controller utils)

add_executable(wp_manager ros_ws/src/waterplus_map_tools/src/wp_manager.cpp)
add_executable(run_around_picture ros_ws/src/my_pkg/src/run_around_picture.cpp)
