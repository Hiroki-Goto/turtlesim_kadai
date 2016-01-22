#include "../function.h"

#define PI 3.14159265359
#define ERROR 0.001

Move::Move(){
		ROS_INFO("start");
		//$B9XFI$HG[?.$N@_Dj(B
		velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
		pose_subscriber = n.subscribe<turtlesim::Pose>("/turtle1/pose",100, &Move::poseCallback,this);
		
		geometry_msgs::Twist vel_msg;
		//$BJB?JB.EY$N=i4|2=(B
		vel_msg.linear.x = 0;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		//$B2sE>B.EY$N=i4|2=(B
		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 0;
		velocity_publisher.publish(vel_msg);
}

Move::~Move(){
		//$B=*N;3NG'(B
		ROS_INFO("finish");
}

double Move::rad_to_deg(double rad){
		//$B$?$@$N3QEY3NG'MQ(B
		return rad /PI * 180;
}

double Move::deg_to_rad(double degree){
		//$B%H%T%C%/$,%i%8%"%s$G$/$k$+$i$=$l$K9g$o$;$k(B
		return degree /180.0 * PI;
}

double Move::get_distance(double x1, double y1, double x2, double y2)	{	
		return sqrt( pow(x1 - x2,2) + pow(y1 - y2,2) );
}
double Move::get_degrees(double x1, double y1, double x2, double y2){		
		return atan2( (y1 - y2), (x1 - x2) );
}


//$BD>?JMQ4X?t(B
void Move::straight(double speed, double distance){
		geometry_msgs::Twist vel_msg;
		vel_msg.linear.x = speed;

		double t0 = ros::Time::now().toSec();
		double current_distance = 0;
		ros::Rate loop_rate(100);
		
		while(current_distance < distance){
				velocity_publisher.publish(vel_msg);
				double t1 = ros::Time::now().toSec();
				current_distance = speed * (t1 - t0);
				ros::spinOnce();
				loop_rate.sleep();
		}
		vel_msg.linear.x = 0;
		velocity_publisher.publish(vel_msg);

}
//$B%0%m!<%P%k:BI87O$rMQ$$$?2sE>(B
void Move::g_turn(double angular_speed, double target_degree){
		geometry_msgs::Twist vel_msg;
		double  goal_rad = deg_to_rad(target_degree); 
		double target_radians =goal_rad - current_pose.theta;
		bool clockwise = ( (target_radians < 0) ? true:false);
		if(clockwise)
				vel_msg.angular.z = -fabs( deg_to_rad(angular_speed) );
		else
				vel_msg.angular.z = fabs( deg_to_rad(angular_speed) );
		
		//ROS_INFO("%lf",vel_msg.angular.z);
		ros::Rate loop_rate(100);
	    if(clockwise){	
			while( (current_pose.theta - goal_rad )  >  ERROR ){
					velocity_publisher.publish(vel_msg);
					ros::spinOnce();
					loop_rate.sleep();
					//ROS_INFO("%lf\t%lf",current_pose.theta,goal_rad);
			}
		}else{
			while( (current_pose.theta - goal_rad )  <  ERROR ){
					velocity_publisher.publish(vel_msg);
					ros::spinOnce();
					loop_rate.sleep();
					//ROS_INFO("%lf\t%lf",current_pose.theta,goal_rad);
			}
		}
		vel_msg.angular.z = 0.0;
		velocity_publisher.publish(vel_msg);
		
}

void Move::goal_posi(double goal_x, double goal_y){
		double target_theta = get_degrees(goal_x,goal_y,current_pose.x,current_pose.y);
		target_theta = rad_to_deg(target_theta);
		ROS_INFO("%lf",target_theta);
		g_turn(60,target_theta);
		
		double target_distance = get_distance(goal_x,goal_y, current_pose.x, current_pose.y);
		straight(3,target_distance);
}

void Move::poseCallback(const turtlesim::PoseConstPtr &pose){
		current_pose.x = pose -> x;
		current_pose.y = pose -> y;
		current_pose.theta = pose -> theta;
	//	ROS_INFO("OK");
}
