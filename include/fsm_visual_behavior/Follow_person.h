#ifndef BEHAVIOR_TREES_FOLLOW_PERSON_H
#define BEHAVIOR_TREES_FOLLOW_PERSON_H

#include "ros/ros.h"
#include "fsm_visual_behavior/PIDController.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/Image.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"

#include <string>

namespace fsm_visual_behavior
{

class Follow_person : public BT::ActionNodeBase
{
public:
    explicit Follow_person(const std::string& name);

    void halt();

    BT::NodeStatus tick();
    void PointCallbackPerson(const std_msgs::Float64::ConstPtr& msg);
    void PointPxCallbackPerson(const std_msgs::Int64::ConstPtr& msg);
    
private:
    const double MIN_TURN_SPEED = 0.0;
    const double MAX_TURN_SPEED = 0.4;
    const double MIN_RANG_BOX = -300;
    const double MAX_RANG_BOX = 300;
    const double MIN_FORW_SPEED = 0.0;
    const double MAX_FORW_SPEED = 0.2;
    const double MIN_FORW_DIST = 1;
    const double MAX_FORW_DIST = 2.5;
    const double MIN_BACKW_DIST = 0.1;
    const double MAX_BACKW_DIST = 1;

    const float MIN_TURNING_SPEED = 0.05;
    const float MAX_TURNING_SPEED = 0.45;

    ros::NodeHandle n_;
    ros::Publisher vel_pub_;
    ros::Subscriber dist_point_person;
    ros::Subscriber px_point_person;

    float dist, pos;
    PIDController turn_pid_, forw_pid_, back_pid_;
    int point;
    int counter_;

};

}

#endif // BEHAVIOR_TREES_FOLLOW_PERSON_H