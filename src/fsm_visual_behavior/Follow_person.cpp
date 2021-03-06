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
#include "fsm_visual_behavior/Follow_person.h"
#include "ros/ros.h"

namespace fsm_visual_behavior
{

Follow_person::Follow_person(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  dist_point_person = n_.subscribe("/dist_person", 1, &Follow_person::PointCallbackPerson, this);
  px_point_person = n_.subscribe("/px_person", 1, &Follow_person::PointPxCallbackPerson, this);
}

void
Follow_person::halt()
{
    ROS_INFO("Follow_person halt");
}

void
Follow_person::PointCallbackPerson(const std_msgs::Float64::ConstPtr& msg)
{
  dist = msg->data;
  std::cerr << dist << std::endl;
}

void Follow_person::PointPxCallbackPerson(const std_msgs::Int64::ConstPtr& msg)
{
  point = msg->data;
  std::cerr << point << std::endl;
}

BT::NodeStatus
Follow_person::tick()
{
  ROS_INFO("Follow_person tick");

  // std::cerr << dist << std::endl;

  geometry_msgs::Twist msg;

  if (0.75 < dist < 2.5)
  {
    if (point < 250)
    {
      msg.linear.x = ADVANCE_SPEED;
      msg.angular.z = TURNING_SPEED;
    }
    if (250 <= point <= 350)
    {
      msg.linear.x = ADVANCE_SPEED;
    }
    if (point > 350)
    {
      msg.linear.x = ADVANCE_SPEED;
      msg.angular.z = -TURNING_SPEED;
    }
  }

  if (0.75 > dist)
  {
    if (point < 250)
    {
      msg.linear.x = -ADVANCE_SPEED;
      msg.angular.z = -TURNING_SPEED;
    }
    if (250 <= point <= 350)
    {
      msg.linear.x = -ADVANCE_SPEED;
    }
    if (point > 350)
    {
      msg.linear.x = -ADVANCE_SPEED;
      msg.angular.z = TURNING_SPEED;
    }
  }

  vel_pub_.publish(msg);

  return BT::NodeStatus::RUNNING;
}

}  // namespace fsm_visual_behavior

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Follow_person>("Follow_person");
}
