#include <ros/ros.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "permission");
	ros::NodeHandle nh;
	ros::Rate rate(1.0);

	int ID=0;
	
	while(ros::ok())
		{
		ROS_INFO("<--- TakeOFF Permission --->");
		ROS_INFO("Enter UAV ID to grant permission-->");
		std::cin>>ID;
		
		switch (ID)
			{
			case 1:
			{ros::param::set("uav0_ver", true);
			ROS_INFO("UAV-1 has been granted permission for takeoff!");
			break;}
			case 2:
			{ros::param::set("uav1_ver", true);
			ROS_INFO("UAV-2 has been granted permission for takeoff!");
			break;}
			case 3:
			{ros::param::set("uav2_ver", true);
			ROS_INFO("UAV-3 has been granted permission for takeoff!");
			break;}
			case 4:
			{ros::param::set("uav3_ver", true);
			ROS_INFO("UAV-4 has been granted permission for takeoff!");
			break;}
			}
		ros::spinOnce();
		rate.sleep();
		}
	return 0;
}
			
			
					

