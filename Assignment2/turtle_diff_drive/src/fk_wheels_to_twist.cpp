#include <ros/ros.h>
#include <turtle_diff_drive/wheel_velocity.h>
#include <geometry_msgs/Twist.h>


const double wheel_radius = 0.05;   
const double   wheel_base = 0.20; 
ros::Publisher pub;

void wheelVelCallback(const turtle_diff_drive::wheel_velocity::ConstPtr &msg)
{
    ROS_INFO("Received: omega_left=%.2f, omega_right=%.2f",
              msg->omega_l, msg->omega_r);
              
    double v= (wheel_radius/2)*(msg->omega_r+msg->omega_l);
    double w= (wheel_radius/wheel_base)*(msg->omega_r-msg->omega_l);
    
    
    
    	geometry_msgs::Twist vel;
    	vel.linear.x=v;
    	vel.angular.z=w;
    	
    	pub.publish(vel);
    	ROS_INFO("Converted: v=%.2f m/s, w=%.2f rad/s", v, w);
    
}

int main(int argc, char ** argv)
{
	ros::init(argc,argv,"fk_wheels_to_twist");
	ros::NodeHandle node2;
	
	ros::Subscriber sub=node2.subscribe("wheel_vel",10,wheelVelCallback);
	pub=node2.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",10);
	ros::spin();
	
	
	
	
	
	return 0;
}
