#ifndef BEHAVIOR_TREES_TURN_H
#define BEHAVIOR_TREES_TURN_H

#include "ros/ros.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include <string>

namespace fsm_visual_behavior
{

class Turn : public BT::ActionNodeBase
{
public:
    explicit Turn(const std::string& name);

    void halt();

    BT::NodeStatus tick();

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;

    int counter_;
};

}

#endif // BEHAVIOR_TREES_TURN_H