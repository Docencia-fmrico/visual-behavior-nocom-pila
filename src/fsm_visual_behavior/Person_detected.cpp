#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/Image.h>
#include <darknet_ros_msgs/BoundingBoxes.h>



void callback_bbx(const sensor_msgs::ImageConstPtr& image, const darknet_ros_msgs::BoundingBoxesConstPtr& boxes)
{

  cv_bridge::CvImagePtr img_ptr_depth;

  try{
      img_ptr_depth = cv_bridge::toCvCopy(*image, sensor_msgs::image_encodings::TYPE_32FC1);
  }
  catch (cv_bridge::Exception& e)
  {
      ROS_ERROR("cv_bridge exception:  %s", e.what());
      return;
  }
  
  for (const auto & box : boxes->bounding_boxes) {
    if(box.Class == "person")
    {
      int px = (box.xmax + box.xmin) / 2;
      int py = (box.ymax + box.ymin) / 2;

      float dist = img_ptr_depth->image.at<float>(cv::Point(px, py)) * 0.001f;
      std::cerr << box.Class << " at (" << dist << "," << px * 0.001f << "," << py * 0.001f << ")"<<std::endl;
      std::cerr << "Centro: "<<(px+py)/2 * 0.001f <<std::endl;
    }
    
  }

}

