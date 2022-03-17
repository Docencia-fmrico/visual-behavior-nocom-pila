#ifndef BEHAVIOR_TREES_FOLLOW_BALL_H
#define BEHAVIOR_TREES_FOLLOW_BALL_H

#include "ros/ros.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/Image.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"

#include <string>

namespace fsm_visual_behavior
{

class Follow_ball : public BT::ActionNodeBase
{
public:
    explicit Follow_ball(const std::string& name);

    void halt();

    BT::NodeStatus tick();
    void PointCallbackBall(const std_msgs::Float64::ConstPtr& msg);
    void PointPxCallbackBall(const std_msgs::Int64::ConstPtr& msg);

private:
    const float ADVANCE_SPEED = 0.1;
    const float TURNING_SPEED = 0.35;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;
    ros::Subscriber dist_point_ball;
    ros::Subscriber px_point_ball;

    float dist;
    int point;
    int counter_;
};

}

#endif // BEHAVIOR_TREES_FOLLOW_BALL_H