// Copyright 2022 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include "fsm_visual_behavior/Turn.h"
#include "ros/ros.h"

namespace fsm_visual_behavior
{

Turn::Turn(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
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

  return BT::NodeStatus::RUNNING;
}

}  // namespace fsm_visual_behavior

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Turn>("Turn");
}
