# Project5: Implementation of Navigation Robot

## Given map defined by SLAM, use Dijkstra's algorithm to navigate the map, pick up objects and drop off to the goal state.

![](https://github.com/minoring/robot/blob/master/Project5/resources/Navigation.png)


## Sequence of Projects
- [Project1](https://github.com/minoring/robot/tree/master/Project1)
- [Project2](https://github.com/minoring/robot/tree/master/Project2)
- [Project3](https://github.com/minoring/robot/tree/master/Project3)
- [Project4](https://github.com/minoring/robot/tree/master/Project4)

## Third-party Packages used in this project
- [slam_gmapping](https://github.com/ros-perception/slam_gmapping) for SLAM. Using gmapping node, with the robot equipped with RGB-D camera, we created the map to navigate (run `./src/scripts/test_slam.sh` to test gmapping)
- [turtlebot](https://github.com/turtlebot/turtlebot) provides all the basic drivers for running and using a TurtleBot with ROS
- [turtlebot_interactions](https://github.com/turtlebot/turtlebot_interactions) supports user side interactions with the turtlebot
- [turtlebot_simulator](https://github.com/turtlebot/turtlebot_simulator) provides launchers for Gazebo of the TurtleBot
## Packages of this project
- [add_markers](https://github.com/minoring/robot/tree/master/Project5/catkin_ws/src/add_markers) create markers in rViz, indicating the objects to pick up and goal state.
- [pick_objects](https://github.com/minoring/robot/tree/master/Project5/catkin_ws/src/pick_objects) moves the robot to goal state, utilizing the map defined using SLAM.
