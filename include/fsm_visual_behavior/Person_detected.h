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

#ifndef FSM_VISUAL_BEHAVIOR_PERSON_DETECTED_H
#define FSM_VISUAL_BEHAVIOR_PERSON_DETECTED_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>
#include "ros/ros.h"

#include <sensor_msgs/Image.h>
#include "std_msgs/Bool.h"
#include <darknet_ros_msgs/BoundingBoxes.h>

namespace fsm_visual_behavior
{

class Person_detected : public BT::ActionNodeBase
{
public:
    explicit Person_detected(const std::string& name);

    void halt();

    BT::NodeStatus tick();

    void PersonCallback(const std_msgs::Bool::ConstPtr& msg);

private:
    ros::NodeHandle nh_;
    ros::Subscriber if_person_;

    bool person_;
};


}  // namespace fsm_visual_behavior

#endif  // FSM_VISUAL_BEHAVIOR_PERSON_DETECTED_H
