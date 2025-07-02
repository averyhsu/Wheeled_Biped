#include "motor_interface/trajectory.hpp"
//1) 360 degrees in 3000 millisecond
//2) 1)--> 0.12 deggrees / ms --> 12 (0.01 degrees)/ms
//3) send frequency = 1ms
const int DEGREES = 240000; //360 degrees = 36000 (0.01 degrees)
const int STEP_WIDTH = 1200; //12 degrees = 1200 (0.01 degrees)
const int DELAY = 20;
const int LOOP_TIME = (DEGREES/STEP_WIDTH)*DELAY; 

//The idea is to find the best #DELAY matched with STEP_WIDTH that allows the motor to move smoothly without losing data.
//This is for IK: 
//Current matches:
// 1. 120 (1.2): 30
// 2. 1200 (12) : 20  --> for some reason I can push a faster loop 

void rotate(FlexCAN can, uint32_t device){
    uint32_t  lastSend = 0;

    int timer = 0;
    int32_t pos =0;

    unsigned long startTime = millis();       

    while((millis()-startTime)<LOOP_TIME){
        uint32_t now = micros();
        if (now - lastSend >= DELAY*1000) { //sebd msg every 50 milliseconds
            lastSend = now;
            timer=timer+1;
            pos = timer*STEP_WIDTH; 
            

            motor_control::pos_abs(can, device,pos, MAX_SPEED);         
        }


    }
}
void circle (FlexCAN, int radius, int center_x, int center_y, int time){
    //This function is not implemented yet.
    //The idea is to use the inverse kinematics to calculate the angles for each point in the circle
    //and then send the angles to the motor.
    //The radius is in mm, the center_x and center_y are the coordinates of the center of the circle.
    //The step_width is the distance between each point in the circle.
    
}