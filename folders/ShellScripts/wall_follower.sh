# !bin/sh

#Launching turtle bot in U world
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 20

#run slam
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" & 
sleep 5

#run navigation
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3

# run wall follower
xterm -e "rosrun wall_follower wall_follower_NODE"
