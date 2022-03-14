#include <string>

#include "fsm_visual_behavior/Turn.h"

#include "ros/ros.h"

namespace behavior_trees
{

Turn::Turn(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void
Turn::halt()
{
    ROS_INFO("Turn halt");
}

BT::NodeStatus
Turn::tick()
{
    ROS_INFO("Turn tick");

    geometry_msgs::Twist msg;
    msg.angular.z = TURNING_SPEED;
    vel_pub_.publish(msg);

    ROS_INFO("Turning");

    return BT::NodeStatus::RUNNING;
}
}