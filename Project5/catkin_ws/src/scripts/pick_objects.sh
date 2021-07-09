#!/bin/sh

xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5

xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=map_file:=/home/workspace/robot/Project5/catkin_ws/src/map/turtle_map.yaml" &
sleep 5

xterm -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
 
xterm -e "source devel/setup.bash; rosrun pick_objects pick_objects"

