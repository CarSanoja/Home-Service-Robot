# !bin/sh

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 20

#launch amcl with world made by slam previously
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5

#Launch navigation and rviz navigation settings
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 20

#pick objects node
xterm -e "rosrun pick_objects pick_objects" &

#start markers
xterm -e "rosrun add_markers basic_shapes" 

