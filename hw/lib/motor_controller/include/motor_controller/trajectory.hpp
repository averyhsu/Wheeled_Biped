#pragma once
#include "motor.hpp"
#include "kinematics.hpp"
struct Leg {
    Motor motor1;
    Motor motor2;
};

void rotate(Motor device, int degrees=90);
void go_to(Leg leg, double x, double y, int speed=40);
void circle(Leg leg, double radius);
void square(Leg leg, double halfSide);
