#!/bin/sh
cd $(pwd)/../..; catkin_make
export ROBOT_INITIAL_POSE="-x -3 -y -3 -Y 0"
xterm -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/src/map/Adamworld.world; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"