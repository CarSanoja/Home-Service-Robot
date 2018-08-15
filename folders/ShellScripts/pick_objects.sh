# !bin/sh

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find folders)/World/U_world5.world" &
sleep 20

#launch amcl with world made by slam previously
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find folders)/World/mymap5.yaml" &
sleep 8

#Launch navigation and rviz navigation settings
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 4

#pick objects node
xterm -e "rosrun pick_objects pick_objects" 
