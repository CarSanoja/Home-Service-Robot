
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 20

#launch amcl with world made by slam previously
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 7

#Launch navigation and rviz navigation settings
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 7

xterm -e "rosrun add_markers basic_shapes" 
