#ifndef MOVE_H_
#define MOVE_H_

class Move{
		public:
		Move();
		~Move();
		void straight(double speed, double distance);
		void g_turn(double angular_speed, double target_degree);
		void poseCallback(const turtlesim::PoseConstPtr &pose);
		void goal_posi(double goal_x, double goal_y);

		private:
		ros::Publisher velocity_publisher;
		ros::Subscriber pose_subscriber;
		turtlesim::Pose current_pose;
		ros::NodeHandle n;

		//$B$3$N(B2$B$D$O$3$N%/%i%9Fb$G$7$+;H$o$J$$$O$:(B
		double rad_to_deg(double rad);
		double deg_to_rad(double degree);
		double get_distance(double x1, double y1, double x2, double y2);
		double get_degrees(double x1, double y1, double x2, double y2);
};

#endif

