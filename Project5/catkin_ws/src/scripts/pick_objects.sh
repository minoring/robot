#!/bin/sh

xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5

xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find pick_objects)/map/turtle_map.yaml" &
sleep 5

xterm -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
 
xterm -e "source devel/setup.bash; rosrun pick_objects pick_objects"

