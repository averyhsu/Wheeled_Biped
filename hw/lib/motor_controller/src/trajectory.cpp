#include "motor_controller/trajectory.hpp"
#include <Arduino.h>

//motor initialization

//The idea is to find the best #DELAY matched with STEP_WIDTH that allows the motor to move smoothly without losing data.
//This is for IK: 
//Current matches:
// 1. 120 (1.2): 30
// 2. 1200 (12) : 20  --> for some reason I can push a faster loop 

void rotate(Motor device){
        //1) 360 degrees in 3000 millisecond
    //2) 1)--> 0.12 deggrees / ms --> 12 (0.01 degrees)/ms
    //3) send frequency = 1ms
    const int DEGREES = 30*100; //360 degrees = 36000 (0.01 degrees)
    const int STEP_WIDTH = 50; //12 degrees = 1200 (0.01 degrees)
    const int DELAY = 1000; //in micros: 1 milli = 1000 micros 1kHZ speed
    const int LOOP_TIME = (DEGREES/STEP_WIDTH)*(DELAY/1000.0); 

    Serial.println("Loop time: " + String(LOOP_TIME) + " ms");

    
    //timer initialization
    uint32_t  lastSend = 0;
    int timer = 0;
    int32_t pos =0;
    unsigned long startTime = millis();       

    while((millis()-startTime)<LOOP_TIME){
        uint32_t now = micros();
        if (now - lastSend >= DELAY) { //sebd msg every 50 milliseconds
            lastSend = now;
            timer=timer+1;
            pos = timer*STEP_WIDTH; 
            
            device.write(pos_abs, pos);
        }


    }
}
void go_to(Leg leg, double x, double y){
    //This function is not implemented yet.
    //The idea is to use the inverse kinematics to calculate the angles for each point in the trajectory
    //and then send the angles to the motor.
    //The x and y are the coordinates of the point in mm.
    
    Angles angles = IK::inverse_kinematics(x, y);
    leg.motor1.write(pos_abs, angles.theta1);
    leg.motor2.write(pos_abs, angles.theta2);
}

   
void circle (Leg leg, double radius){
    
    const int STEP_ANGLE = 250; //unit: 0.01 degrees --> 0.1 degrees step
    const int FREQ = 15000; //unit: microseconds; --> 1 millisecond = 1khz
    const int LOOP_TIME =(360.0/(STEP_ANGLE/100.0))*(FREQ/1000.0); //unit: seconds --> 3600 iterations * FREQ = total time in millis
    const int centerX = 16;
    const int centerY = 0;
    Serial.println("Loop time: " + String(LOOP_TIME) + " ms");    
    //timer initialization
    uint32_t  lastSend = 0;
    double theta = 0;
    double x;
    double y;
    unsigned long startTime = millis();       

    while((millis()-startTime)<LOOP_TIME){
        uint32_t now = micros();
        if (now - lastSend >= FREQ) { //sebd msg every 50 milliseconds
            lastSend = now;

            x = centerX+radius*cos((M_PI / 180.0)* theta);
            y = centerY+radius*sin((M_PI / 180.0)* theta);
            go_to(leg, x, y);
            theta = theta+STEP_ANGLE/100.0;
        }
    }
}

void square(Leg leg, double halfSide){
    const int STEP_ANGLE = 25;            // 0.01 units → 250 * 0.01 = 2.5 units per step
    const double STEP      = STEP_ANGLE / 100.0;  
    const int FREQ         = 10000;        // microseconds between steps
    const double sideLen   = 2 * halfSide;
    
    // how many linear steps on each side
    const int STEPS_PER_SIDE = int(sideLen / STEP);
    const int TOTAL_STEPS    = STEPS_PER_SIDE * 4;
    
    // total time (ms) = #steps * (FREQ µs / 1000)
    const int LOOP_TIME = int(TOTAL_STEPS * (FREQ / 1000.0));

    const int centerX = 16;
    const int centerY = 0;
    Serial.println("Loop time: " + String(LOOP_TIME) + " ms");

    uint32_t lastSend      = 0;
    int      stepCount     = 0;
    unsigned long startTime = millis();

    while ((millis() - startTime) < LOOP_TIME && stepCount < TOTAL_STEPS) {
        uint32_t now = micros();
        if (now - lastSend >= FREQ) {
            lastSend = now;

            int idx     = stepCount;  
            int sideNum = idx / STEPS_PER_SIDE;  // 0,1,2,3
            int pos     = idx % STEPS_PER_SIDE;  // 0 .. STEPS_PER_SIDE-1

            double x, y;
            switch (sideNum) {
                case 0: // bottom: left→right
                    x = centerX - halfSide + pos * STEP;
                    y = centerY - halfSide;
                    break;
                case 1: // right: bottom→top
                    x = centerX + halfSide;
                    y = centerY - halfSide + pos * STEP;
                    break;
                case 2: // top: right→left
                    x = centerX + halfSide - pos * STEP;
                    y = centerY + halfSide;
                    break;
                case 3: // left: top→bottom
                    x = centerX - halfSide;
                    y = centerY + halfSide - pos * STEP;
                    break;
            }

            go_to(leg, x, y);
            stepCount++;
        }
    }
}

