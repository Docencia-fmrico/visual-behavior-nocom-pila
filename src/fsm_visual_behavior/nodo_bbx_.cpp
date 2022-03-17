#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/Image.h>
#include <darknet_ros_msgs/BoundingBoxes.h>

#include "std_msgs/Bool.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int64.h"

void callback_bbx(const sensor_msgs::ImageConstPtr& image, const darknet_ros_msgs::BoundingBoxesConstPtr& boxes)
{
  ros::NodeHandle n;
  ros::Publisher if_person = n.advertise<std_msgs::Bool>("/person_detected", 1);
  ros::Publisher if_ball = n.advertise<std_msgs::Bool>("/ball_detected", 1);
  ros::Publisher dist_person = n.advertise<std_msgs::Float64>("/dist_person", 1);
  ros::Publisher dist_ball = n.advertise<std_msgs::Float64>("/dist_ball", 1);
  ros::Publisher px_person = n.advertise<std_msgs::Int64>("/px_person", 1);
  ros::Publisher px_ball = n.advertise<std_msgs::Int64>("/px_ball", 1);
  
  bool person = false;
  bool ball = false;
  float dist_b = 0; 
  float dist_p = 0;
  int px_p = 0; 
  int px_b = 0; 
  cv_bridge::CvImagePtr img_ptr_depth;
  std_msgs::Bool cmd_p;
  std_msgs::Float64 cmd_dist_p;
  std_msgs::Int64 cmd_px_p;

  std_msgs::Bool cmd_b;
  std_msgs::Float64 cmd_dist_b;
  std_msgs::Int64 cmd_px_b;
  

  try{
      img_ptr_depth = cv_bridge::toCvCopy(*image, sensor_msgs::image_encodings::TYPE_32FC1);
  }
  catch (cv_bridge::Exception& e)
  {
      ROS_ERROR("cv_bridge exception:  %s", e.what());
      return;
  }

  for (const auto & box : boxes->bounding_boxes) {
    int px = (box.xmax + box.xmin) / 2;
    int py = (box.ymax + box.ymin) / 2;

    float dist = img_ptr_depth->image.at<float>(cv::Point(px, py)) * 0.001f;
    //if (box.Class == "sports ball")
    //  std::cerr << box.Class << " at (" << dist << std::endl;

    if (box.Class == "sports ball" && dist <= 2.5 && dist != 0)
    {
      dist_b = dist;
      px_b = px;
      ball = true;
      ROS_INFO("HAY BALL");
      std::cerr << px << std::endl;
    }
    //if (box.Class == "person")
    //  std::cerr << box.Class << " at (" << dist << std::endl;

    if (box.Class == "person" && dist <= 2.5 && dist != 0)
    {
      dist_p = dist;
      px_p = px;
      person = true;
      ROS_INFO("HAY PERSONA");
      std::cerr << px << std::endl;
    }
  }
  cmd_p.data = person;
  cmd_b.data = ball;
  cmd_dist_b.data = dist_b;
  cmd_dist_p.data = dist_p;
  cmd_px_p.data = px_p;
  cmd_px_b.data = px_b;
  px_person.publish(cmd_px_p);
  px_ball.publish(cmd_px_b);
  if_person.publish(cmd_p);

  dist_person.publish(cmd_dist_p);
 
  if_ball.publish(cmd_b);

  dist_ball.publish(cmd_dist_b);

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vision_node");

  ros::NodeHandle nh;

  ros::Publisher if_person = nh.advertise<std_msgs::Bool>("/person_detected", 1);
  ros::Publisher if_ball = nh.advertise<std_msgs::Bool>("/ball_detected", 1);
  ros::Publisher dist_person = nh.advertise<std_msgs::Float64>("/dist_person", 1);
  ros::Publisher dist_ball = nh.advertise<std_msgs::Float64>("/dist_ball", 1);
  ros::Publisher px_person = nh.advertise<std_msgs::Int64>("/px_person", 1);
  ros::Publisher px_ball = nh.advertise<std_msgs::Int64>("/px_ball", 1);

  message_filters::Subscriber<sensor_msgs::Image> image_depth_sub(nh, "/camera/depth/image_raw", 1);
  message_filters::Subscriber<darknet_ros_msgs::BoundingBoxes> bbx_sub(nh, "/darknet_ros/bounding_boxes", 1);

  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, darknet_ros_msgs::BoundingBoxes> MySyncPolicy_bbx;
  message_filters::Synchronizer<MySyncPolicy_bbx> sync_bbx(MySyncPolicy_bbx(10), image_depth_sub, bbx_sub);

  sync_bbx.registerCallback(boost::bind(&callback_bbx, _1, _2));

  ros::spin();

  return 0;
}