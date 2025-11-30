#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
#include <turtlesim/Pose.h>


const double K_rho = 1.5;
const double K_alpha = 4.0;
const double K_beta = -1.0;
double x_g=9.0;
double y_g=8.0;
double theta_g=0.9;

ros::Publisher pub;


void positionCallback(const turtlesim::Pose::ConstPtr &msg)
{
    ROS_INFO("Pose received: x=%.2f, y=%.2f, theta=%.2f", msg->x, msg->y, msg->theta);

    double rho= sqrt(pow((x_g-msg->x),2) + pow((y_g-msg->y),2));
    double alpha=atan2(y_g-msg->y,x_g-msg->x)-msg->theta;
    double beta=((theta_g-msg->theta)-alpha);
              
    double v= K_rho*rho;
    double w= (K_alpha*alpha)+(K_beta*beta);
    
    
    
    	geometry_msgs::Twist vel;
    	vel.linear.x=v;
    	vel.angular.z=w;
    	
    	pub.publish(vel);
    	ROS_INFO("Converted: v=%.2f m/s, w=%.2f rad/s", v, w);
    
}

int main(int argc, char ** argv)
{
	ros::init(argc,argv,"go_to_goal_controller");
	ros::NodeHandle node3;
	
	ros::Subscriber sub=node3.subscribe("/turtle1/pose",10,positionCallback);
	pub=node3.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	ros::spin();
	return 0;
}
