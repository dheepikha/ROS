#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <cmath>


const double r =1;
const double l = 0.5;
const double j= 0.01;

const double b =0.1;
const double ke=0.01;
const double kt=0.01;


const double dt = 0.01;    


double V = 0.0;   
double I = 0.0;         
double w = 0.0;  


double v_min =0.0, v_max = 1000.0; // clamp voltage for realism
 double omega_rpm_min = 0.0, omega_rpm_max = 300.0;

void voltageCallback(const std_msgs::Float32::ConstPtr& msg)
{
    V = msg->data;
        ROS_INFO("Received voltage command: %.2f V", V);

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "simulator");
    ros::NodeHandle n1;
    
    ros::Publisher motor_speed= n1.advertise<std_msgs::Float32>("motor_speed", 10);
    ros::Subscriber motor_voltage = n1.subscribe("motor_voltage", 10, voltageCallback);

ros::Rate rate(100);
	while (ros::ok())
	{
	
	
	if (V > v_max) V = v_max;
    if (V < v_min) V = v_min;

		double dI= (V-r*I-ke*w)/l;
		
		double dW= (kt*I-b*w)/j;
		
		I+=dI*dt;
		w+=dW*dt;
		
		double w_rpm = w * 60.0 / (2.0 * M_PI);
		
		if (w_rpm > omega_rpm_max) w_rpm = omega_rpm_max;
        if (w_rpm < omega_rpm_min) w_rpm = omega_rpm_min;

	std_msgs::Float32 speed_msg;
        speed_msg.data = w_rpm	;  
        motor_speed.publish(speed_msg);
        
	ros::spinOnce();
        rate.sleep();
	}
	return 0;
}
