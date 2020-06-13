# HOME SERVICE ROBOT
Project 5 of Udacity Robotics Software Engineer Nanodegree
![video](https://github.com/adamalavi/Robot-Software-Engineering-Udacity-ND/blob/master/Project%205/videos/Project%205-Home%20service%20robot.gif)  

## Overview  
In this project, you will use everything you learned in the Nanodegree Program to build a Home Service Robot in ROS.  
### Mapping  
You will create a `test_slam.sh` script file and launch it to manually test SLAM.  
A functional map of the environment should be created which would be used for localization and navigation tasks.  
### Localization and Navigation  
You will create a `test_navigation.sh` script file to launch it for manual navigation test.  
Your robot should be able to navigate in the environment after a 2D Nav Goal command is issued.  
You will create a `pick_objects.sh` file that will send multiple goals for the robot to reach.  
The robot travels to the desired pickup zone, displays a message that it reached its destination, waits 5 seconds, travels to the desired drop off zone, and displays a message that it reached the drop off zone. 
### Home Service Functions  
You will create a `add_marker.sh` file that will publish a marker to rviz.  
The marker should initially be published at the pickup zone.
The student should write a home_service.sh file that will run all the nodes in this project.  
The student's home service robot should be simulated as follow:  
* Initially show the marker at the pickup zone.
* Hide the marker once your robot reaches the pickup zone.
* Wait 5 seconds to simulate a pickup.
* Show the marker in the drop off zone once your robot reaches it.

## Packages used and their functions
1.  TurtleBot packages are used to spawn and use a turtle bot to map the world and move across it from one location to another.
2.	Gmapping package is used for mapping the world. It provides the feature of Simultaneous Localization And Mapping (SLAM) which is used to create a map of the world that can later be used by the turtle bot to localize itself and navigate its way through the world from the start point to the pick up zone and then to the drop zone.
3.	AMCL node is used for the purpose of localization. The adaptive Monte Carlo localisation node uses a particle filter for the purpose of localisation. For the AMCL node to work, it needs a predefined map of the environment which is obtained from the gmapping node.
4.	Pick_objects node was written in C++ and it provides the turtlebot with a set of goal coordinates to the turtle bot base for it to move to. In this node, the turtle bot is first provided the coordinates of the pick up zone to the robot base. When the robot is enroute to the pick up zone it publishes a topic “state” as an integer zero which is received by the add_markers node. As soon as the robot reaches the pick up position, the state is changed to 1 and this tells the add_markers node to delete the virtual object from the pick up zone. Then the robot moves to the goal pose after waiting for 5 seconds and the state changes to 2. As the robot reaches the drop zone, the state is changed to 3 and thus the add_markers adds the virtual object in the drop zone signalling the completion of the task.
5.	Add_markers node is a subscriber of the topic “state” and it adds or deletes markers from the pick up and drop zones based on the integer values published by the pick_objects node.


## Prerequisites/Dependencies  
* Gazebo >= 7.0  
* ROS Kinetic  
* ROS navigation package  
```
sudo apt-get install ros-kinetic-navigation
```
* ROS map_server package  
```
sudo apt-get install ros-kinetic-map-server
```
* ROS move_base package  
```
sudo apt-get install ros-kinetic-move-base
```
* ROS amcl package  
```
sudo apt-get install ros-kinetic-amcl
```

## Run the project  
* Clone this repository
* Navigate to the `src` folder and clone the necessary repositories  
```
cd /home/workspace/catkin_ws/src  
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git  
```
* Open the repository, make and source  
```
cd /home/workspace/catkin_ws/
catkin_make
source devel/setup.bash
```
* Launch the home service robot
```
./src/scripts/home_service.sh
```
