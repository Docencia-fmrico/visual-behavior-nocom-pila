#ifndef BEHAVIOR_TREES_PERCEIVE_BALL_H
#define BEHAVIOR_TREES_PERCEIVE_BALL_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>
#include "ros/ros.h"

#include <sensor_msgs/Image.h>
#include "std_msgs/Float64.h"


namespace fsm_visual_behavior
{

class Perceive_ball : public BT::ActionNodeBase
{
public:
    explicit Perceive_ball(const std::string& name);

    void halt();

    BT::NodeStatus tick();

    void PerceiveBallCallback(const std_msgs::Float64::ConstPtr& msg);

private:
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle nh_;
    ros::Subscriber dist_sub;

    float dist;
    int counter_;
};

}


#endif // BEHAVIOR_TREES_PERCEIVE_BALL_H