#include <webots/Robot.hpp>
#include <iostream>
#include <webots/InertialUnit.hpp>
#include <webots/Motor.hpp>
#include <math.h>
#include "simplePID_class.hpp"


double Kp = 3.0; // Proportional gain
double Ki = 1.5; // Integral gain
double Kd = 1.5; // Derivative gain
double scale_factor = 50.0;
PIDController pid(Kp, Ki, Kd); //Kp, Ki, Kd

//time step in milliseconds
int TIME_STEP = 1;

using namespace webots;

int main() {
  
  // int timer =0;
  Robot *robot = new Robot();
  InertialUnit *imu = robot->getInertialUnit("imu");
  Motor *right_wheel = robot ->getMotor("right_wheel_joint");
  Motor *left_wheel = robot ->getMotor("left_wheel_joint");
  Motor *right_knee= robot ->getMotor("right_knee_joint");
  Motor *left_knee = robot ->getMotor("left_knee_joint");
  Motor *right_hip = robot ->getMotor("right_hip_joint");
  Motor *left_hip = robot ->getMotor("left_hip_joint");
  right_wheel->setPosition(INFINITY);
  left_wheel->setPosition(INFINITY);
  if (!imu) {
    std::cerr << "Error: InertialUnit 'imu' not found. Check the device name." << std::endl;
    delete robot;
    return 1;
  }
  imu->enable(TIME_STEP);
  
  
  //Begin control

  right_knee->setPosition(0);
  left_knee->setPosition(0);

  //size 3 aeray: r:p:y
  while (robot->step(TIME_STEP) != -1)
  {
    // timer++;
    // if(timer<1000) break;
    const double *rpy = imu->getRollPitchYaw();  
    std::cout << "Pitch: " << rpy[1]*180.0/3.14159265359 << std::endl;
    double output = scale_factor*pid.calculateControlSignal(0, rpy[1]);
    std::cout << "Output: " << output<< std::endl;
    right_wheel->setVelocity(output);
    left_wheel->setVelocity(output);


  }
  delete robot;
  return 0;
}