#ifndef BEHAVIOR_TREES_PERSON_DETECTED_H
#define BEHAVIOR_TREES_PERSON_DETECTED_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>
#include "ros/ros.h"

#include <sensor_msgs/Image.h>
#include "std_msgs/Bool.h"
#include <darknet_ros_msgs/BoundingBoxes.h>

namespace fsm_visual_behavior
{

class Person_detected : public BT::ActionNodeBase
{
public:
    explicit Person_detected(const std::string& name);

    void halt();

    BT::NodeStatus tick();

    void PersonCallback(const std_msgs::Bool::ConstPtr& msg);
private:

    ros::NodeHandle nh_;
    ros::Subscriber if_person_;

    bool person_;
};


}  // namespace fsm_visual_behavior

#endif  // BEHAVIOR_TREES_Person_detected_H