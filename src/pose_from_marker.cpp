#include "pose_from_marker.h"


PoseFromMarker::PoseFromMarker(ros::NodeHandle nh, int numberOfGoals, int init_marker_id):
 ac("move_base", true),
 numberOfGoals(numberOfGoals),
 nh_(nh),
 marker_id(init_marker_id)
{
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = 0.0;
  goal.target_pose.pose.position.y = 0.0;
  goal.target_pose.pose.position.z = 0.0;

  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.0;
  goal.target_pose.pose.orientation.w = 1.0;
}


void PoseFromMarker::publishGoals_cb(const geometry_msgs::PoseStamped& pose_msg)
{
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server");
  }

  goal.target_pose.pose.position.x = pose_msg.pose.position.x;
  goal.target_pose.pose.position.y = pose_msg.pose.position.y;

  ac.sendGoal(goal);
  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Goal reached");
  }
  else
  {
    ROS_INFO("Goal cannot be reached");
  }
}

void PoseFromMarker::rotate_behaviour()
{

   tf::TransformListener tf(ros::Duration(10));
   costmap_2d::Costmap2DROS global_costmap("global_costmap", tf);
   costmap_2d::Costmap2DROS local_costmap("local_costmap", tf);
    
    rotate_recovery::RotateRecovery rr;
    rr.initialize("my_rotate_recovery", &tf, &global_costmap, &local_costmap);
   
    rr.runBehavior();
}

void PoseFromMarker::getPose()
{
   
  ROS_INFO("waiting for aruco_marker to publish pose...");
  while(numberOfGoals != 0)
  { 
    // set desired marker id
    nh_.setParam("/aruco_simple/marker_id", marker_id);
    pose_sub = nh_.subscribe("/aruco_simple/pose", 100, &PoseFromMarker::publishGoals_cb, this);

    //intiate rotate behaviour
    //rotate_behaviour();
    
    numberOfGoals = numberOfGoals - 1;
    marker_id = marker_id + 1;

    std::cout << "goals left: " << numberOfGoals << std::endl;
  }
  
  
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "get_pose");
  ros::NodeHandle node_handle("~");
  
  int numberOfTargets = 3;
  int id = 0;  

  PoseFromMarker poseFromMarker(node_handle, numberOfTargets, id);

  poseFromMarker.getPose();

  ros::spin();

  return 0;
}
