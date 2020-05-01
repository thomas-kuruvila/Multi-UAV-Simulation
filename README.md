# Multi-UAV-Simulation
Simulated 4 UAV's that follows pre-described paths to 4 different destination and returns back.

# Overview
This will provide a general overview of the system and its various components used in the simulation.

1. SITL --> Software In The Loop allows us to run a bot (Plane, Copter or Rover) without the hardware, allowing us to test the behaviour of our code without hardware. Here we connect each SITL instances with (i)the apm execution of mavros for basic control and (ii) Gazebo for Visualisation. The first is done through a udp port of the sim_vehicle, which can be viewed in  swarm/launch/world.launch under the <mavros and vehicle config tag>. The second is achieved by specifying the <fdm_port_in> and <fdm_port_out> tags in the model.sdf file present in each of the UAV model directory at swarm/models. 

2.Gazebo --> Gazebo offers robot simulation in a robust physics engine, high-quality graphics and convenient programmatic and graphical interfaces. I used world.launch present in swarm/launch to use the swarm.world environment present in swarm/worlds. The swarm.world features an empty world with a ground plane and 4 UAV's.The details of each model introduced can be found at swarm/models.

3.MAVROS --> It is a ROS wrapper for the MAVLINK communication protocol. It accepts mavlink data published by fcb and publishes them in appropriate topics. This allows for easy manipulation of the UAV using the ROS middleware. Mavros for each UAV is initialised in the world.launch file. A namespace is also used to differentiate between mavros topics of each uav. It is connected to the SITL instance via a UDP port, as mentioned above.

4. UAV Nodes --> These perform the functionality of publishing control commands to each UAV. A small offset has been set to the local locations owing to the inaccuracy in achieving the current location. The UAV nodes are present at swarm/src.

5. Telemetry Node --> This Node subscribes to the local position topics of each UAV and display its current location to the user. 

6. Permission Node --> This performs the NPNT compliance of each UAV. It depends on the setting and resetting of the verification parameter in the ROS parameter server. Each UAV node checks if the verification parameter is set to True or False before arming and proceeds only if the parameter is set to True. 

7. mission.sh --> This is a bash sript that runs individual uav nodes with an interval of 10sec. The permission is assumed to be granted when the script is called. 


# Execution
This describes the execution process. It is assumed that all dependencies are installed and the package has been succefully built. Refer to package.xml for the list of dependencies. 

1. Launch 4 SITL Instances.

	sim_vehicle.py -v ArduCopter -f gazebo-iris -I 0
	sim_vehicle.py -v ArduCopter -f gazebo-iris -I 1
	sim_vehicle.py -v ArduCopter -f gazebo-iris -I 2
	sim_vehicle.py -v ArduCopter -f gazebo-iris -I 3

2. Launch the gazebo world along with the 4 ardupilot plugin enabled UAV's
 	
	roslaunch swarm world.launch

The simulation and visualisation environment along with the parameters for NPNT compliance are initiated.

3. Start the multi UAV mission

	roslaunch swarm mission.launch

The 4 ROS nodes corresponding to each UAV has started its execution. The takeoff will not occur unless necessary permission is granted. 

4. Granting permission for takeoff

	rosrun swarm permission

Enter the UAV ID as 1,2,3 or 4 to grant permission to the 1st, 2nd, 3rd or 4th UAV. 

5. Viewing Telemetry Data

	rosrun swarm telemetry

This displays the (x,y,z) coordinates of each UAV. Here I have run the entire operation on local coordinates. Global coordinate system is not used here.

Note: The Multi UAV mission with delay can be started using the permission.sh script file. It starts each node with an interval of 10sec. This does not guarentee that the takeoff will occur exactly 10sec apart, but in a perfect system it should :D This does not request takeoff permission and is assumed to be granted all together when mission is called. There is room for improvement using the ros::time parameter to time the takeoff accordingly.
