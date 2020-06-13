#!/bin/sh
cd $(pwd)/../..; catkin_make
export ROBOT_INITIAL_POSE="-x -3 -y -3 -Y 0"
export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/map/map.yaml"
export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/map/Adamworld.world" 
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5