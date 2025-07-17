#pragma once
#include "motor.hpp"
#include "kinematics.hpp"
struct Leg {
    Motor motor1;
    Motor motor2;
};

void rotate(Motor device);
void go_to(Leg leg, double x, double y);
void circle(Leg leg, double radius);