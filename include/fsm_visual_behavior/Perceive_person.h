#ifndef BEHAVIOR_TREES_PERCEIVE_PERSON_H
#define BEHAVIOR_TREES_PERCEIVE_PERSON_H

#include "ros/ros.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"

#include <string>

namespace fsm_visual_behavior
{

class Perceive_person : public BT::ActionNodeBase
{
public:
    explicit Perceive_person(const std::string& name);

    void halt();

    BT::NodeStatus tick();

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;

    int counter_;
};

}

#endif // BEHAVIOR_TREES_PERCEIVE_PERSON_H