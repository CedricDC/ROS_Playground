#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32

def number_cb(msg):
	print "Received ", msg.data, " from ", msg._connection_header["topic"]

def number_subscriber():
	rospy.init_node("py_receiver")
	sub = rospy.Subscriber("py_number", Float32, number_cb)

	rospy.spin()

if __name__ == '__main__':
	try:
		number_subscriber()
	except rospy.ROSInterruptException:
		pass
