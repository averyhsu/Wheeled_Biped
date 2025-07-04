// #define DEBUG
#include <FlexCAN_T4.h>
#include "motor_interface/motor_controller.hpp"
#include "motor_interface/trajectory.hpp"


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
inline const int TEST_MOTOR_ID = 2;


void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Hello");

    
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)

    Serial.println("CAN bus initialized.");
    #ifdef DEBUG
        Serial.println("Debug mode is ON");
        motor_system::change_pid(can1);

    #endif

    motor_control::zero_encoder(can1, 1);
    motor_control::zero_encoder(can1, 2);
    motor_control::get_pos_abs(can1, 1);
    motor_control::get_pos_abs(can1, 2);



}

void loop() {

 
    #ifdef DEBUG
        Serial.println("Main Debug");
    #endif

    go_to(can1, 10, 13);

    delay(3000);
    motor_control::get_pos_abs(can1, 1);
    motor_control::get_pos_abs(can1, 2);




    while(true);    
}

