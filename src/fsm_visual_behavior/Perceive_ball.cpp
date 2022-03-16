#include <string>

#include "fsm_visual_behavior/Perceive_ball.h"

#include "ros/ros.h"

namespace fsm_visual_behavior
{

Perceive_ball::Perceive_ball(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  //vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void
Perceive_ball::halt()
{
    ROS_INFO("Perceive_ball halt");
}

BT::NodeStatus
Perceive_ball::tick()
{
    ROS_INFO("Perceive_ball tick");

    

    return BT::NodeStatus::SUCCESS;
}
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Perceive_ball>("Perceive_ball");
}