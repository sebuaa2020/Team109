#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
  ros::init(argc, argv, "demo_simple_goal");
  MoveBaseClient ac("move_base", true);
  int test = 0;
  while(!ac.waitForServer(ros::Duration(5.0))) {
	  if (test == 0) {
		  printf("test1 finish\n")
	  }
	  test++;
  } 
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = -3.0;
  goal.target_pose.pose.position.y = 2.0;
  goal.target_pose.pose.orientation.w = 1.0;
  ac.sendGoal(goal);
  ac.waitForResult();
  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
	  printf("test2 finish\n")
  }
  else {
	  printf("test3 finish\n")
  }

  return 0;
}
