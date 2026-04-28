create the model in isaacsim
load an environment and a robot in my case a limo with differential controller already configured.

add the lidar under a link (in this case base_link)

for the lidar you can go with either RTX version Example Rotary 2D or the simpler Physx version each require different Action Graph

going with Physx Lidar here

in order to see the lidar after starting simulation.
add objects in the stage. remember to enable collision on the objects otherwise the laser pass through.

also in raw usd properties of the lidar check the drawPoints or Lines as well as enabled to visualize and debug whether the lidar is working.

actions graphs
	/clock
	/odom
	/tf 
	lidar /scan
	/cmd_vel
odom requires computing odom node connect to publish odom and to raw transform tree from odom to base_link

from Isaac compute odometry node connect the orientation and translation to Rotation and Position from Raw Transform Tree from Odom to base_link to make the odom frame stationary.

for Isaac compute odometry node chassisPrim choose /World/limo_ROS

then a transform tree from base_link to other links

verify to have the TF tree correctly by running
ros2 run tf2_tools view_frames

it should be odom -> base_link -> other links



create the yaml file with let's call it  mapper_params_online_async.yaml copy the yaml file from the slam_toolbox fithub page (just change the base_frame: base_link) and then run the slam_toolbox with the yaml parameters like this

remember to include the full path of the yaml as instructed by the package.

ros2 launch slam_toolbox online_async_launch.py slam_params_file:=/home/aidin/A/SLAM_ISAAC_TESTS/mapper_params_online_async.yaml

check whether /map is published via ros2 topic list

open rviz2 and set the fixed frame to map
add the Map from topics in Rviz, add the /scan from laserScan lidar
add the TF

move the robot with teleop_twist slowly 

save the map with 
ros2 run nav2_map_server map_saver_cli -f map_limo
