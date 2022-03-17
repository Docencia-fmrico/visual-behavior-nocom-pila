#include "fsm_visual_behavior/Perceive_ball.h"
#include "behaviortree_cpp_v3/behavior_tree.h"

#include "ros/ros.h"
#include "std_msgs/Float64.h"

namespace fsm_visual_behavior
{

Perceive_ball::Perceive_ball(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  dist_sub = nh_.subscribe("/dist_ball", 1, &Perceive_ball::PerceiveBallCallback, this);
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

    std::cerr << dist << std::endl;

    return BT::NodeStatus::SUCCESS;
}

void 
Perceive_ball::PerceiveBallCallback(const std_msgs::Float64::ConstPtr& msg)
{
  dist = msg->data;
}

}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Perceive_ball>("Perceive_ball");
}