#include "goto_goal_pose.h"
#include <aruco_ros/aruco_ros_utils.h>
#include <aruco_ros/ArucoThresholdConfig.h>
#include <aruco_ros/aruco_simple.h>
int main(int argc, char** argv)
{
	ros::init(argc, argv, "aruco_simple");
	ros::NodeHandle node_handle("~");

	node_handle.setParam("camera_frame", "/camera_rgb_optical_frame");
	node_handle.setParam("marker_frame", "/turtle_frame");
	// node_handle.setParam("marker_id", 0);
	node_handle.setParam("marker_size", 0.18);
	node_handle.setParam("useRectifiedImages", true);
	node_handle.setParam("reference_frame", "/odom");


	ArucoSimple aru_simple;
	ros::spin();

	return 0;
}
