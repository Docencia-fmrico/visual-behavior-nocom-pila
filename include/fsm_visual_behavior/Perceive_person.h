#ifndef BEHAVIOR_TREES_PERCEIVE_PERSON_H
#define BEHAVIOR_TREES_PERCEIVE_PERSON_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "fsm_visual_behavior/PIDController.hpp"

#include <string>
#include "ros/ros.h"

#include <sensor_msgs/Image.h>
#include "std_msgs/Float64.h"


namespace fsm_visual_behavior
{

class Perceive_person : public BT::ActionNodeBase
{
public:
    explicit Perceive_person(const std::string& name);

    void halt();

    BT::NodeStatus tick();

    void PerceivePersonCallback(const std_msgs::Float64::ConstPtr& msg);

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle nh_;
    ros::Subscriber dist_sub;

    float dist;
    int counter_;
    PIDController pid1_;
};

}

#endif // BEHAVIOR_TREES_PERCEIVE_PERSON_H