#!/bin/bash

rosparam set uav0_ver true
rosparam set uav1_ver true
rosparam set uav2_ver true
rosparam set uav3_ver true

rosrun swarm uav0
sleep 10
rosrun swarm uav1 
sleep 10
rosrun swarm uav2
sleep 10
rosrun swarm uav3
