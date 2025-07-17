//1. convert RPM to DPS
//2. parse number in eight 8 bytes array
// #define Debug
#pragma once
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <array>
#include <cassert> //cpp assertion library
#include <iomanip>   
#include <string>
#include <cstring>

inline constexpr int DEVICE_NUM = 3;
inline constexpr uint32_t ALL = 0;
inline constexpr int MAX_SPEED = 800; //805
inline constexpr int MIN_SPEED = -805;//-805
inline constexpr uint32_t CMD_PERIOD_US = 1000;   // 1 kHz  (1000 µs)
inline constexpr uint32_t INTERVAL=10; //active reply interval unit: 10 millisecond

//Control loop frequencies
inline constexpr uint32_t TORQUE_FREQ = 70 ;//70 microseconds: 15KHZ every 0.066 ms =~ 70 microseconds
inline constexpr uint32_t SPEED_FREQ = 200; //200 microseconds: 5KHZ every 0.2 ms = 200 microseconds
inline constexpr uint32_t POS_FREQ = 1000; //1000 microseconds: 1KHZ = every 1 ms =1000 microseconds

using FlexCAN =  FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>&; //reference value to create adiitional copies
enum accel{
    accel_pos=0,
    decel_pos= 1,
    accel_vel = 2,
    decel_vel =3,          
    };
enum pvt{
    stop=0,
    pos_abs=1, 
    pos_inc=2,
    velocity=3,
    torque=4, 
    release=5,           
    };
enum pid{
    invalid=0,    //0
    kp_torque=1,  //1
    ki_torque=2,  //2
    kp_vel=4,     //3
    ki_vel=5,     //4
    kp_pos=7,     //5
    ki_pos=8,     //6
    kd_pos=9,     //7
};

class Motor{
    private:
        FlexCAN m_can;
        uint32_t m_device{};
        uint32_t m_pos{};
        uint32_t m_vel{};
        uint32_t m_torque{};

        //Assigns device ID
        auto id_assignment (uint32_t device) -> uint32_t {
            if (device ==0){ return 0x280;}
            else{ return 0x140+device; }
        }
        
        auto check_id()->int{
            return m_device-0x140+0x240; //check ID for reading
        }

        auto rpm_to_dps(int32_t rpm) -> int32_t{
            int32_t res = (rpm/60);     //to rps
            res = res*360;              //to dps
            res = res*100;              //to 0.01 dps
            return res;
        }

        auto val_to_array(int32_t data, uint8_t* arr, int element=4) -> void{
            uint32_t uData= static_cast<uint32_t>(data);        //no sign extension when right shifting with unsigned (maintains correct two's complement binary)

            for(int i = 0; i<element; i++){
                
                arr[i]= static_cast<uint8_t>(uData & 0xff);   //grab LSB --> cast
                uData = uData>>8;

                #ifdef DEBUG    
                // std::cout << std::hex<<static_cast<int>(arr[i])<<'\n';
                #endif
            }
        }
        
        auto float_to_array(float data, uint8_t* arr, int element = 4) -> void {
            uint32_t uData;
            std::memcpy(&uData, &data, sizeof(float));  // Bitcast float to uint32_t safely

            for (int i = 0; i < element; i++) {
                arr[i] = static_cast<uint8_t>(uData & 0xFF);  // Extract LSB
                uData = uData >> 8;

                #ifdef DEBUG
                // std::cout << std::hex << static_cast<int>(arr[i]) << '\n';
                #endif
            }
        }

        auto array_to_val(uint8_t* arr, int element=4) -> int32_t {
            uint32_t res=0;
            for(int i = 0; i<element; i++){
                res = res|(static_cast<uint32_t>(arr[i]) <<(8*i)); //grab LSB --> cast for no sign extension
            }
            return static_cast<int32_t>(res);
        }
        
        auto array_to_float(uint8_t* arr, int element =4) -> float {
            uint32_t res = 0;
            for (int i = 0; i < element; ++i) {
                res |= static_cast<uint32_t>(arr[i]) << (8 * i);  // Little-endian
            }
            float result;
            std::memcpy(&result, &res, sizeof(float));  // Bitcast safely
            return result;
        }

    
    public:
        
        // Constructor to initialize the motor with a FlexCAN instance and device ID
        Motor(FlexCAN can, uint32_t device) : m_can{can}, m_device{id_assignment(device)} {};

        /**
         * @brief Write a command to the motor.
         * 
         * @param[in]  command The pvt command to send to the motor.
         * @param position: 0.01 deg
         * @param velocity: rpm
         * @param torque: 0.01 A
         */
        auto write(pvt command, int32_t value=0) -> void;

        /**
         * @brief Read motor position.
         * 
         * @param[in]  command The pvt command to read from the motor.
         * @param position: 0.01 deg/prints deg
         * @param velocity: rpm
         * @param torque: 0.01 A
         */
        auto read_pos() -> int32_t;

        auto publish_pos(int mode =1, uint32_t interval=INTERVAL) -> void;
        auto read_active_pos() -> int32_t;
        
        /**
         * @brief Resets the System. 
         *        This is needed after zero-ing encoder
         */
        auto system_reset() -> void;

        auto zero_encoder() -> void;
        
        auto read_pid(pid command) -> float;
        auto write_pid(pid command, float value)->void;
        auto read_accel(accel command) -> void;
        auto write_accel(accel command, int32_t val) -> void;
    };