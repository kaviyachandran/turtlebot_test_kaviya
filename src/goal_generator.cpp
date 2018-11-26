#include "goal_generator.h"


GoalGenerator::GoalGenerator(ros::NodeHandle nh, int numberOfGoals, int size_x, int size_y):
 ac("move_base", true),
 numberOfGoals(numberOfGoals)
{
  
  environment_size_min = size_x;
  environment_size_max = size_y;
  
  ros::NodeHandle nh_ = nh;

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

float GoalGenerator::randomPoseGenerator()
{
  std::random_device random_val;
  std::mt19937 mt(random_val());
  std::uniform_real_distribution<double> dist(environment_size_min+1.0,environment_size_max-1.0);

  return dist(mt);
}



bool GoalGenerator::setGoal(float x, float y)
{ 
  
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;

  ROS_INFO("Sending goal");
  
  ac.sendGoal(goal);
  ac.waitForResult();

  bool goalReached = false;

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    goalReached = true;
  }
 
  return goalReached;

}

void GoalGenerator::publishGoals()
{
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server");
  }
  
  while(numberOfGoals != 0)
  {
    randomPose.x = randomPoseGenerator();
    randomPose.y = randomPoseGenerator();

    if(setGoal(randomPose.x, randomPose.y))
    { 
      numberOfGoals = numberOfGoals - 1;
    }

    std::cout << "goals left: " << numberOfGoals << std::endl;
  }
  
  ROS_INFO("Task Completed");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "goto_node");
  ros::NodeHandle node_handle("~");
  
  int numberOfTargets = 3;
  
  float env_min = -5.0;
  float env_max = 5.0;

  GoalGenerator goalGenerator(node_handle, numberOfTargets, env_min, env_max);

  goalGenerator.publishGoals();

  ros::spin();

  return 0;
}
