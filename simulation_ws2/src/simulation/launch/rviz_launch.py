# WORKS: Launches urdf visualization in RViz2 with joint_state_publisher_gui
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument        # lets us define CLI arguments
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, Command
from launch_ros.actions import Node                     # to start ROS 2 nodes
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare    # resolves package paths dynamically


def generate_launch_description():
    # -------------------------------------------------------------------------
    # 1️⃣  FIND PACKAGE PATHS
    # -------------------------------------------------------------------------
    # FindPackageShare('simulation') locates your installed package’s `share/`
    # directory no matter where the workspace is built. This is safer than
    # hardcoding absolute paths.
    pkg_share = FindPackageShare('simulation')

    # PathJoinSubstitution joins path components in a cross-platform way at
    # launch time. These two lines create dynamic paths to your default
    # .xacro file and RViz config.
    default_xacro = PathJoinSubstitution([pkg_share, 'robot_description', 'robot.urdf.xacro'])
    default_rviz  = PathJoinSubstitution([pkg_share, 'config', 'robot.rviz'])

    # -------------------------------------------------------------------------
    # 2️⃣  DECLARE LAUNCH ARGUMENTS (USER-OVERRIDABLE INPUTS)
    # -------------------------------------------------------------------------
    # DeclareLaunchArgument registers a variable that can be passed on the CLI
    # when running `ros2 launch`. Each argument has:
    #   - a name (e.g. 'model')
    #   - a default value
    #   - a description for help output

    # Example usage: ros2 launch simulation display.launch.py model:=/path/to/custom.xacro
    model_arg = DeclareLaunchArgument(
        'model',                      # argument name
        default_value=default_xacro,  # default if user doesn’t override
        description='Path to the .xacro robot model'
    )

    # Same pattern for RViz configuration file
    rviz_arg = DeclareLaunchArgument(
        'rviz_config',
        default_value=default_rviz,
        description='Path to RViz2 config (.rviz) file'
    )

    # Boolean toggle for GUI vs. headless joint_state_publisher
    # CLI: ros2 launch simulation display.launch.py use_gui:=false
    use_gui_arg = DeclareLaunchArgument(
        'use_gui',
        default_value='true',
        description='Use joint_state_publisher_gui (true/false)'
    )

    # Extra arguments to pass into xacro macros at runtime.
    # CLI: ros2 launch simulation display.launch.py xacro_args:="wheel_radius:=0.05"
    xacro_args = DeclareLaunchArgument(
        'xacro_args',
        default_value='',
        description='Extra args for xacro, e.g. "use_gazebo:=true wheel_radius:=0.05"'
    )

    # -------------------------------------------------------------------------
    # 3️⃣  CONVERT XACRO → URDF DYNAMICALLY
    # -------------------------------------------------------------------------
    # The Command substitution executes a shell command at launch time.
    # Here it runs:  xacro <path_to_file> <extra_args>
    # The result (URDF XML text) is captured and stored.
    #
    # ParameterValue(value_type=str) tells the launch system this output
    # should be treated as a string parameter (not a path or number).
    #
    # LaunchConfiguration('model') retrieves the current value of the
    # 'model' argument—either the default or whatever the user provided.
    # Same for LaunchConfiguration('xacro_args').
    # Therefore = Xacro+param I could pass here
    robot_description = ParameterValue(
        Command(['xacro ', LaunchConfiguration('model'), ' ', LaunchConfiguration('xacro_args')]),
        value_type=str
    )

    # -------------------------------------------------------------------------
    # 4️⃣  START ROBOT_STATE_PUBLISHER
    # -------------------------------------------------------------------------
    # This node reads the URDF from the `robot_description` parameter and
    # publishes TF transforms for all links and joints.  RViz uses these TFs
    # to display the robot model in 3D.
    rsp = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{'robot_description': robot_description}]
    )

    # -------------------------------------------------------------------------
    # 5️⃣  START JOINT_STATE_PUBLISHER (GUI OR HEADLESS)
    # -------------------------------------------------------------------------
    # Publishes /joint_states for the robot. The GUI version lets you move
    # sliders to change joint positions interactively. The headless version
    # just sends fixed zero values.
    #
    # IfCondition and UnlessCondition evaluate the 'use_gui' launch argument.
    jsp_gui = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher',
        condition=IfCondition(LaunchConfiguration('use_gui'))
    )

    jsp_headless = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        condition=UnlessCondition(LaunchConfiguration('use_gui'))
    )

    # -------------------------------------------------------------------------
    # 6️⃣  START RVIZ2
    # -------------------------------------------------------------------------
    # Launch RViz2 so you can visualize the robot model. The '-d' argument
    # loads a saved configuration file (.rviz) that remembers camera position,
    # display types, and colors.  Remove this line if you want to start RViz
    # blank.
    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', LaunchConfiguration('rviz_config')],
        output='screen'  # print RViz logs to the terminal
    )

    # -------------------------------------------------------------------------
    # 7️⃣  COLLECT AND RETURN EVERYTHING
    # -------------------------------------------------------------------------
    # LaunchDescription holds all actions that should run when this file is
    # launched.  Arguments are declared first, then node actions follow.
    return LaunchDescription([
        model_arg, rviz_arg, use_gui_arg, xacro_args,  # declare args
        rsp, jsp_gui, jsp_headless, rviz               # launch nodes
    ])
