#!/bin/bash
# This script is to control robot by voice


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

# voice
roslaunch xfyun_waterplus iat_cn.launch &
roslaunch xfyun_waterplus voice_cmd_wpb_home.launch &
rosrun my_pkg voice_ctrl
