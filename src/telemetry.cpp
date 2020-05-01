#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

geometry_msgs::PoseStamped uav0_loc;
void loc_cb_uav0(const geometry_msgs::PoseStamped::ConstPtr& loc){
    uav0_loc = *loc;
}

geometry_msgs::PoseStamped uav1_loc;
void loc_cb_uav1(const geometry_msgs::PoseStamped::ConstPtr& loc){
    uav1_loc = *loc;
}

geometry_msgs::PoseStamped uav2_loc;
void loc_cb_uav2(const geometry_msgs::PoseStamped::ConstPtr& loc){
    uav2_loc = *loc;
}

geometry_msgs::PoseStamped uav3_loc;
void loc_cb_uav3(const geometry_msgs::PoseStamped::ConstPtr& loc){
    uav3_loc = *loc;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "telemetry");
	ros::NodeHandle nh;
	ros::Rate rate(1.0);

	ros::Subscriber loc_sub_uav0 = nh.subscribe<geometry_msgs::PoseStamped>("uav0/mavros/local_position/pose", 1, loc_cb_uav0);
	ros::Subscriber loc_sub_uav1 = nh.subscribe<geometry_msgs::PoseStamped>("uav1/mavros/local_position/pose", 1, loc_cb_uav1);
	ros::Subscriber loc_sub_uav2 = nh.subscribe<geometry_msgs::PoseStamped>("uav2/mavros/local_position/pose", 1, loc_cb_uav2);
	ros::Subscriber loc_sub_uav3 = nh.subscribe<geometry_msgs::PoseStamped>("uav3/mavros/local_position/pose", 1, loc_cb_uav3);


	while(ros::ok())
	{
	ROS_INFO("<--- Telemetry Data --->");
	std::cout <<"Copter 1: x->"<<uav0_loc.pose.position.x<<" y->"<<uav0_loc.pose.position.y  <<" z->"<<uav0_loc.pose.position.z<<std::endl;
	std::cout <<"Copter 2: x->"<<uav1_loc.pose.position.x<<" y->"<<uav1_loc.pose.position.y  <<" z->"<<uav1_loc.pose.position.z<<std::endl;
	std::cout <<"Copter 3: x->"<<uav2_loc.pose.position.x<<" y->"<<uav2_loc.pose.position.y  <<" z->"<<uav2_loc.pose.position.z<<std::endl;
	std::cout <<"Copter 4: x->"<<uav3_loc.pose.position.x<<" y->"<<uav3_loc.pose.position.y  <<" z->"<<uav3_loc.pose.position.z<<std::endl;

	ros::spinOnce();
	rate.sleep();
	}
return 0;
}

	
