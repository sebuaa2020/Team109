#!/bin/bash
# This script is to run main controller to run other service


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
if ! [ -d main_controller ]; then
  mkdir main_controller
fi

# launch
roslaunch wpr_simulation wpb_simple.launch > main_controller/wpr_simulation.log &
rosrun my_pkg main_controller -d main_controller
