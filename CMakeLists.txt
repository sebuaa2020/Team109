cmake_minimum_required(VERSION 3.16)
project(Team109)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/pcl-1.8)
include_directories(/opt/ros/melodic/include)

add_executable(Team109 main.cpp)
