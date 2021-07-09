#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"

visualization_msgs::Marker marker;
ros::Publisher marker_pub;
bool reached_pickup = false;
bool reached_dropoff = false;
double pickup_x = -3.0;
double pickup_y = -1.0;
double pickup_w = 1.0;
double dropoff_x = -1.0;
double dropoff_y = -1.5;
double dropoff_w = 1.0;
double threshold = 0.3;

void odom_callback(const nav_msgs::Odometry::ConstPtr& msg) {
  ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", 
      msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  // Since map is rotated 90 degree, new negative x-axis is old y-axis and
  // new y-axis is old x-axis.
  if ((fabs(-pickup_y - msg->pose.pose.position.x) < threshold) &&
      (fabs(pickup_x - msg->pose.pose.position.y) < threshold)) {
    reached_pickup = true;
    // Hide marker
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ros::Duration(5).sleep();
  }
  if (reached_pickup && 
      (fabs(-dropoff_y - msg->pose.pose.position.x) < threshold) &&
      (fabs(dropoff_x - msg->pose.pose.position.y) < threshold)) {
    reached_dropoff = true;
    // Set marker at drop off zone
    marker.pose.position.x = dropoff_x;
    marker.pose.position.y = dropoff_y;
    marker.pose.orientation.w = dropoff_w;

    // Publish the marker at the drop off zone
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
  }
}

int main( int argc, char** argv ) {
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1); marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 1000, odom_callback);

  while (!ros::ok()) { }
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;

  marker.type = visualization_msgs::Marker::CUBE;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = pickup_x;
  marker.pose.position.y = pickup_y; 
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.1;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  // Publish the marker 
  while (marker_pub.getNumSubscribers() < 1) {
    if (!ros::ok()) {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  marker_pub.publish(marker);

  ros::spin();
}

