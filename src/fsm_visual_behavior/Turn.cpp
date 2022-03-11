#include <string>

#include "fsm_visual_behavior/Turn.h"

#include "ros/ros.h"

namespace behavior_trees
{

Turn::Turn(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
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
    msg.angular.z = 0.35;
    vel_pub_.publish(msg);

    ROS_INFO("Turning");

    return BT::NodeStatus::RUNNING;
}
}