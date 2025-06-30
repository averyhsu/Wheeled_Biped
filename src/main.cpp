// #define DEBUG
#include <FlexCAN_T4.h>
#include "controller.hpp"
#include "trajectory.hpp"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
inline const int TEST_MOTOR_ID = 2;


void setup() {
    Serial.begin(115200);
    while (!Serial);


    
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)

    Serial.println("CAN bus initialized.");
    #ifdef DEBUG
        Serial.println("Debug mode is ON");
        motor_system::change_pid(can1);

    #endif

    motor_control::zero_encoder(can1, TEST_MOTOR_ID);
    motor_control::get_pos_abs(can1, TEST_MOTOR_ID);


}

void loop() {

    //1.need to implement a timer that restricts how fast CAN frames are sent 
    //  a. I loose data if I more than 3 within 1kHZ (1ms)
    //  b. Implement smth like the 'delay(1)' below, that doesn't pause stuff ,else I'll lose data
    // motor_control::pos_abs(can1, TEST_MOTOR_ID, 9000, MAX_SPEED);
    // for(int i =0; i<4;i++)
    // {
    //         motor_control::pos_abs(can1, 1, 18000, MAX_SPEED);
    //         delay(1);
    // }

    // motor_control::pos_abs(can1, TEST_MOTOR_ID, -360000, MAX_SPEED);
    // delay(5000);
    #ifdef DEBUG
        Serial.println("Main Debug");
    #endif
    // delay(1000);
    rotate(can1, TEST_MOTOR_ID);
    // delay(2000);
    // motor_control::stop(can1, TEST_MOTOR_ID);
    // for(int i = 0; i < 300; i++)
    // {
    //     motor_control::pos_inc(can1, TEST_MOTOR_ID, 120, MAX_SPEED);
    //     delay(50);
    // }
    // motor_control::pos_abs(can1, TEST_MOTOR_ID, 120, MAX_SPEED);
    delay(1000);
    motor_control::get_pos_abs(can1, TEST_MOTOR_ID);




    while(true);
  
    
}

