/*
CAN frame arrives on the wire; the FlexCAN hardware compares its
ID against your RX mailbox filter(s) and drops the frame into the
first matching mailbox (each mailbox holds exactly one frame).
Because you called enableMBInterrupts(), that mailbox immediately
raises an interrupt, which runs the library’s ISR. The ISR’s only
job is to be fast: it copies the frame out of the hardware mailbox 
into FlexCAN_T4’s software RX ring buffer (your RX_SIZE_… queue),
then clears the mailbox so hardware is ready for the next 
frame. Later—on your schedule—your loop() calls can1.events().
That function drains the software RX queue in user space and,
for each queued frame, invokes the callback you registered 
with onReceive(canSniff). Inside canSniff(...) you’re now reading a
fully buffered message (with fields like id, len, buf, mb, timestamp) t
hat was captured earlier by the ISR. 
In short: bus → RX mailbox → (interrupt) ISR → software queue → events() → canSniff().*/

// #define DEBUG
//#define DEBUG2
#include <FlexCAN_T4.h>
#include "motor_controller/trajectory.hpp"
// #include "motor_controller/kinematics.hpp"
#include "motor_controller/motor.hpp"
#include "Wire.h"


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_32> can1;
Motor m4(can1, 6);



void find_device(){
       // ---1----LOOP through to read CANID
    CAN_message_t msg;
    msg.id = 0x300;
    msg.len = 8; 
    msg.buf[0] = 0x79;
    msg.buf[1] = 0x00;
    msg.buf[2] = 0x01;
    for(int j  = 3; j<8;j++){
        msg.buf[j] = 0x00;
    }
    if (can1.write(msg)) {
    
        Serial.println("Find device sent");
    }
    else{
        Serial.println("Failed to find");
    }
    delay(100);
    // ---2---READ reply to check which ID
    // CAN_message_t reply;
    // //should add ID check
    // while(can1.read(reply)){
    //     // Serial.print("Reply from ID: ");
    //     // Serial.println(reply.id, HEX);
    //     int device_id = reply.buf[7]<<8 | reply.buf[6];
    //     Serial.print("Device ID: ");
    //     Serial.println(device_id, HEX);
    // }
    // delay(100);
    // ---2--DONE

}
void setID(int id){
    CAN_message_t msg;
        msg.id = 0x300;
        msg.len = 8; 
        msg.buf[0] = 0x79;
        msg.buf[1] = 0x00;
        msg.buf[2] = 0x00;
        for(int j  = 3; j<7;j++){
            msg.buf[j] = 0x00;
        }
        msg.buf[7] = 0x00+id; //set ID to
        if (can1.write(msg)) {
        
            Serial.println("set  ID 1 to : " + String(id));   
        }
        else{
            Serial.println("Failed to set to ID: " + String(id));
        }
        delay(100);
}   

void canSniff(const CAN_message_t &msg) {
    Serial.print("Received on ID: 0x");
    Serial.print(msg.id, HEX);
    int device_id = msg.buf[7]<<8 | msg.buf[6];
    Serial.print("Device ID: ");
    Serial.println(device_id, HEX);
}
void setup() {
    Wire.begin();              // Teensy 4.1: SDA=18, SCL=19
    Wire.setClock(100000);     // keep conservative if wiring is long
    Serial.begin(115200);
    while (!Serial);
    can1.begin();
    can1.setBaudRate(1000000); // Set baud rate to 1Mbps(motor requirement)
    can1.enableMBInterrupts();
    can1.onReceive(canSniff);

    Serial.println("CAN bus initialized.");
    // can1.mailboxStatus();

    find_device();
    // can1.mailboxStatus();
        
    find_device();

}


void loop() {
    //  m4.write(velocity, 600);
    //  m4.system_reset();
    can1.events();

    // can1.mailboxStatus();
    // setID(6);
    // find_device();
    // while(true);
}


