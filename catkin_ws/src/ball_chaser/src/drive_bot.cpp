#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

ros::Publisher moter_command_publisher;

bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
                          ball_chaser::DriveToTarget::Response& res) {
  ROS_INFO("DriveToTarget request received - linear_x:%1.2f, angular_z:%1.2f",
      (float)req.linear_x, (float)req.angular_z);

  geometry_msgs::Twist moter_command;
  moter_command.linear.x = req.linear_x;
  moter_command.angular.z = req.angular_z;
  moter_command_publisher.publish(moter_command);

  // Wait 1 second for velocities to settle
  ros::Duration(1).sleep();
  
  // Return a response message
  res.msg_feedback = "Velocities set - linear_x: " + std::to_string(req.linear_x) + " , angular_z: " + std::to_string(req.angular_z);
  ROS_INFO_STREAM(res.msg_feedback);

  return true;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "drive_bot");
  
  ros::NodeHandle n;

  // Inform ROS master that we will be publishing a message of
  // type geometry_msgs::Twist on the robot actuation topic with a publishing
  // queue size of 10
  moter_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  // Define a drive /ball_chaser/command_robot service with a
  // handle_drive_request callback function
  ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot",
      handle_drive_request); 
  
  // Handle ROS communication events
  ros::spin();

  return 0;
}

