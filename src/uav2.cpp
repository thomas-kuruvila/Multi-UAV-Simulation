#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

geometry_msgs::PoseStamped current_loc;
void loc_cb(const geometry_msgs::PoseStamped::ConstPtr& loc){
    current_loc = *loc;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "uav2_node");
	ros::NodeHandle nh;

	ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("uav2/mavros/state", 1, state_cb);
	ros::Subscriber loc_sub = nh.subscribe<geometry_msgs::PoseStamped>("uav2/mavros/local_position/pose", 1, loc_cb);
	ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("uav2/mavros/setpoint_position/local", 10);
	ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("uav2/mavros/cmd/arming");
	ros::ServiceClient mode_client = nh.serviceClient<mavros_msgs::SetMode>("uav2/mavros/set_mode");
	ros::ServiceClient takeoff_client = nh.serviceClient<mavros_msgs::CommandTOL>("uav2/mavros/cmd/takeoff");


	ros::Rate rate(20.0);

	while(ros::ok() && current_state.connected)
		{
	        ros::spinOnce();
        	rate.sleep();
    		}
	
	geometry_msgs::PoseStamped pose;
	pose.pose.position.x = 0;
	pose.pose.position.y = 10;
	pose.pose.position.z = 10;
    

	for(int i = 100; ros::ok() && i > 0; --i)
		{
		local_pos_pub.publish(pose);
		ros::spinOnce();
		rate.sleep();
		}

	mavros_msgs::SetMode set_mode;
	set_mode.request.custom_mode = "GUIDED";

	mavros_msgs::CommandBool arm_mode;
	arm_mode.request.value = true;

	mavros_msgs::CommandTOL takeoff_request;
	takeoff_request.request.altitude =10;

 	
	bool permission2;

	while(current_loc.pose.position.y <= 9.8 && ros::ok() && nh.getParam("uav2_ver", permission2))
		{
		if( current_state.mode != "GUIDED")
			{
			if( mode_client.call(set_mode) && set_mode.response.mode_sent)
				{
				ROS_INFO("Mode -> GUIDED");
				}
			} 
		else if( !current_state.armed && current_state.guided && permission2)
			{
			if( arming_client.call(arm_mode) && arm_mode.response.success)
				{
				ROS_INFO("Vehicle armed");
				}
			}
		else if(current_loc.pose.position.z < 9.8 && current_state.guided && current_state.armed)
			{
			 if( takeoff_client.call(takeoff_request) && takeoff_request.response.success)
				{
				ROS_INFO("Takeoff Started..");
				}
			}
		else if (current_loc.pose.position.z >=9.8)
			{
			ROS_INFO("Moving to A");
			local_pos_pub.publish(pose);
			}
		else 
			{ROS_INFO("here");}
		ros::spinOnce();
		rate.sleep();
		}

	pose.pose.position.y = 1;

	while(ros::ok())
		{
		if(current_loc.pose.position.y >=1.2)
			{
			local_pos_pub.publish(pose);
			ROS_INFO("Return to Home");
			}
		if(current_loc.pose.position.y <=1.2 && current_loc.pose.position.z >= 9.8)
			{
			set_mode.request.custom_mode = "LAND";
			if( mode_client.call(set_mode) && set_mode.response.mode_sent)
				{
				ROS_INFO("Mode -> LAND");
				nh.setParam("uav2_ver", false);
				break;
				}
			}
		
		ros::spinOnce();
		rate.sleep();
		}


	return 0;
}

	


	

	

	

