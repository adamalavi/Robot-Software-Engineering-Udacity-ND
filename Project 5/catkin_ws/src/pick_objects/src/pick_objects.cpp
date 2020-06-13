#include "ros/ros.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  
  ros::Publisher state_pub = n.advertise<std_msgs::Int8>("state", 100);
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  
  std_msgs::Int8 msg;
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  float goals[2][3] = { {7, -1.2, 1.0}, {-3.5, -1.5, -1.57}  };
  // Define a position and orientation for the robot to reach
  for(int i=0;i<sizeof(goals)/sizeof(goals[0]);i++)
  {
    goal.target_pose.pose.position.x = goals[i][0];
    goal.target_pose.pose.position.y = goals[i][1];
    goal.target_pose.pose.orientation.w = goals[i][2];

     // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
    
    msg.data = 0;
    if (i==1)
      msg.data = 2;
    ROS_INFO("%d", msg.data);
    state_pub.publish(msg);
    
    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      ROS_INFO("Goal reached");
      msg.data = 1;
      if (i==1)
        msg.data = 3;
      ROS_INFO("%d", msg.data);
      state_pub.publish(msg);
    }
    else
      ROS_INFO("Traversal failed for some reason");
    ros::Duration(5.0).sleep();
  }
  return 0;
}