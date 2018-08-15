#!/bin/sh

#Launch turtlebot in the custom world
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find folders)/World/U_world5.world" &
sleep 20

#Launch gmapping demo
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch  " &
sleep 3

#Launch turtlebot teleop
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 3

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
