#!/bin/bash
# This script is to run object detection within ros

# cd ros_ws
CURR_DIR=$(dirname $(readlink -f $0))
cd $CURR_DIR
cd ../ros_ws

# install dependencies
#rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y

# make ros
catkin_make

# setup environment
source ./devel/setup.zsh

# launch
roslaunch wpr_simulation wpb_simple.launch &
roslaunch wpb_home_tutorials obj_detect.launch &
rosrun my_pkg obj_detect_recv_marker