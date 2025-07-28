#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <cmath>

float deg_to_rad(float deg){
    return deg*M_PI/180;
}

int main(int argc, char **argv)
{
    // Initialize the ROS node
    ros::init(argc, argv, "simple_controller_node");
    ros::NodeHandle nh;

    // Create publishers for the joint controllers.
    // The topic names are <robot_namespace>/<controller_name>/command
    ros::Publisher left_hip_pub = nh.advertise<std_msgs::Float64>("/wheeled_biped/left_hip_position_controller/command", 10);
    ros::Publisher right_hip_pub = nh.advertise<std_msgs::Float64>("/wheeled_biped/right_hip_position_controller/command", 10);
    ros::Publisher left_knee_pub = nh.advertise<std_msgs::Float64>("/wheeled_biped/left_knee_position_controller/command", 10);
    ros::Publisher right_knee_pub = nh.advertise<std_msgs::Float64>("/wheeled_biped/right_knee_position_controller/command", 10);

    ros::Publisher left_wheel_pub = nh.advertise<std_msgs::Float64>("/wheeled_biped/left_wheel_velocity_controller/command", 10);
    ros::Publisher right_wheel_pub = nh.advertise<std_msgs::Float64>("/wheeled_biped/right_wheel_velocity_controller/command", 10);

    // Wait a moment for everything to initialize
    ros::Duration(1.0).sleep();

    // Set the control loop rate (e.g., 100 Hz)
    ros::Rate loop_rate(100);

    double start_time = ros::Time::now().toSec();
    ROS_INFO("Starting simple controller. Robot should start moving.");

    while (ros::ok())
    {
        double elapsed_time = ros::Time::now().toSec() - start_time;

        // --- Hip Oscillation Control ---
        // Create a sinusoidal motion for the hips to simulate walking
        // double amplitude = 0.5; // radians
        // double frequency = 0.5; // Hz
        // double desired_pos = amplitude * sin(2 * M_PI * frequency * elapsed_time);

        std_msgs::Float64 hip_cmd;
        hip_cmd.data = 0.0;
        left_hip_pub.publish(hip_cmd);
        right_hip_pub.publish(hip_cmd);

        // Knee position control
        std_msgs::Float64 knee_cmd;
        knee_cmd.data = deg_to_rad(90);
        left_knee_pub.publish(knee_cmd);
        right_knee_pub.publish(knee_cmd);

        // --- Wheel Velocity Control ---
        // Command the wheels to move forward at a constant velocity
        std_msgs::Float64 wheel_cmd;
        wheel_cmd.data = 0.0; // rad/s
        left_wheel_pub.publish(wheel_cmd);
        right_wheel_pub.publish(wheel_cmd);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
