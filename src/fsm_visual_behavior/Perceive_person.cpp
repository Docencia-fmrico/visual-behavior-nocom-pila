#include "fsm_visual_behavior/Perceive_person.h"
#include "behaviortree_cpp_v3/behavior_tree.h"

#include "ros/ros.h"
#include "std_msgs/Float64.h"

namespace fsm_visual_behavior
{

Perceive_person::Perceive_person(const std::string& name, const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config), counter_(0)
{
  dist_sub = nh_.subscribe("/dist_person", 1, &Perceive_person::PerceivePersonCallback, this);
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

    setOutput<std::string>("person", "hola");

    std::cerr << dist << std::endl;

    return BT::NodeStatus::SUCCESS;
}

void 
Perceive_person::PerceivePersonCallback(const std_msgs::Float64::ConstPtr& msg)
{
  dist = msg->data;
}

}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Perceive_person>("Perceive_person");
}