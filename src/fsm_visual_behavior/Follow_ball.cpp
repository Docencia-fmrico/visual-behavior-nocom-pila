#include <string>

#include "fsm_visual_behavior/Follow_ball.h"

#include "ros/ros.h"

namespace fsm_visual_behavior
{

Follow_ball::Follow_ball(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0), turn_pid_(MIN_RANG_BOX, MAX_RANG_BOX, MIN_TURN_SPEED, MAX_TURN_SPEED), forw_pid_(MIN_FORW_DIST, MAX_FORW_DIST, MIN_FORW_SPEED, MAX_FORW_SPEED), back_pid_(MIN_BACKW_DIST, MAX_BACKW_DIST, - MIN_FORW_SPEED, - MAX_FORW_SPEED)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  dist_point_ball = n_.subscribe("/dist_ball", 1, &Follow_ball::PointCallbackBall, this);
  px_point_ball = n_.subscribe("/px_ball", 1, &Follow_ball::PointPxCallbackBall, this);
}

void
Follow_ball::halt()
{
    ROS_INFO("Follow_ball halt");
}

void 
Follow_ball::PointCallbackBall(const std_msgs::Float64::ConstPtr& msg)
{
  //if(msg->data != 0)
  //{
    dist = msg->data;
    std::cerr << dist << std::endl; 
  //}
}

void Follow_ball::PointPxCallbackBall(const std_msgs::Int64::ConstPtr& msg)
{/*
  if(msg->data != 0)
  {
    point = msg->data;
    std::cerr << point << std::endl;
  }*/
}

BT::NodeStatus
Follow_ball::tick()
{
    ROS_INFO("Follow_ball tick");
    double veloc = forw_pid_.get_output(dist);

    //std::cerr << dist << std::endl;

    geometry_msgs::Twist msg;

    ROS_INFO("vel x= ");
    std::cerr << veloc << std::endl; 

    /*
    if(0.5 < dist < 2.5)
    {
      if(point < 250)
      {
        msg.linear.x = ADVANCE_SPEED;
        msg.angular.z = TURNING_SPEED;
      }
      if( 250 <= point <= 350)
      {
        msg.linear.x = ADVANCE_SPEED;
        //msg.angular.z = TURNING_SPEED;
      }
      if(point > 350)
      {
        msg.linear.x = ADVANCE_SPEED;
        msg.angular.z = - TURNING_SPEED;
      }
      
    }*/
    
    

    vel_pub_.publish(msg);

    return BT::NodeStatus::RUNNING;
}
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Follow_ball>("Follow_ball");
}