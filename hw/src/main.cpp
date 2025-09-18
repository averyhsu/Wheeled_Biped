// #define DEBUG
//#define DEBUG2
#include <FlexCAN_T4.h>
#include "motor_controller/trajectory.hpp"
// #include "motor_controller/kinematics.hpp"
#include "motor_controller/motor.hpp"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
Motor m1(can1, 1);
Motor m2(can1, 2);
Motor m3 (can1, 3);
Leg l1 = {m1, m2};

Motor TEST_MOTOR = m1;
Motor motors[] = {m1, m2, m3};





void setup() {
    Serial.begin(115200);
    while (!Serial);
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)

    Serial.println("CAN bus initialized.");
    go_to(l1,32.4,0);
    delay(500);
    m1.zero_encoder();
    m2.zero_encoder();
    // m3.zero_encoder();

    // #ifdef DEBUG
    //     Serial.println("Debug mode is ON");
    //     motor_system::change_pid(can1);

    // #endif
}

void loop() {


    /*PID*/
    // m1.write_pid(kp_pos, 0.025); //0.5

    // m1.write_pid(kd_pos, 20); //0.5

    for(int i =0; i<1; i++){
        motors[i].read_pid(kp_pos);
        motors[i].read_pid(ki_pos);
        motors[i].read_pid(kd_pos);

        // motors[i].write_pid(kp_pos, 0.1);//0.1
        // delay(100);
        // motors[i].write_pid(ki_pos, 0.0); //0.001
        // delay(100);
        // motors[i].write_pid(kd_pos, 60); //0.5
        // delay(100);

        // motors[i].read_pid(kp_pos);
        // motors[i].read_pid(ki_pos);
        // motors[i].read_pid(kd_pos);
    }
    
    // delay(100);

 
    /*CHANGE ACCELERATION*/
    for(int i =0; i<1; i++){
        motors[i].read_accel(accel_pos);
        motors[i].read_accel(decel_pos);

    }
    // m1.write_accel(accel_pos, 40000);
    // delay(300);
    // m1.read_accel(accel_pos);
    // delay(100);


    // m2.write_accel(accel_pos, 40000);
    // delay(300);
    // m2.read_accel(accel_pos);
    // delay(100);



    /*TEST MOVE COMMANDS*/

        // m2.write(pos_abs, -9000, 100);

    /*REAL MOVE*/
    // rotate(m1, 45);

    double width =7;
    go_to(l1, 16+width, 0);
    delay(500);
    for(int i =0; i<5;i++){
        circle(l1, width);

    }

    // delay(6500);
    // m1.write(release);
    // m2.write(release);
    while(true);    
}

