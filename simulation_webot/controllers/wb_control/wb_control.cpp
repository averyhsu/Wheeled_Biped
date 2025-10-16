#include <webots/Robot.hpp>
#include <iostream>
#include <webots/InertialUnit.hpp>
#include <webots/Motor.hpp>
#include <math.h>
#include "simplePID_class.hpp"
#include <algorithm>

const double PI = 3.14159265358979323846;
const double BENT = 0;
const double target_vel = 0;

double Kp1 = 7;
; // Proportional gain 7
double Ki1 = 0.9; // Integral gain 0.9
double Kd1 = 6; // Derivative gain 6
double scale_factor1 = 5.0;
PIDController pid1(Kp1, Ki1, Kd1); //Kp, Ki, Kd

double Kp2 = 1.9
; // Proportional gain
double Ki2 = 0.04; // Integral gain
double Kd2 = 0.09; // Derivative gain
double scale_factor2 = 0.01;
PIDController pid2(Kp2, Ki2, Kd2); //Kp, Ki, Kd

//time step in milliseconds
int TIME_STEP = 1;

using namespace webots;

double deg_to_rad(double deg){
  return deg*PI/180;
}


int main() {

  //INITIALIZATION  
  // int timer =0;
  Robot *robot = new Robot();
  InertialUnit *imu = robot->getInertialUnit("imu");
  Motor *right_wheel = robot ->getMotor("right_wheel_joint");
  Motor *left_wheel = robot ->getMotor("left_wheel_joint");
  Motor *right_knee= robot ->getMotor("right_knee_joint");
  Motor *left_knee = robot ->getMotor("left_knee_joint");
  Motor *right_hip = robot ->getMotor("right_hip_joint");
  Motor *left_hip = robot ->getMotor("left_hip_joint");
  right_wheel->setPosition(std::numeric_limits<double>::infinity());
  left_wheel->setPosition(std::numeric_limits<double>::infinity());
  if (!imu) {
    std::cerr << "Error: InertialUnit 'imu' not found. Check the device name." << std::endl;
    delete robot;
    return 1;
  }
  imu->enable(TIME_STEP);
  
  
  //Begin control
  //Zero everything
  right_hip->setPosition(deg_to_rad(-BENT));
  left_hip->setPosition(deg_to_rad(-BENT));
  right_knee->setPosition(deg_to_rad(2*BENT));
  left_knee->setPosition(deg_to_rad(2*BENT));

  right_wheel->setVelocity(0);
  left_wheel->setVelocity(0);
  
//Initialize variable 
  double right_vel = 0;
  double left_vel = 0;
  double cur_vel  = 0;
  double e_vel = 0;
  double target_theta = 0;

  const double *rpy = NULL;
  double output =0;

  

  while (robot->step(TIME_STEP) != -1)
  {

    /*------PID #2 wheel velocity -> target pitch-------*/
    right_vel = right_wheel->getVelocity();
    left_vel = left_wheel->getVelocity();
    cur_vel  = (right_vel+left_vel)/2.0;
    e_vel = cur_vel-0.0;
    std::cout << "cur_vel: " << cur_vel << std::endl;

    target_theta = -1*std::clamp(scale_factor2*pid2.calculateControlSignal(target_vel, e_vel),-PI/2, PI/2);
    std::cout << "Target Theta: " << target_theta*180.0/PI << std::endl;
    /*------PID #2 END-------*/
   
    /*------PID #1 INPUT -> OUTPUT: pitch -> wheel velocity-------*/
    //API outputs in radians
    rpy = imu->getRollPitchYaw();  
    std::cout << "Pitch: " << rpy[1]*180.0/PI <<"\n"<<"\n"<< std::endl;
    std::cout << ""<<std::endl;

    output = std::clamp(scale_factor1*pid1.calculateControlSignal(target_theta, rpy[1]),-60.0, 60.0);
    std::cout << "Output: " << output<< std::endl;
    right_wheel->setVelocity(output);
    left_wheel->setVelocity(output);
    /*------PID #1 END-------*/


  }
  delete robot;
  return 0;
}