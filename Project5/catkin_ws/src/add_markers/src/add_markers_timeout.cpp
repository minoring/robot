#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv ) {
  ros::init(argc, argv, "add_markers_timeout");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  while (!ros::ok()) { }
  visualization_msgs::Marker marker;
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
  marker.pose.position.x = -1.0;
  marker.pose.position.y = -1.0;
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

  // Pause 5 seconds
  ros::Duration(5).sleep();

  // Hide marker
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
  ros::Duration(5).sleep();

  // Set marker at drop off zone
  marker.pose.position.x = -2.0;
  marker.pose.position.y = -2.0;
  marker.pose.orientation.w = 1.0;

  // Publish the marker at the drop off zone
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);

  ros::spin();
 
}

