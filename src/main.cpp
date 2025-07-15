// #define DEBUG
//#define DEBUG2
#include <FlexCAN_T4.h>
#include "motor_controller/trajectory.hpp"
// #include "motor_controller/kinematics.hpp"
#include "motor_controller/motor.hpp"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
inline const int TEST_MOTOR = 3;
Motor m3 (can1, 3);



void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)

    Serial.println("CAN bus initialized.");
    m3.zero_encoder();
    // #ifdef DEBUG
    //     Serial.println("Debug mode is ON");
    //     motor_system::change_pid(can1);

    // #endif
    // m3.zero_encoder();

    // motor_control::zero_encoder(can1, TEST_MOTOR);
    // motor_control::get_pos_abs(can1, TEST_MOTOR);

}

void loop() {
    // delay(1000);
    // m3.write(velocity, 60);
    // delay(2000);
    // m3.write(stop);
    // delay(1000);
    // m3.read_pid(kp_pos);
    // m3.read_accel(accel_pos);
    // m3.read_accel(accel_pos);

    m3.write(stop);
    m3.read_pos();

    m3.write_accel(accel_pos, 60000);
    delay(300);
    m3.write_accel(decel_pos, 5000);


    m3.read_accel(accel_pos);
    m3.read_accel(decel_pos);
    m3.read_accel(accel_vel);
    m3.read_accel(decel_vel);
    rotate(m3);
    delay(500);
    m3.read_pos();

    

 
    // #ifdef DEBUG
    //     Serial.println("Main Debug");
    // #endif

    // go_to(can1, 10, 13);

    // motor_control::vel(can1, TEST_MOTOR, 60);
    // delay(1500);
    // motor_control::stop(can1, TEST_MOTOR);
    // delay(300);
    // motor_control::get_pos_abs(can1, TEST_MOTOR);




    while(true);    
}

