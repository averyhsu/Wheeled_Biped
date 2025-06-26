//1. convert RPM to DPS
//2. parse number in eight 8 bytes array
#pragma once
#define DEBUG
#include <FlexCAN_T4.h>
#include <array>
#include <cassert> //cpp assertion library
#include <iostream>
#include <iomanip>   
#include <string>
inline constexpr int MAX_SPEED = 805;
inline constexpr int MIN_SPEED = -805;
inline constexpr uint32_t CMD_PERIOD_US = 1000;   // 1 kHz  (1000 µs)
inline constexpr uint32_t ALL = 0;
//Control loop frequencies
inline constexpr uint32_t TORQUE_FREQ = 15 ;//KHZ every 0.066 ms
inline constexpr uint32_t SPEED_FREQ = 5; //KHZ every 0.2 ms
inline constexpr uint32_t POS_FREQ = 1; //KHZ = every 1 ms





using FlexCAN = FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>;

namespace motor_control{
    void stop (FlexCAN can, uint32_t device);
    void vel (FlexCAN can, uint32_t device, int32_t rpm);
    void pos_inc (FlexCAN can, uint32_t device, int32_t deg, int32_t rpm);
    void pos_abs (FlexCAN can, uint32_t device, int32_t deg, int32_t rpm);
    void system_reset(FlexCAN can, uint32_t device);
    void zero_encoder (FlexCAN can, uint32_t device);
    void get_pos_abs(FlexCAN can, uint32_t device);




}


