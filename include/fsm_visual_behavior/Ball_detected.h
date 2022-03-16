#ifndef BEHAVIOR_TREES_BALL_DETECTED_H
#define BEHAVIOR_TREES_BALL_DETECTED_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>
#include "ros/ros.h"

#include <sensor_msgs/Image.h>
#include "std_msgs/Bool.h"
#include <darknet_ros_msgs/BoundingBoxes.h>

namespace fsm_visual_behavior
{

class Ball_detected : public BT::ActionNodeBase
{
public:
    explicit Ball_detected(const std::string& name);

    void halt();

    BT::NodeStatus tick();

    void BallCallback(const std_msgs::Bool::ConstPtr& msg);
private:

    ros::NodeHandle nh_;
    ros::Subscriber if_ball_;

    bool ball_;
};


}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_BALL_DETECTED_H




