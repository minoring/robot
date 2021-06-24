#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z) {
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;  
  srv.request.angular_z = ang_z;  

  if (!client.call(srv)) {
    ROS_ERROR("Failed to call service /ball_chaser/command_robot");
  }
}

void process_image_callback(const sensor_msgs::Image img) {
  int white_pixel = 255;
  float lin_x = 0;
  float ang_z = 0;

  // Loop through each pixel in the image and determine the presence of the ball
  for (int i = 0; i < img.height * img.step; ++i) {
    if (img.data[i] == white_pixel) {
      if (i % img.step < img.step / 3) {
        ROS_INFO_STREAM("The ball is in left side");
        ang_z = 0.2;
      } else if (i % img.step < img.step * 2 / 3) {
        ROS_INFO_STREAM("The ball is in middle side");
        // If the ball is in middle, move forward
        lin_x = 0.3;    
      } else {
        ROS_INFO_STREAM("The ball is in right side");
        ang_z = -0.2;
      }
      break;
    }
  }
  drive_robot(lin_x, ang_z);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
  
  // Subscribe to /camera/rgb/image_raw topic to read the image data inside
  // the process_image_callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  // Handle ROS communication events
  ros::spin();
  
  return 0;
}

