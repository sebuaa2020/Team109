#!/bin/bash
# This script is to make robot run around map and picture


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

# launch

