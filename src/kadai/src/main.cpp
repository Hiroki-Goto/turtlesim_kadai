#include "function.h"

int main(int argc, char **argv){
		ros::init(argc, argv, "kadai");
		//クラスの定義
		Move move;
		ros::Rate loop_rate(0.5);
		move.goal_posi(5.5,5.5);
		move.goal_posi(5.5,10.5);

		move.goal_posi(0.5,3.0);
		
		move.goal_posi(10.5,3);

		move.goal_posi(8.75,5.5);
		
		move.goal_posi(5.5,0.5);
		
		move.goal_posi(0.5,8.0);
		
		move.goal_posi(10.5,8.0);

		move.goal_posi(8.75,5.5);
		
		move.goal_posi(5.5,10.5);
		
		move.goal_posi(5.5,5.5);
		ros::spinOnce();
		return 0;
}

