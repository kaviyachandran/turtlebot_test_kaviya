#ifndef POSE_FROM_MARKER_H
#define POSE_FROM_MARKER_H


#include <iostream>
#include <random>

#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <pcl/point_types.h>
#include <aruco_ros/aruco_simple.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <rotate_recovery/rotate_recovery.h>


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


class PoseFromMarker
{
 public:

  struct Position
    {
        float x;
        float y;
    };

  Position randomPose;

  float environment_size_max;
  float environment_size_min;

  // Constructor.
  PoseFromMarker(ros::NodeHandle, int a, int b);
  MoveBaseClient ac;

  void getPose();

  void publishGoals_cb(const geometry_msgs::PoseStamped&);

 void rotate_behaviour();

 private:
  
  
  //MoveBaseClient ac;

  ros::Subscriber pose_sub;
  
  move_base_msgs::MoveBaseGoal goal;
  
  
  int numberOfGoals; 
  int marker_id; 
  
  
  //! ROS node handle.
  ros::NodeHandle nh_;

  

};


#endif  