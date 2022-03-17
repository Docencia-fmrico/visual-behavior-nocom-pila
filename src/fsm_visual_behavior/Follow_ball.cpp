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
#include "fsm_visual_behavior/Follow_ball.h"
#include "ros/ros.h"

namespace fsm_visual_behavior
{

Follow_ball::Follow_ball(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  dist_point_ball = n_.subscribe("/dist_ball", 1, &Follow_ball::PointCallbackBall, this);
  px_point_ball = n_.subscribe("/px_ball", 1, &Follow_ball::PointPxCallbackBall, this);
}

void
Follow_ball::halt()
{
    ROS_INFO("Follow_ball halt");
}

void
Follow_ball::PointCallbackBall(const std_msgs::Float64::ConstPtr& msg)
{
  if (msg->data != 0)
  {
    dist = msg->data;
    std::cerr << dist << std::endl;
  }
}

void Follow_ball::PointPxCallbackBall(const std_msgs::Int64::ConstPtr& msg)
{
  if (msg->data != 0)
  {
    point = msg->data;
    std::cerr << point << std::endl;
  }
}

BT::NodeStatus
Follow_ball::tick()
{
  ROS_INFO("Follow_ball tick");

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
  factory.registerNodeType<fsm_visual_behavior::Follow_ball>("Follow_ball");
}
