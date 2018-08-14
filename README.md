# Home-Service-Robot

#### Summary of Tasks
Let’s summarize what should be done in this project to simulate a home service robot:

1. Design a simple environment with the Building Editor in Gazebo.
2. Teleoperate your robot and manually test SLAM.
3. Create a wall_follower node that autonomously drives your robot to map your environment.
4. Use the ROS navigation stack and manually commands your robot using the 2D Nav Goal arrow in rviz to move to 2 different desired positions and orientations.
5. Write a pick_objects node that commands your robot to move to the desired pickup and drop off zones.
6. Write an add_markers node that subscribes to your robot odometry, keeps track of your robot pose, and publishes markers to rviz.


#### Install ROS Navigation System

```bash
$ sudo apt-get update
$ sudo apt-get install ros-kinetic-navigation
```

### install xterm 

```bash
$ sudo apt-get install xterm
```

For this setup, catkin_ws is the name of the active ROS workspace.

```sh
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ..
catkin_make
source devel/setup.bash
```

Clone the required repository to the `~/catkin_ws/src` folder. Note that this repository already includes official ROS packages compatible with this repository: [gmapping](https://github.com/ros-perception/slam_gmapping), [turtlebot_teleop](https://github.com/turtlebot/turtlebot), [turtlebot_rviz_launchers](https://github.com/turtlebot/turtlebot_interactions), and [turtlebot_gazebo](https://github.com/turtlebot/turtlebot_simulator).

* **gmapping**: With the `gmapping_demo.launch` file, you can easily perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.

* **turtlebot_teleop**: With the `keyboard_teleop.launch` file, you can manually control a robot using keyboard commands.

* **turtlebot_rviz_launchers**: With the `view_navigation.launch` file, you can load a preconfigured rviz workspace. You’ll save a lot of time by launching this file, because it will automatically load the robot model, trajectories, and map for you.

* **turtlebot_gazebo**: With the `turtlebot_world.launch` you can deploy a turtlebot in a gazebo environment by linking the world file to it.


```sh
cd ~/catkin_ws/src
git clone https://github.com/CarSanoja/Home-Service-Robot
sudo apt-get update
rosdep -i install gmapping -y
rosdep -i install turtlebot_teleop -y
rosdep -i install turtlebot_rviz_launchers -y
rosdep -i install turtlebot_gazebo -y
```

#### Build catkin workspace

```bash
$ cd ~/catkin_ws
$ catkin_make
```
#### source the development folder

```bash
$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```

## Map navigation based on the built map

```bash
$ cd ~/catkin_ws/src/folders/ShellScripts
$ ./home_service.sh 
```
## Results

Video: https://youtu.be/e1sITd4z_jg
