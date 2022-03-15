#ifndef BEHAVIOR_TREES_BALL_DETECTED_H
#define BEHAVIOR_TREES_BALL_DETECTED_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"

namespace fsm_visual_behavior
{

class Ball_detected : public BT::ActionNodeBase
{
public:
    explicit Ball_detected(const std::string& name);

    void halt();

    BT::NodeStatus tick();

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;

    int counter_;
};


}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_BALL_DETECTED_H
