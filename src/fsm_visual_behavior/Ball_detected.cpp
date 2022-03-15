#include <string>

#include "fsm_visual_behavior/Ball_detected.h"

#include "behaviortree_cpp_v3/behavior_tree.h"

#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

namespace fsm_visual_behavior
{

Ball_detected::Ball_detected(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void
Ball_detected::halt()
{
    ROS_INFO("Ball_detected halt");
}

BT::NodeStatus
Ball_detected::tick()
{
    ROS_INFO("Ball_detected tick");

    geometry_msgs::Twist msg;
    msg.angular.z = TURNING_SPEED;
    vel_pub_.publish(msg);

    

    return BT::NodeStatus::SUCCESS;
}

}  // namespace fsm_visual_behavior

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Ball_detected>("Ball_detected");
}
