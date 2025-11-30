#include <ros/ros.h>
#include <turtle_diff_drive/wheel_velocity.h>

int main(int argc, char **argv)
{
	ros::init(argc,argv,"wheel_velocity_pub");
	ros::NodeHandle node1;
	
	ros::Publisher pub=node1.advertise<turtle_diff_drive::wheel_velocity>("wheel_vel",10);
	
	ros::Rate loop_rate(1);
	
	while(ros::ok())
	{
		turtle_diff_drive::wheel_velocity msg;
		msg.omega_l=12;
		msg.omega_r=8;
		
		pub.publish(msg);
		ROS_INFO("Publishing: omega_left=%.2f, omega_right=%.2f", msg.omega_l, 			msg.omega_r); 
		loop_rate.sleep();
	}
	return 0;
	
	
}
