//1. convert RPM to DPS
//2. parse number in eight 8 bytes array
#pragma once
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <array>
#include <cassert> //cpp assertion library
#include <iostream>
#include <iomanip>   
#include <string>
inline constexpr int DEVICE_NUM = 3;
inline constexpr int MAX_SPEED = 805;
inline constexpr int MIN_SPEED = -805;
inline constexpr uint32_t CMD_PERIOD_US = 1000;   // 1 kHz  (1000 µs)
inline constexpr uint32_t ALL = 0;
//Control loop frequencies
inline constexpr uint32_t TORQUE_FREQ = 70 ;//70 microseconds: 15KHZ every 0.066 ms =~ 70 microseconds
inline constexpr uint32_t SPEED_FREQ = 200; //200 microseconds: 5KHZ every 0.2 ms = 200 microseconds
inline constexpr uint32_t POS_FREQ = 1000; //1000 microseconds: 1KHZ = every 1 ms =1000 microseconds





using FlexCAN =  FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>&; //reference value to create adiitional copies

namespace parsing{
    enum class Pid{
        invalid,
        kp_torque,
        ki_torque,
        kp_vel,
        ki_vel,
        kp_pos,
        ki_pos,
        kd_pos,
    };
    
    struct PIDInfo {
        uint32_t device_id;
        Pid pid;
        int target_value;
    };

}
namespace motor_system{
    int read_pid(FlexCAN can, uint32_t device, parsing::Pid pid);
    void change_pid(FlexCAN can);
}
namespace motor_control{
    
    void stop (FlexCAN can, uint32_t device);
    void vel (FlexCAN can, uint32_t device, int32_t rpm);
    void pos_inc (FlexCAN can, uint32_t device, int32_t deg, int32_t rpm);
    void pos_abs (FlexCAN can, uint32_t device, int32_t deg, int32_t rpm);
    void get_pos_abs(FlexCAN can, uint32_t device);

    void system_reset(FlexCAN can, uint32_t device);
    void zero_encoder (FlexCAN can, uint32_t device);

}


