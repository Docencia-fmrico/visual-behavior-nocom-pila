#include "fsm_visual_behavior/Person_detected.h"
#include "behaviortree_cpp_v3/behavior_tree.h"

#include "ros/ros.h"
#include "std_msgs/Bool.h"

namespace fsm_visual_behavior
{

Person_detected::Person_detected(const std::string& name)
: BT::ActionNodeBase(name, {}), person_(false)
{
  if_person_ = nh_.subscribe("/person_detected", 1, &Person_detected::PersonCallback, this);
}

void
Person_detected::halt()
{
    ROS_INFO("Person_detected halt");
}

BT::NodeStatus
Person_detected::tick()
{
    ROS_INFO("Person_detected tick");

    if(person_)
    {
    ROS_INFO("SUCCESS");
      return BT::NodeStatus::SUCCESS;
    }
    else
    {
    ROS_INFO("FAILURE");
      return BT::NodeStatus::FAILURE;
    }
  }

void 
Person_detected::PersonCallback(const std_msgs::Bool::ConstPtr& msg)
{
  person_ = msg->data; //std_msgs::Bool::data; // Updates the variable "person_"
}

}  // namespace fsm_visual_behavior



#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Person_detected>("Person_detected");
}