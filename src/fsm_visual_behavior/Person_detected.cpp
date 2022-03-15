#include "fsm_visual_behavior/Person_detected.h"
#include "behaviortree_cpp_v3/behavior_tree.h"



namespace fsm_visual_behavior
{

Person_detected::Person_detected(const std::string& name)
: BT::ActionNodeBase(name, {}), counter_(0)
{
  vel_pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  //sub_darknet_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &Person_detected::tick, this);
  
}

void
Person_detected::halt()
{
    ROS_INFO("Person_detected halt");
}

BT::NodeStatus
Person_detected::tick()
{
    ROS_INFO("Person_detected tick");

    geometry_msgs::Twist msg;
    msg.angular.z = TURNING_SPEED;
    vel_pub_.publish(msg);
    const darknet_ros_msgs::BoundingBoxesConstPtr boxes;
    
    for (const auto & box : boxes->bounding_boxes) {
    int px = (box.xmax + box.xmin) / 2;
    int py = (box.ymax + box.ymin) / 2;

    //float dist = img_ptr_depth->image.at<float>(cv::Point(px, py)) * 0.001f;
    //std::cerr << box.Class << " at (" << dist << std::endl;
    if(box.Class == "person")
    {return BT::NodeStatus::SUCCESS;}
    else{

      return BT::NodeStatus::FAILURE;
    }
  }

    
}

}  // namespace fsm_visual_behavior

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<fsm_visual_behavior::Person_detected>("Person_detected");
}
