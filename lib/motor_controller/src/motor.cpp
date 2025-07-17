#include "motor_controller/motor.hpp"
// #define DEBUG
// #define DEBUG2

/**
 * @brief  Write a command to the motor.
 * 
 * @param[in]  command The pvt command to send to the motor.
 * @param position: 0.01 deg
 * @param velocity: rpm
 * @param torque: 0.01 A
 *
 */
auto Motor::write(pvt command, int32_t value) ->void {
    // Implementation for writing motor commands
    CAN_message_t msg;
    msg.id = m_device;
    msg.len = 8; 
    int32_t dps = rpm_to_dps(MAX_SPEED); 

    switch (command) {
        case stop:
            msg.buf[0] = 0x81; // Stop command
            val_to_array(0,&msg.buf[1],7);  
            break;
        case pos_abs:
            msg.buf[0] = 0xA4; // Absolute position command
            val_to_array(dps, &msg.buf[2], 2); //store speed in bytes 2-4
            break;
        case pos_inc:
            msg.buf[0] = 0xA8; // Incremental position command
            val_to_array(dps, &msg.buf[2], 2); //store speed in bytes 2-4
            break;
        case velocity:
            msg.buf[0] = 0xA2; // Velocity command
            value = rpm_to_dps(value); // Convert RPM to 0.01 DPS
            val_to_array(0,&msg.buf[1],3);
            break;
        case torque:
            msg.buf[0]; // Torque command
            break;
        case release:
            msg.buf[0] = 0x80;
            val_to_array(0,&msg.buf[1],7);  
            break;
    }

    val_to_array(value, &msg.buf[4]); //store position in bytes 4-7
    
    
    if (m_can.write(msg)) {
        
        #ifdef DEBUG
        Serial.println("write command");
        #endif
    }
    else {
        Serial.println("Error sending command message: " + String(command));
    }

  
    
}

auto Motor::read_pos() -> int32_t {
    uint8_t hex = 0x92;
    CAN_message_t msg;
    uint8_t check;
    // Define the message
    msg.id = m_device;
    msg.len = 8; // Data length code (8 bytes)   
    msg.buf[0] = hex; // Absolute position command       
    
    check =hex; // Store the command byte for checking later
    for(int i =1; i<8;i++){
        msg.buf[i] = 0x00;
    }
    if (m_can.write(msg)) {
        #ifdef DEBUG
        Serial.println("Read pos command sent");
        #endif
    }
    else {
        Serial.println("Error sending read pos command message: ");
    }

    //Wait for reply
    while (true){
        if (m_can.read(msg)&&msg.buf[0]==check){
            #ifdef DEBUG
            Serial.println("Received message");
            Serial.println(msg.buf[0],HEX);
            #endif          
            //read 4-8 bytes d
            double angle = static_cast<double>(array_to_val(&msg.buf[4]));
            Serial.print("Motor ");
            Serial.print(m_device-0x140);
            Serial.print(" is at ");
            Serial.print((angle/100.0));
            Serial.println(" degrees absolute");
            return angle;
        
        }
        else{
            #ifdef DEBUG2
            Serial.println("not receiving message");
            #endif
        }
    }

}

auto Motor::publish_pos(int mode, uint32_t interval) -> void {
    CAN_message_t msg;
    msg.id = m_device;
    msg.len = 8; 
    msg.buf[0] = 0xB6;
    msg.buf[1] = 0x92; // choose abs_pos
    msg.buf[2]=mode;
    val_to_array(interval, &msg.buf[3],2); //store interval in bytes 3-4
    if (m_can.write(msg)) {
        if(mode){Serial.println("Enable position active reply");}
        else{Serial.println("Disable position active reply");}
    } else {
        Serial.println("Error sending encoder reset message");
    }

}

