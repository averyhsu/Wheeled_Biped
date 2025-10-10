from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, Command, TextSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare
import os

def generate_launch_description():
    pkg = FindPackageShare('simulation')
    urdf_xacro = PathJoinSubstitution([pkg, 'robot_description', 'robot.urdf.xacro'])
    rviz_config_file = PathJoinSubstitution([pkg, 'config', 'robot.rviz'])

    # ---------- Arguments (mirrors your XML) ----------
    paused      = LaunchConfiguration('paused')
    use_sim     = LaunchConfiguration('use_sim_time')
    gui         = LaunchConfiguration('gui')
    headless    = LaunchConfiguration('headless')
    debug       = LaunchConfiguration('debug')
    rviz        = LaunchConfiguration('rviz')

    x = LaunchConfiguration('x');     y = LaunchConfiguration('y');     z = LaunchConfiguration('z')
    roll = LaunchConfiguration('roll'); pitch = LaunchConfiguration('pitch'); yaw = LaunchConfiguration('yaw')

    # Joint position args (you'll use these with controllers after spawn)
    left_hip_pos   = LaunchConfiguration('left_hip_pos')
    right_hip_pos  = LaunchConfiguration('right_hip_pos')
    left_knee_pos  = LaunchConfiguration('left_knee_pos')
    right_knee_pos = LaunchConfiguration('right_knee_pos')
    left_wheel_pos = LaunchConfiguration('left_wheel_pos')
    right_wheel_pos= LaunchConfiguration('right_wheel_pos')

    declare_args = [
        DeclareLaunchArgument('paused', default_value='true'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('gui', default_value='true'),
        DeclareLaunchArgument('headless', default_value='false'),
        DeclareLaunchArgument('debug', default_value='false'), # Not used, but kept for consistency
        DeclareLaunchArgument('rviz', default_value='true'), # Default to true for convenience

        DeclareLaunchArgument('x', default_value='0'),
        DeclareLaunchArgument('y', default_value='0'),
        DeclareLaunchArgument('z', default_value='1'),
        DeclareLaunchArgument('roll',  default_value='0'),
        DeclareLaunchArgument('pitch', default_value='0'),
        DeclareLaunchArgument('yaw',   default_value='0'),

        DeclareLaunchArgument('left_hip_pos',   default_value='0'),
        DeclareLaunchArgument('right_hip_pos',  default_value='0'),
        DeclareLaunchArgument('left_knee_pos',  default_value='-2.1'),
        DeclareLaunchArgument('right_knee_pos', default_value='-2.1'),
        DeclareLaunchArgument('left_wheel_pos', default_value='0.0'),
        DeclareLaunchArgument('right_wheel_pos',default_value='0.0'),

    ]

    # ---------- robot_description from xacro ----------
    # The ParameterValue substitution is more robust as it handles complex commands
    # and allows for passing other substitutions to the xacro command. It ensures
    # the command's string output is used as the parameter value.
    robot_description_content = ParameterValue(
        Command(['xacro ', urdf_xacro, ' use_ros2_control:=true']),
        value_type=str
    )

    rsp = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[
            {'robot_description': robot_description_content, 'use_sim_time': use_sim}
        ],
        output='screen'
    )

    # ---------- Gazebo Sim (Ignition) ----------
    # Build base gz sim command depending on GUI/headless and paused/run
    # Find the Gazebo ROS package
    # For Gazebo Fortress, we use the 'ros_gz_sim' package
    pkg_ros_gz_sim = FindPackageShare('ros_gz_sim')

    # Start Gazebo paused
    gazebo_paused = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py'])
        ),
        launch_arguments={'gz_args': 'empty.sdf'}.items(),
        condition=IfCondition(paused)
    )

    # Start Gazebo running
    gazebo_running = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py'])
        ),
        launch_arguments={'gz_args': '-r empty.sdf'}.items(),
        condition=UnlessCondition(paused)
    )

    # Bridge to connect ROS topics with Gazebo (e.g., for clock)
    gz_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        # Bridge clock, and the joint states from Gazebo to ROS
        arguments=[
            '/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock',
            '/world/default/model/wheeled_biped/joint_state@sensor_msgs/msg/JointState[gz.msgs.Model',
        ],
        output='screen'
    )

    # ---------- Delayed Spawn Action----------
    # The spawn action is delayed by 5 seconds to allow Gazebo to fully start.
    # This prevents a race condition where the spawn request is sent before Gazebo is ready.
    delayed_spawn = TimerAction(
        period=5.0,
        actions=[Node(
            package='ros_gz_sim',
            executable='create',
            output='screen',
            arguments=[
                '-name', 'wheeled_biped',
                '-topic', 'robot_description',
                '-X', x, '-Y', y, '-Z', z,
                '-Roll', roll, '-Pitch', pitch, '-Yaw', yaw,
            ]
        )]
    )

    # ---------- TODO (joint positions) ----------
    # The -J flags from gazebo_ros (classic) don’t exist in ros_gz_sim create.
    # To set initial joint angles in Gazebo Sim, load controllers (ros2_control + gz_ros2_control)
    # and send a one-shot command after spawn, or define default joint poses in SDF.
    # (Happy to wire this for your robot once you tell me which controllers you use.)

    # ---------- RViz ----------
    # Conditionally launch RViz2 if the 'rviz' argument is true
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_file],
        condition=IfCondition(rviz),
        output='screen'
    )

    return LaunchDescription(
        declare_args + [
            rsp,
            gazebo_paused,
            gazebo_running,
            delayed_spawn,
            gz_bridge,
            rviz_node,
        ]
    )
