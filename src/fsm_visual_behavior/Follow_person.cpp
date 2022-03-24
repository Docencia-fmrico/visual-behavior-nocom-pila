#include <string>

#include "fsm_visual_behavior/Follow_person.h"

#include "ros/ros.h"

namespace fsm_visual_behavior
{

Follow_person::Follow_person(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0), turn_pid_(MIN_RANG_BOX, MAX_RANG_BOX, MIN_TURN_SPEED, MAX_TURN_SPEED), forw_pid_(MIN_FORW_DIST, MAX_FORW_DIST, MIN_FORW_SPEED, MAX_FORW_SPEED), back_pid_(MIN_BACKW_DIST, MAX_BACKW_DIST, - MIN_FORW_SPEED, - MAX_FORW_SPEED)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  dist_point_person = n_.subscribe("/dist_person", 1, &Follow_person::PointCallbackPerson, this);
  px_point_person = n_.subscribe("/px_person", 1, &Follow_person::PointPxCallbackPerson, this);
}

void
Follow_person::halt()
{
    ROS_INFO("Follow_person halt");
}

void 
Follow_person::PointCallbackPerson(const std_msgs::Float64::ConstPtr& msg)
{
  dist = msg->data;
  std::cerr << dist << std::endl;

}
void Follow_person::PointPxCallbackPerson(const std_msgs::Int64::ConstPtr& msg)
{
/*
  point = msg->data;
  std::cerr << point << std::endl;*/
}

BT::NodeStatus
Follow_person::tick()
{
    ROS_INFO("Follow_person tick");
    //double f_veloc = forw_pid_.get_output(dist);
    //double a_veloc = forw_pid_.get_output(dist);

    ROS_INFO("vel x= ");
    //std::cerr << veloc << std::endl; 
    
    geometry_msgs::Twist msg;

    //msg.linear.x = veloc;
    //msg.angular.z = TURNING_SPEED;
    
    

    vel_pub_.publish(msg);

    return BT::NodeStatus::RUNNING;
}
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Follow_person>("Follow_person");
}