auto Motor::read_active_pos() -> int32_t {
        CAN_message_t msg;
        //should add ID check
        if (m_can.read(msg)&&msg.buf[0]==0x92&&msg.id==(check_id())){
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

auto Motor::write_pid(pid command, float value)->void{
    const uint8_t msg_hex = 0x32;
    CAN_message_t msg;
    
    // Define the message
    msg.id = m_device;
    msg.len = 8; // Data length code (8 bytes)

    msg.buf[0] = msg_hex;
    msg.buf[1] = static_cast<uint8_t>(command);
    val_to_array(0, &msg.buf[2], 2); // Store 0 in bytes 2-3 (not used in this case)
    float_to_array(value, &msg.buf[4],4);
    if (m_can.write(msg)) {
        #ifdef DEBUG
        Serial.println("Write PID");
        #endif
    }
    else {
        Serial.println("Error sending read PID message");
    }
    delay(5);

}

auto Motor::read_pid(pid command) -> float{
    const uint8_t msg_hex = 0x30;
    CAN_message_t msg;
    
    // Define the message
    msg.id = m_device;
    msg.len = 8; // Data length code (8 bytes)

    msg.buf[0] = msg_hex;
    msg.buf[1] = static_cast<uint8_t>(command);
    val_to_array(0, &msg.buf[2], 6); // Store 0 in bytes 2-7 (not used in this case)
    if (m_can.write(msg)) {
        #ifdef DEBUG
        Serial.println("Read PID");
        #endif
    }
    else {
        Serial.println("Error sending read PID message");
    }
    
    while (true){
        if (m_can.read(msg)){
            #ifdef DEBUG
            Serial.println("Received message");
            #endif

            if((msg.id ==check_id())&& msg.buf[0]==msg_hex){

                //read 4-8 bytes 

                float ret = array_to_float(&msg.buf[4]);
                Serial.print("PID command ");
                Serial.print(String(command));
                Serial.print(" value is: ");
                Serial.println(ret,3);
                return ret;
            }
        }
        else{
            // Serial.println("not receiving message");

        }
    }

    return -1;
}

auto Motor::system_reset() -> void {
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
            delay(1000);
            Serial.println("System Resetted");

        }

auto Motor::zero_encoder() -> void {
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
                        Serial.print("Encoder zeroed at raw pulse ");
                        Serial.println(initial);
                        system_reset();
                        break;
                    }
                } else {
                    #ifdef DEBUG
                    Serial.println("Not receiving message");
                    #endif
                }
            }
        }

auto Motor::read_accel(accel command) -> void{
    const uint8_t msg_hex = 0x42;
    CAN_message_t msg;
    
    // Define the message
    msg.id = m_device;
    msg.len = 8; // Data length code (8 bytes)

    msg.buf[0] = msg_hex;
    msg.buf[1] = static_cast<uint8_t>(command);
    val_to_array(0, &msg.buf[2], 6); // Store 0 in bytes 2-7 (not used in this case)
    if (m_can.write(msg)) {
        #ifdef DEBUG
        Serial.println("Read accel/decel");
        #endif
    }
    else {
        Serial.println("Error sending accel/decel");
    }
    
    while (true){
        if (m_can.read(msg)){
            #ifdef DEBUG
            Serial.println("Received message");
            #endif

            if((msg.id ==check_id())&& msg.buf[0]==msg_hex){
                
                //read 4-8 bytes
                float ret = array_to_val(&msg.buf[4]);
                Serial.print("accel/decel command ");
                Serial.print(String(command));
                Serial.print(" value is: ");
                Serial.println(ret);
                return;
            }
        }
        else{
            // Serial.println("not receiving message");

        }
    }

}
auto Motor::write_accel(accel command, int32_t val) -> void{
    const uint8_t msg_hex = 0x43;

    CAN_message_t msg;
    msg.id = m_device;
    msg.len = 8; 
    msg.buf[0] = msg_hex; 
    
    switch (command) {
        case accel_pos:
            msg.buf[1] = 0x00; // Stop command
            break;
        case decel_pos:
            msg.buf[1] = 0x01; // Absolute position command
            break;
        case accel_vel:
            msg.buf[1] = 0x02; // Incremental position command
            break;
        case decel_vel:
            msg.buf[1] = 0x03; // Velocity command
            for(int i =1; i<4;i++){msg.buf[i] = 0x00;}
            break;
    }
    val_to_array(0, &msg.buf[2],2); 
    val_to_array(val, &msg.buf[4]);         
    if (m_can.write(msg)) {        
        #ifdef DEBUG
        Serial.println("write accel/decel");
        #endif
    }
    else {
        Serial.println("Error sending command message: " + String(command));
    }
    delay(5);

}

