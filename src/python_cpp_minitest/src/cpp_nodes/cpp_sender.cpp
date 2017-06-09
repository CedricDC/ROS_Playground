#include <chrono>
#include <iostream>

#include "python_cpp_minitest/cpp_number_generator.h"

// ROS related includes
#include <ros/ros.h>
#include <std_msgs/Float32.h>

// declare ros publishers and subscribers
ros::Publisher number_publisher;

int main(int argc, char** argv) {
  ros::init(argc, argv, "cpp_sender");

  ros::NodeHandle nh;  // handle to node

  number_publisher = nh.advertise<std_msgs::Float32>("cpp_number", 10);

  // fill cpp number message
  std_msgs::Float32 msg;
  msg.data = 2.0;
  const float freq = 0.5;  // send message with this frequency

  ros::Rate loop_rate(freq);
  std::chrono::time_point<std::chrono::steady_clock> t_current, t_last;
  t_current = std::chrono::steady_clock::now();
  t_last = t_current;
  std::chrono::duration<double> loop_time;

  while (ros::ok()) {
    t_current = std::chrono::steady_clock::now();
    msg.data = getFloat(0.0, 20.0);
    number_publisher.publish(msg);

    loop_time = t_current - t_last;
    std::cout << "[cpp sender] Loop took " << loop_time.count() << " seconds."
	      << std::endl;
    t_last = t_current;
    loop_rate.sleep();
  }

  return 0;
}
