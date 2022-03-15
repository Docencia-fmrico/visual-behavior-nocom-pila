#ifndef BEHAVIOR_TREES_PERSON_DETECTED_H
#define BEHAVIOR_TREES_PERSON_DETECTED_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"

namespace fsm_visual_behavior
{

class Person_detected : public BT::ActionNodeBase
{
public:
    explicit Person_detected(const std::string& name);

    void halt();

    BT::NodeStatus tick();

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;

    int counter_;
};


}  // namespace fsm_visual_behavior

#endif  // BEHAVIOR_TREES_Person_detected_H
