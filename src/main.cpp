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





void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)

    Serial.println("CAN bus initialized.");
    go_to(l1,32.4,0);
    delay(300);
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

    // TEST_MOTOR.read_pid(kp_pos);
    // TEST_MOTOR.read_pid(ki_pos);
    // TEST_MOTOR.read_pid(kd_pos);

    // TEST_MOTOR.write_pid(kp_pos, 0.1);//0.1
    // delay(100);
    // TEST_MOTOR.write_pid(ki_pos, 0.0); //0.001
    // delay(100);
    // TEST_MOTOR.write_pid(kd_pos, 60); //0.5
    // delay(100);

    // TEST_MOTOR.read_pid(kp_pos);
    // TEST_MOTOR.read_pid(ki_pos);
    // TEST_MOTOR.read_pid(kd_pos);
    // delay(100);

 
    /*CHANGE ACCELERATION*/

    m1.write_accel(accel_pos, 40000);
    delay(300);
    m1.read_accel(accel_pos);
    delay(100);


    m2.write_accel(accel_pos, 40000);
    delay(300);
    m2.read_accel(accel_pos);
    delay(100);



    /*TEST MOVE COMMANDS*/

    // TEST_MOTOR.read_pos();
    // delay(500);
    // m1.write(stop);
    // TEST_MOTOR.write(pos_abs, 2000);
    // // rotate(TEST_MOTOR);
    // delay(500);
    // TEST_MOTOR.read_pos();
    // delay(5000);

    /*REAL MOVE*/
    double width =5;
  
    go_to(l1, 16-width, 0-width);
    delay(500);
    for(int i =0; i<1;i++){
        square(l1, width);
    }

    // delay(10000);
    // m1.write(release);
    // m2.write(release);
    while(true);    
}

