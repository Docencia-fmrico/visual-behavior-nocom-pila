#include <string>

#include "fsm_visual_behavior/Perceive_person.h"

#include "ros/ros.h"

namespace fsm_visual_behavior
{

Perceive_person::Perceive_person(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  //vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void
Perceive_person::halt()
{
    ROS_INFO("Perceive_person halt");
}

BT::NodeStatus
Perceive_person::tick()
{
    ROS_INFO("Perceive_person tick");

   

    return BT::NodeStatus::SUCCESS;
}
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Perceive_person>("Perceive_person");
}