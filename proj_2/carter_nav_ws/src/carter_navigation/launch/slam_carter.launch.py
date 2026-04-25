import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # 1. Pointcloud to Laserscan Converter
        Node(
            package='pointcloud_to_laserscan',
            executable='pointcloud_to_laserscan_node',
            name='pointcloud_to_laserscan',
            remappings=[
                ('cloud_in', '/point_cloud'),
                ('scan', '/scan')
            ],
            parameters=[{
                'target_frame': 'XT_32_10hz', # Matches your LiDAR frame
                'transform_tolerance': 0.01,
                'min_height': -0.1, # Adjust based on where your LiDAR is
                'max_height': 0.1,
                'angle_min': -3.1415, # -180 degrees
                'angle_max': 3.1415,  # 180 degrees
                'range_min': 0.5,
                'range_max': 50.0,
                'use_inf': True,
                'inf_epsilon': 1.0
            }]
        ),

        # 2. SLAM Toolbox (Asynchronous Mode)
        Node(
            package='slam_toolbox',
            executable='async_slam_toolbox_node',
            name='slam_toolbox',
            output='screen',
            parameters=[{
                'use_sim_time': True,
                'odom_frame': 'odom',
                'base_frame': 'base_link',
                'scan_topic': '/scan',
                'mode': 'mapping',
                # These help with smoother mapping
                'map_update_interval': 0.5,
                'resolution': 0.05,
                'max_laser_range': 20.0
            }]
        )
    ])
