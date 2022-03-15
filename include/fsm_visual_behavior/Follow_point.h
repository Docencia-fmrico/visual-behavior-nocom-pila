#ifndef BEHAVIOR_TREES_FOLLOW_POINT_H
#define BEHAVIOR_TREES_FOLLOW_POINT_H

#include "ros/ros.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"

#include <string>

namespace fsm_visual_behavior
{

class Follow_point : public BT::ActionNodeBase
{
public:
    explicit Follow_point(const std::string& name);

    void halt();

    BT::NodeStatus tick();

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;

    int counter_;
};

}

#endif // BEHAVIOR_TREES_FOLLOW_POINT_H