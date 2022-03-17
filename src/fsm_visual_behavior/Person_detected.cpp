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

#include "fsm_visual_behavior/Person_detected.h"
#include "behaviortree_cpp_v3/behavior_tree.h"

#include <string>
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

  if (person_)
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
  person_ = msg->data;  // std_msgs::Bool::data; Updates the variable "person_"
}

}  // namespace fsm_visual_behavior



#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Person_detected>("Person_detected");
}
