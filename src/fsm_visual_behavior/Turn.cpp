#include <string>

#include "behavior_trees/CheckBattery.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

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
    turn_ts_ = ros::Time::now();

    geometry_msgs::Twist msg;
    msg.angular.z = 0.35;
    vel_pub_.publish(msg);

    ROS_INFO("Turning");

    return BT::NodeStatus::RUNNING;
}