#ifndef GOAL_GENERATOR_H
#define GOAL_GENERATOR_H


#include <iostream>
#include <random>

#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


class GoalGenerator
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
  GoalGenerator(ros::NodeHandle, int a, int grid_x, int grid_y);
  MoveBaseClient ac;

  void publishGoals();

  bool setGoal(float a , float b);

  float randomPoseGenerator();

 private:
  
  
  //MoveBaseClient ac;

  
  
  move_base_msgs::MoveBaseGoal goal;
  
  

  int numberOfGoals; 
  int size_x; 
  int size_y;
 
  //! ROS node handle.
  ros::NodeHandle nh_;

 

};


#endif  