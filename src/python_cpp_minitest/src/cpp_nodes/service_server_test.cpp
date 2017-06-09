#include <iostream>

#include <playground_msgs/CompareGtDouble.h>
#include <playground_msgs/Flt64.h>
#include <ros/ros.h>

bool compare(playground_msgs::CompareGtDouble::Request &req,
	     playground_msgs::CompareGtDouble::Response &res) {
  double a = static_cast<double>(req.value1.data);
  double b = static_cast<double>(req.value2.data);
  std::cout << "Is " << a << " >= " << b << " ?" << std::endl;
  res.greater = static_cast<bool>(a >= b);
  // Note that greater is a 'bool', not a 'Bool', thus we do not request
  // greater.data
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "comparison_server");
  ros::NodeHandle nh;

  ros::ServiceServer server = nh.advertiseService("compare_gt_double", compare);

  ROS_INFO("Service server is ready");
  ros::spin();

  return 0;
};
