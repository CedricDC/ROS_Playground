#include <functional>
#include "python_cpp_minitest/cpp_number_generator.h"

// ROS related inclues
#include <playground_msgs/CompareGtDouble.h>
#include <playground_msgs/Flt64.h>
#include <ros/ros.h>
#include <std_msgs/Float32.h>

void cpp_value_listener_cb(
    const boost::shared_ptr<std_msgs::Float32 const>& msg_ptr,
    float* return_value) {
  //std::cout << "Received new value " << msg_ptr->data << std::endl;
  if (return_value == nullptr) {
    ROS_ERROR("return value points to null!");
  } else {
  ROS_INFO("Received new value");
    *return_value = msg_ptr->data;
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "comparison_client");

  ros::NodeHandle nh;

  ros::Rate loop_rate(0.25);

  float topic_value = 0.0f;

  // using std::function and bind
  std::function<void(const boost::shared_ptr<std_msgs::Float32 const>&)>
      bound_cb =
	  std::bind(cpp_value_listener_cb, std::placeholders::_1, &topic_value);
  // using std::function and lambda function
  std::function<void(const boost::shared_ptr<std_msgs::Float32 const>& msg_ptr)>
      bound_cb_2 = [&topic_value](
	  const boost::shared_ptr<std_msgs::Float32 const>& msg_ptr) {
	cpp_value_listener_cb(msg_ptr, &topic_value);
      };

  ros::Subscriber cpp_value_listener;
  cpp_value_listener =
      nh.subscribe<std_msgs::Float32>("cpp_number", 1, bound_cb);

  while (ros::ok()) {

    ros::spinOnce(); // This will update information from subscribers

    playground_msgs::Flt64 value1;
    value1.data = (double)getFloat();

    ros::ServiceClient client =
	nh.serviceClient<playground_msgs::CompareGtDouble>("compare_gt_double");

    playground_msgs::CompareGtDouble srv;
    srv.request.value1 = value1;
    srv.request.value2.data = topic_value;
    if (client.call(srv)) {
      bool ret = (bool)srv.response.greater;
      if (ret) {
	ROS_INFO(
	    "Number %g was greater or equal to %g, generated by other node",
	    value1.data, topic_value);
      } else {
	ROS_INFO("Number %g was less than %g, generated by other node",
		 value1.data, topic_value);
      }
    } else {
      ROS_WARN("Service Call failed");
    }

    loop_rate.sleep();
  }

  return 0;
}
