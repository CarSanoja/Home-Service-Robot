#!/bin/sh

#Launch turtlebot in the custom world
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find folders)/World/U_world5.world" &
sleep 20

#Launch gmapping demo
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find folders)/World/mymap5.yaml" &

sleep 6

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
