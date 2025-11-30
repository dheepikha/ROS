#include <ros/ros.h>
#include<std_msgs/Float32.h>


double desired_speed=0.0;
double actual_speed=0.0;
const double kp=14;
double V=0.0;

void speedCallback(const std_msgs::Float32::ConstPtr&msg)
{

	actual_speed =msg->data;

}




int main(int argc,char **argv)
{
	ros ::init(argc,argv,"controller");
	ros ::NodeHandle n2;
	
desired_speed = atof(argv[1]);

	
	ros:: Publisher motorvoltage = n2.advertise<std_msgs::Float32>("motor_voltage",10);
	
	ros::Subscriber motorspeed= n2.subscribe("motor_speed",10,speedCallback);
	
	ros::Rate rate(100);
	
	while(ros::ok())
	{
		float error = desired_speed - actual_speed;
		V= kp*error;

		// Clamp voltage for safety
        if (V > 1000.0) V = 1000.0;
        if (V < 0.0)    V = 0.0;
		
		std_msgs::Float32 msg;
		msg.data=V;
		motorvoltage.publish(msg);
		
	
	  ros::spinOnce();
        rate.sleep();
	
	
	
	}
	return 0;
	
	



}
