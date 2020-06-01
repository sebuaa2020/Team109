#!/bin/bash
# This script is to run robot with gui


# cd ros_ws
CURR_DIR=$(dirname $(readlink -f $0))
cd $CURR_DIR
cd ../ros_ws

# install dependencies
#rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y

# make ros
catkin_make

# setup environment
source ./devel/setup.bash

# mkdir output dir
cd $CURR_DIR # first cd script folder
if ! [ -d Team109_robot ]; then
  mkdir main_controller
fi

# launch
roslaunch wpr_simulation wpb_simple.launch
rosrun cyrobot_monitor cyrobot_monitor
