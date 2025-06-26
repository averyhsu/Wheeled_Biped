#include "trajectory.hpp"
//1) 360 degrees in 3000 millisecond
//2) 1)--> 0.12 deggrees / ms --> 12 (0.01 degrees)/ms
//3) send frequency = 1ms
const int LOOP = 6000;

void rotate(FlexCAN& can, uint32_t device){
    uint32_t  lastSend = 0;

    int timer = 0;
    int32_t pos =0;

    unsigned long startTime = millis();       

    while((millis()-startTime)<LOOP){
        uint32_t now = micros();
        if (now - lastSend >= 1000000) { //check in microseconds to be precise
            lastSend = now;
            timer=timer+150;
            // pos = timer*12; //position fucntion based on time
            // Serial.println(pos);

            motor_control::vel(can, device,timer);         
        }


    }

}