#include "Wire.h"
#include "imu_class.hpp"
#include "simplePID_class.hpp"
#include "motor_controller/motor.hpp"
#include <FlexCAN_T4.h>

double Kp = 0.5; // Proportional gain
double Ki = 0.0; // Integral gain
double Kd = 0.1; // Derivative gain
double scale_factor = 10.0;
IMU imu;
PIDController pid(Kp, Ki, Kd); //Kp, Ki, Kd

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
Motor m3 (can1, 3);


double measuredRoll = 0.0;
double setpoint = 0.0;


void setup() {
    Serial.begin(115200);
    Wire.begin();              // Teensy 4.1: SDA=18, SCL=19
    Wire.setClock(100000);     // keep conservative if wiring is long
    imu.initialize();
    if (float* rpy = imu.poll()) {
        //calibrate initial position as setpoint
        setpoint = rpy[0];
        measuredRoll = rpy[0];

    }

    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)
    Serial.println("CAN bus initialized.");
  
}

void loop() {

    if (float* rpy = imu.poll()) {
        measuredRoll = rpy[0];
    }
    double measuredValue = measuredRoll;
    double controlSignal = pid.calculateControlSignal(setpoint, measuredValue);
    double output = controlSignal*scale_factor;//scale to suitable range for motor command
    m3.write(velocity, output); //velocity in rpm

    Serial.print("Control Signal: ");
    Serial.println(output);
}
