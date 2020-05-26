#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>


void PrintMarkerPosition(const visualization_msgs::Marker& marker) {
    if (marker.type != visualization_msgs::Marker::TEXT_VIEW_FACING)
        return;

    geometry_msgs::Point position;
    position = marker.pose.position;

    ROS_INFO("text.x is %f, text.y is %f, text.z is%f\n", position.x, position.y, position.z);
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "print_received_marker");

    ros::NodeHandle nh;
    ros::Subscriber marker_sub = nh.subscribe("obj_marker", 100, PrintMarkerPosition);

    ros::spin();

    return 0;
}
