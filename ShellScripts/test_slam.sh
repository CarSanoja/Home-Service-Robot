#!/bin/sh

#Launch turtlebot in the custom world
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$/home/workspace/catkin_ws/Home-Service-Robot/Worlds/U_world1.world" &
sleep 2

#Launch gmapping demo
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:=$/home/workspace/catkin_ws/Home-Service-Robot/turtlebot_simulator/turtlebot_gazebo/launch/gmapping.launch.xml" &
sleep 3

#Launch turtlebot teleop
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 3

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
