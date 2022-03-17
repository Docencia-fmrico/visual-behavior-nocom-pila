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

#include "fsm_visual_behavior/Ball_detected.h"
#include "behaviortree_cpp_v3/behavior_tree.h"

#include <string>
#include "ros/ros.h"
#include "std_msgs/Bool.h"

namespace fsm_visual_behavior
{

Ball_detected::Ball_detected(const std::string& name)
: BT::ActionNodeBase(name, {}), ball_(false)
{
  if_ball_ = nh_.subscribe("/ball_detected", 1, &Ball_detected::BallCallback, this);
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

  if (ball_)
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
Ball_detected::BallCallback(const std_msgs::Bool::ConstPtr& msg)
{
  ball_ = msg->data;  // std_msgs::Bool::data; Updates the variable "ball_"
}

}  // namespace fsm_visual_behavior


#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Ball_detected>("Ball_detected");
}
