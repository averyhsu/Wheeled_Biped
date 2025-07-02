#pragma once
#include <iostream>
#include <cmath>
const double L1 = 17.5; //mm
const double L2 = 15.0; //mm


struct Angles {
    int theta1; // in 0.01 degrees
    int theta2; // in 0.01 degrees
};

namespace IK {
    auto inverse_kinematics(double x, double y) -> Angles;
    auto test() -> int;
}
