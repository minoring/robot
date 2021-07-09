#!/bin/sh

xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/robot/Project5/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/worlds/Home.world" &
sleep 5

xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo amcl.launch map_file:=/home/workspace/robot/Project5/catkin_ws/src/map/map.yaml" &
sleep 5

xterm -e "source devel/setup.bash; rosrun rviz rviz -d src/rvizConfig/home_service.rviz" &
sleep 5

xterm -e "source devel/setup.bash; rosrun add_markers add_markers" &
sleep 5

xterm -e "source devel/setup.bash; rosrun pick_objects pick_objects"

