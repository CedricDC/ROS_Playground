#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32
import python_cpp_minitest.py_number_generator

def number_publisher():
	rospy.init_node("py_sender")
	pub = rospy.Publisher("py_number", Float32, queue_size = 10)

	# sending rate
	sending_rate = 1.0
	rate = rospy.Rate(sending_rate) # in Hz
	msg = Float32()

	while not rospy.is_shutdown():
		msg.data = python_cpp_minitest.py_number_generator.getNumber()
		pub.publish(msg)
		rate.sleep()

if __name__ == '__main__':
	try:
		number_publisher()
	except rospy.ROSInterruptException:
		pass
