#pragma once
#include "motor_controller.hpp"
#include "kinematics.hpp"

void rotate(FlexCAN can, uint32_t device);
void go_to(FlexCAN can, double x, double y);
