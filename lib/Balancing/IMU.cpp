#include <Wire.h>
#include <ros.h>
#include <sensor_msgs/Imu.h>
#include "Arduino/MPU6050/MPU6050.h"

// --- ROS node handle and publisher ---
ros::NodeHandle nh;
sensor_msgs::Imu imu_msg;
ros::Publisher imu_pub("imu/data", &imu_msg);

// --- MPU setup ---
MPU6050 mpu;

// Converts raw readings to SI units
constexpr float A_GAIN = 9.80665f / 16384.0f;       // ±2g FS
constexpr float G_GAIN = (3.14159265f / 180.0f) / 131.0f; // ±250°/s FS

//----------------------------------------------------------------------
// Initializes the IMU and ROS interfaces
void setup() {
  Wire.begin();
  mpu.initialize();

  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.advertise(imu_pub);
}

//----------------------------------------------------------------------
// Reads MPU‑6050, fills the Imu message, and publishes it.
// Call this at your desired control rate (e.g. 100 Hz).
void publishImuData() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Timestamp and frame
  imu_msg.header.stamp = nh.now();
  imu_msg.header.frame_id = "imu_link";

  // Fill linear acceleration
  imu_msg.linear_acceleration.x = ax * A_GAIN;
  imu_msg.linear_acceleration.y = ay * A_GAIN;
  imu_msg.linear_acceleration.z = az * A_GAIN;

  // Fill angular velocity
  imu_msg.angular_velocity.x = gx * G_GAIN;
  imu_msg.angular_velocity.y = gy * G_GAIN;
  imu_msg.angular_velocity.z = gz * G_GAIN;

  // (Orientation left zero for now)
  imu_pub.publish(&imu_msg);
}

//----------------------------------------------------------------------
// Main loop simply calls our helper and spins ROS.
void loop() {
  publishImuData();
  nh.spinOnce();
  delay(10);  // ~100 Hz
}
