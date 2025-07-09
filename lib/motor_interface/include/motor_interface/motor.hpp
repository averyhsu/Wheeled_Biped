//1. convert RPM to DPS
//2. parse number in eight 8 bytes array
#pragma once
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <array>
#include <cassert> //cpp assertion library
#include <iomanip>   
#include <string>
inline constexpr int DEVICE_NUM = 3;
inline constexpr int MAX_SPEED = 805; //805
inline constexpr int MIN_SPEED = -805;//-805
inline constexpr uint32_t CMD_PERIOD_US = 1000;   // 1 kHz  (1000 µs)
inline constexpr uint32_t ALL = 0;
inline constexpr uint32_t INTERVAL=10; //active reply interval unit: 10 millisecond

//Control loop frequencies
inline constexpr uint32_t TORQUE_FREQ = 70 ;//70 microseconds: 15KHZ every 0.066 ms =~ 70 microseconds
inline constexpr uint32_t SPEED_FREQ = 200; //200 microseconds: 5KHZ every 0.2 ms = 200 microseconds
inline constexpr uint32_t POS_FREQ = 1000; //1000 microseconds: 1KHZ = every 1 ms =1000 microseconds

using FlexCAN =  FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16>&; //reference value to create adiitional copies


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
        
        auto rpm_to_dps(int32_t rpm) -> int32_t{
            int32_t res = (rpm/60);     //to rps
            res = res*360;              //to dps
            res = res*100;              //to 0.01 dps
            return res;
        }

        auto val_to_array(int32_t data, uint8_t* bytes) -> void{
            uint32_t uData= static_cast<uint32_t>(data);        //no sign extension when right shifting with unsigned (maintains correct two's complement binary)

            for(int i = 0; i<4; i++){
                
                bytes[i]= static_cast<uint8_t>(uData & 0xff);   //grab LSB --> cast
                uData = uData>>8;

                #ifdef DEBUG    
                // std::cout << std::hex<<static_cast<int>(bytes[i])<<'\n';
                #endif
            }

        }
       
        auto array_to_val(uint8_t* data) -> int32_t {
            int32_t res=0;
            for(int i = 0; i<4; i++){
                res = res|(static_cast<int32_t>(data[i]) <<(8*i)); //grab LSB --> cast
            }
            return res;
        }

    
    public:
        enum pvt
        {
            stop=0,
            pos_abs=1, 
            pos_inc=2,
            velocity=3,
            torque=4,            
        };

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
        auto write(pvt command, int32_t value) -> void;

        /**
         * @brief Read motor data.
         * 
         * @param[in]  command The pvt command to read from the motor.
         * @param position: 0.01 deg/prints deg
         * @param velocity: rpm
         * @param torque: 0.01 A
         */
        auto read(pvt command) -> int32_t;

        auto publish_pos(int mode =1, uint32_t interval=INTERVAL) -> void;
        auto read_active_pos() -> int32_t;
        /**
         * @brief Resets the System. 
         *        This is needed after zero-ing encoder
         */
        auto system_reset() -> void {
            CAN_message_t msg;
            msg.id = m_device;
            msg.len = 8; 
            msg.buf[0] = 0x76; // System reset command
            for(int i =1; i<8; i++){msg.buf[i] = 0x00;}
            if (m_can.write(msg)) {
                #ifdef DEBUG
                Serial.println("System reset sent");
                #endif
            } else {
                Serial.println("Error sending system reset message");
            }
            delay(300);
            Serial.println("System Resetted");

        }

        auto zero_encoder() -> void {
            CAN_message_t msg;
            msg.id = m_device;
            msg.len = 8; 
            msg.buf[0] = 0x64; // Zero encoder command
            for(int i =1; i<8; i++){msg.buf[i] = 0x00;}
            if (m_can.write(msg)) {
                #ifdef DEBUG
                Serial.println("Zero encoder command sent");
                #endif
            } else {
                Serial.println("Error sending zero encoder message");
            }

            // Wait for reply
            while (true) {
                if (m_can.read(msg)) {
                    #ifdef DEBUG
                    Serial.println("Received message");
                    #endif
                    if ((msg.buf[0] == 0x64)) {

                        int32_t initial = array_to_val(&msg.buf[4]);
                        system_reset();
                        Serial.print("Encoder zeroed at raw pulse");
                        Serial.println(initial);
                        break;
                    }
                } else {
                    #ifdef DEBUG
                    Serial.println("Not receiving message");
                    #endif
                }
            }
        }
};