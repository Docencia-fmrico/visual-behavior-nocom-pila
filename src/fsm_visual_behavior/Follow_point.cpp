#include <string>

#include "fsm_visual_behavior/Follow_point.h"

#include "ros/ros.h"

namespace fsm_visual_behavior
{

Follow_point::Follow_point(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void
Follow_point::halt()
{
    ROS_INFO("Follow_point halt");
}

BT::NodeStatus
Follow_point::tick()
{
    ROS_INFO("Follow_point tick");

    geometry_msgs::Twist msg;
    msg.angular.z = TURNING_SPEED;
    vel_pub_.publish(msg);

   

    return BT::NodeStatus::RUNNING;
}
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Follow_point>("Follow_point");
}