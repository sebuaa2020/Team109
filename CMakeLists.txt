cmake_minimum_required(VERSION 3.16)
project(Team109)

set(CMAKE_CXX_STANDARD 14)

# custom by your environment this can make your IDE like clion support intellisense
include_directories(/opt/ros/melodic/include)
include_directories(/usr/include/pcl-1.8)

add_executable(Team109 main.cpp)
