#include "motor_interface/motor.hpp"

/**
 * @brief  Write a command to the motor.
 * 
 * @param[in]  command The pvt command to send to the motor.
 * @param position: 0.01 deg
 * @param velocity: rpm
 * @param torque: 0.01 A
 *
 */
void Motor::write(pvt command, int32_t value) {
    // Implementation for writing motor commands
    CAN_message_t msg;
    msg.id = m_device;
    msg.len = 8; 
    switch (command) {
        case stop:
            msg.buf[0] = 0x81; // Stop command
            for(int i =1; i<8; i++){msg.buf[i] = 0x00;}
            break;
        case pos_abs:
            msg.buf[0] = 0xA4; // Absolute position command
            int32_t dps = rpm_to_dps(MAX_SPEED); 
            val_to_array(dps, &msg.buf[2]); //store speed in bytes 2-4
            break;
        case pos_inc:
            msg.buf[0] = 0xA8; // Incremental position command
            int32_t dps = rpm_to_dps(MAX_SPEED); 
            val_to_array(dps, &msg.buf[2]); //store speed in bytes 2-4
            break;
        case velocity:
            msg.buf[0] = 0xA2; // Velocity command
            value = rpm_to_dps(value); // Convert RPM to 0.01 DPS
            for(int i =1; i<4;i++){msg.buf[i] = 0x00;}
            break;
        case torque:
            msg.buf[0] = 0xA1; // Torque command
            break;

    val_to_array(value, &msg.buf[4]); //store position in bytes 4-7
    if (m_can.write(msg)) {
        // Serial.println("Absolute position command");
    }
    else {
        Serial.println("Error sending command message: " + String(command));
    }
    }



}

int32_t Motor::read(pvt command) {
    CAN_message_t msg;
    int8_t check;
    // Define the message
    msg.id = m_device;
    msg.len = 8; // Data length code (8 bytes)
    switch (command) {
        case pos_abs:
            msg.buf[0] = 0x92; // Absolute position command
            break;
        case pos_inc:
            msg.buf[0]; // Incremental position command
            break;
        case velocity:
            msg.buf[0]; // Velocity command
            break;
        case torque:
            msg.buf[0]; // Torque command
            break;
    }
    
    check = msg.buf[0]; // Store the command byte for checking later
    for(int i =1; i<8;i++){
        msg.buf[i] = 0x00;
    }
    if (m_can.write(msg)) {
        #ifdef DEBUG
        Serial.println("Read command sent");
        #endif
    }
    else {
        Serial.println("Error sending read command message: " + String(command));
    }

    //Wait for reply
    while (true){
        if (m_can.read(msg)){
            #ifdef DEBUG
            Serial.println("Received message");
            #endif
            if(msg.buf[0]==check){
                //read 4-8 bytes daug

                double angle = static_cast<double>(array_to_val(&msg.buf[4])/100.0);
                Serial.print("Motor ");
                Serial.print(m_device);
                Serial.print(" is at ");
                Serial.print(angle);
                Serial.println(" degrees absolute");
                break;
            }
        }
        else{
            #ifdef DEBUG2
            Serial.println("not receiving message");
            #endif
        }
    }

}

void Motor::publish_pos(int mode =1, uint32_t interval=INTERVAL){
    CAN_message_t msg;
    msg.id = m_device;
    msg.len = 8; 
    msg.buf[0] = 0xB6;
    msg.buf[1] = 0x92; // choose abs_pos
    msg.buf[2]=mode;
    val_to_array(interval, &msg.buf[3]); //store interval in bytes 3-4
    if (m_can.write(msg)) {
        if(mode){Serial.println("Enable position active reply");}
        else{Serial.println("Disable position active reply");}
    } else {
        Serial.println("Error sending encoder reset message");
    }

}

int32_t Motor::read_active_pos(){
        CAN_message_t msg;
        //should add ID check
        if (m_can.read(msg)&&msg.buf[0]==0x92&&msg.id==(m_device-0x140)){
            #ifdef DEBUG
            Serial.println("Received message");
            #endif         
            //read 4-8 bytes daug

            int32_t angle = static_cast<double>(array_to_val(&msg.buf[4]));
            Serial.print("Motor ");
            Serial.print(m_device);
            Serial.print(" is at ");
            Serial.print(angle/100.0);
            Serial.println(" degrees absolute");
        
            
            return angle;
        }
        return -1;
}   