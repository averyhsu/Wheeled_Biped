#include <FlexCAN_T4.h>
#include "controller.hpp"
#include "trajectory.hpp"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;




void setup() {
    Serial.begin(115200);
    while (!Serial);


    
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)

    Serial.println("CAN bus initialized.");
    motor_control::zero_encoder(can1, 1);
    motor_control::get_pos_abs(can1, 1);


}

void loop() {

    //1.need to implement a timer that restricts how fast CAN frames are sent 
    //  a. I loose data if I more than 3 within 1kHZ (1ms)
    //  b. Implement smth like the 'delay(1)' below, that doesn't pause stuff ,else I'll lose data
    // motor_control::pos_abs(can1, 1, 9000, MAX_SPEED);
    // for(int i =0; i<4;i++)
    // {
    //         motor_control::pos_abs(can1, 1, 18000, MAX_SPEED);
    //         delay(1);
    // }

    // motor_control::pos_abs(can1, 1, -360000, MAX_SPEED);
    // delay(5000);

    rotate(can1, 1);
    delay(5000);
    motor_control::get_pos_abs(can1, 1);
    motor_control::stop(can1,1);




    while(true);
  
    
}

