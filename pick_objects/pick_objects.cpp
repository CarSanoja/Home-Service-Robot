#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double pick[2] = {-6.0, -9.25};
double drop[2] = {-1.0, -0.0};

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  ros::Publisher pos_pub = n.advertise<std_msgs::UInt8>("/robot_position", 1);


  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = pick[0];
  goal.target_pose.pose.position.y = pick[1];
  goal.target_pose.pose.orientation.w = 1.57;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   ROS_INFO("Hooray, picked up");
    std_msgs::UInt8 msg1;
    msg1.data = 0;
    ROS_INFO("The message is %d", msg1.data);
    pos_pub.publish(msg1);
  }

  else{
    ROS_INFO("The base failed picking up");
    return 0; 
  }
  sleep(5);

  move_base_msgs::MoveBaseGoal drop_goal;
  // set up the frame parameters
  drop_goal.target_pose.header.frame_id = "map";
  drop_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  drop_goal.target_pose.pose.position.x = drop[0];
  drop_goal.target_pose.pose.position.y = drop[1];
  drop_goal.target_pose.pose.orientation.w = 1.20;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(drop_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, GOT IT");
    std_msgs::UInt8 msg2;
    msg2.data = 1;
    ROS_INFO("The message is %d", msg2.data);
    pos_pub.publish(msg2);
    sleep(5);
  } 
  else {
    ROS_INFO("The Robot failed");
  }

  return 0;
  
}
