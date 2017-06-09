#include <iostream>

// ROS related includes
#include <ros/ros.h>
#include <std_msgs/Float32.h>

// declare ros publishers and subscribers
ros::Subscriber number_subscriber;

// Callback Functions
void cpp_receiver_cb(
    const boost::shared_ptr<std_msgs::Float32 const>& msg_ptr) {
  std::cout << "[cpp receiver cb] Received: " << msg_ptr->data << " from "
	    << number_subscriber.getTopic() << std::endl;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "cpp_receiver");

  ros::NodeHandle nh;  // handle to node

  number_subscriber = nh.subscribe("cpp_number", 10, &cpp_receiver_cb);

  ros::spin();

  return 0;
}
