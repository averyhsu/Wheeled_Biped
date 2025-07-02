#include "motor_interface/motor_controller.hpp"

namespace parsing{

    

    //parser() takes in an int32_t and converts it into 4 byte hexa decimal from LSB to MSB (small to big)
    auto int_to_array(int32_t data) -> std::array<uint8_t, 4>{
        std::array<uint8_t,4> bytes = {};
        uint32_t uData= static_cast<uint32_t>(data);        //no sign extension when right shifting with unsigned (maintains correct two's complement binary)

        for(int i = 0; i<4; i++){
            
            bytes[i]= static_cast<uint8_t>(uData & 0xff);   //grab LSB --> cast
            uData = uData>>8;

            #ifdef DEBUG    
            // std::cout << std::hex<<static_cast<int>(bytes[i])<<'\n';
            #endif
        }
        return bytes;
    }
    auto array_to_int(std::array<uint8_t, 4> data)->int32_t{
        int32_t res=0;
        for(int i = 0; i<4; i++){
            res = res|(static_cast<int32_t>(data[i]) <<(8*i)); //grab LSB --> cast
            
        }
        return res;
    }

    //Actually convert rpm to 0.01 dps (degree per second)
    auto rpm_to_dps(int32_t rpm) -> int32_t{
        int32_t res = (rpm/60);     //to rps
        res = res*360;              //to dps
        res = res*100;              //to 0.01 dps
        return res;
    }
    
    //Assigns device ID
    auto id_assignment (uint32_t device) -> uint32_t {
        if (device ==0){
            return 0x280;
        }
        else{
            return 0x140+device; 
        }
    }

    auto read_pid_change_target(FlexCAN can) -> PIDInfo {
        Serial.setTimeout(5000);

        PIDInfo pid_info={};
            while(true){        
                
                    Serial.println("Please make changes to PID gains");
                    Serial.print("Enter Target Device ID (0-");
                    Serial.print(DEVICE_NUM);
                    Serial.print("): ");
                    int device = Serial.parseInt();
                    if (device < 0 || device > DEVICE_NUM) {
                        Serial.println("Invalid device ID");
                        continue;
                    }
                    Serial.println(device);
                    pid_info.device_id = device;                 
                    break;
                
            }
            while(true){
                // Input PID to change
                Serial.println("");
                Serial.print("Enter Target PID (0-");
                Serial.print(static_cast<int>(Pid::kd_pos));
                Serial.println("): ");
                Serial.println("1: kp_torque");
                Serial.println("2: ki_torque");
                Serial.println("3: kp_vel");
                Serial.println("4: ki_vel");
                Serial.println("5: kp_pos");
                Serial.println("6: ki_pos");    
                Serial.println("7: kd_pos");
                int pid = Serial.parseInt();
                if (pid < 0 || pid > static_cast<int>(Pid::kd_pos)|| pid == static_cast<int>(Pid::invalid)) {
                    Serial.println("Invalid PID");
                    continue;
                }
                Serial.println(pid);
                pid_info.pid = static_cast<Pid>(pid);
                break;

            }
            int current_value = motor_system::read_pid(can, pid_info.device_id, pid_info.pid);
            Serial.print("Current PID value is: ");
            Serial.println(current_value);
            

            while (true){
                Serial.print("Enter New PID value:");
                int target = Serial.parseInt();
                if (target <= 0){
                    Serial.println("Invalid PID value");
                    continue;
                }
                Serial.println(target);
                pid_info.target_value = target;
                break;
            }
        
        return pid_info;

    }
}

namespace motor_system{
    //0x30 read PID
    int read_pid(FlexCAN can, uint32_t device, parsing::Pid pid){
        const uint8_t msg_hex = 0x30;
        CAN_message_t msg;
       
        // Define the message
        msg.id = parsing::id_assignment(device);
        msg.len = 8; // Data length code (8 bytes)

        msg.buf[0] = msg_hex;
        msg.buf[1] = static_cast<uint8_t>(pid);
        for(int i =2; i<8;i++){
            msg.buf[i] = 0x00;
        }
        if (can.write(msg)) {
            Serial.println("Read PID command");
        }
        else {
            Serial.println("Error sending read PID message");
        }

         while (true){
            if (can.read(msg)){
                #ifdef DEBUG
                Serial.println("Received message");
                #endif

                if(/*(msg.id ==0x240+device)&&*/ msg.buf[0]==msg_hex){

                    //read 4-8 bytes 
                    std::array<uint8_t,4> data = {};
                    for(int i = 0; i<4;i++){
                        data[i]=msg.buf[i+4]; //plus 4 for where the data field starts
                    }
                    int ret = parsing::array_to_int(data);
                    Serial.print("PID value is: ");
                    Serial.println(ret);
                    return ret;
                }
            }
            else{
                // Serial.println("not receiving message");

            }
        }
    }

    void change_pid(FlexCAN can){
        //Read PID 
        parsing::PIDInfo pid_info = parsing::read_pid_change_target(can);
        if(pid_info.device_id == 0){
            Serial.println("Change PID for all devices");
        }
        else{
            Serial.print("Change PID for device: ");
            Serial.println(pid_info.device_id);
        }
        // int current_value = motor_system::read_pid(can, pid_info.device_id, pid_info.pid);
        // Serial.print("Current PID value: ");
        // Serial.println(current_value);

        //Prepare the msg
        const uint8_t msg_hex = 0x32;
        CAN_message_t msg;
       
        // Define the sending msg
        msg.id = parsing::id_assignment(pid_info.device_id);
        msg.len = 8; // Data length code (8 bytes)

        msg.buf[0] = msg_hex;
        msg.buf[1] = static_cast<uint8_t>(pid_info.pid);
        for(int i =2; i<4;i++){
            msg.buf[i] = 0x00;
        }
        //Send new PID target
        auto data = parsing::int_to_array(pid_info.target_value);
        for(int i = 4; i < 8; i++){
            msg.buf[i] = data[i-4];
        }
        if (can.write(msg)) {
            Serial.println("Change PID command");
        }
        else {
            Serial.println("Error sending change PID message");
        }
        delay(500);//delay
        Serial.println("Done changing PID");
        motor_control::system_reset(can, pid_info.device_id); 
        //double check if the PID is changed
        int current_value = motor_system::read_pid(can, pid_info.device_id, pid_info.pid);
        Serial.println("");
        Serial.print("Confirm PID value is: ");
        Serial.println(current_value);
        Serial.println("");

    }

}
namespace motor_control{
    
    //0x81: Stop movement
    void stop (FlexCAN can, uint32_t device){
        CAN_message_t msg;
        // Define the message
        msg.id = parsing::id_assignment(device);
        msg.len = 8; 
        msg.buf[0] = 0x81;
        for(int i =1; i<8; i++){
            msg.buf[i] = 0x00;
        }

        if (can.write(msg)) {
            Serial.println("Stop command");
        }
        else {
            Serial.println("Error sending stop message");
        }
    }
    
    //0xA2: Velocity control using RPM (round per minute)
    void vel (FlexCAN can, uint32_t device, int32_t rpm){
        
        // //1.Set throttle
        // static uint32_t lastMicros = 0;
        // uint32_t now = micros();  
        // if (now - lastMicros < POS_FREQ) {
        //     // too soon — just exit, no blocking, no CAN write
        //     return;
        // }
        // lastMicros = now;                // stamp the send-time


        CAN_message_t msg;
       
        // Define the message
        msg.id = parsing::id_assignment(device);
        msg.len = 8; // Data length code (8 bytes)
        msg.buf[0] = 0xA2;
        for(int i =1; i<4;i++){
            msg.buf[i] = 0x00;
        }
        int32_t dps = parsing::rpm_to_dps (rpm);
        std::array<uint8_t, 4> data = parsing::int_to_array(dps);

        for(int i =4; i<8;i++){
            msg.buf[i] = data[i-4]; //receive data;
        }
        if (can.write(msg)) {
            Serial.println("Velocity command");
        }
        else {
            Serial.println("Error sending velocity message");
        }
        

    }
    
    //0x76: system reset
    void system_reset(FlexCAN can, uint32_t device){
        CAN_message_t msg;
       
        // Define the message
        msg.id = parsing::id_assignment(device);
        msg.len = 8; // Data length code (8 bytes)

        msg.buf[0] = 0x76;
        for(int i =1; i<8;i++){
            msg.buf[i] = 0x00;

        }
        if (can.write(msg)) {
            Serial.println("System Resetting");
        }
        else {
            Serial.println("Error sending reset message");
        }
        delay(1000);//delay 1s
        Serial.println("Done System Reset");

    }

    //0x64: set encoder zero_offset at current posiiton + system reset for it to take effect
    //  Waits for reply
    void zero_encoder (FlexCAN can, uint32_t device){
        CAN_message_t msg;
        #ifdef DEBUG
            Serial.println("Debug controller.cpp");
        #endif 
       
        // Define the message
        msg.id = parsing::id_assignment(device);
        msg.len = 8; // Data length code (8 bytes)

        msg.buf[0] = 0x64;
        for(int i =1; i<8;i++){
            msg.buf[i] = 0x00;
        }
        if (can.write(msg)) {
            Serial.println("Encoder reset command");
        }
        else {
            Serial.println("Error sending encoder reset message");
        }

        //Wait for reply
        while (true){
            if (can.read(msg)){
                #ifdef DEBUG
                Serial.println("Received message");
                #endif
                if((msg.id ==0x240+device)&& msg.buf[0]==0x64){
                    Serial.println("ZEROED");

                    //read 4-8 bytes daug
                    std::array<uint8_t,4> data = {};
                    for(int i = 0; i<4;i++){
                        data[i]=msg.buf[i+4]; //plus 4 for where the data field starts
                    }
                    int32_t initial = parsing::array_to_int(data);
                    motor_control::system_reset(can, device);
                    Serial.print("The zeroed-offset is at raw pulse: ");
                    Serial.println(initial);
                    break;
                }
            }
            else{
                // Serial.println("not receiving message");

            }
        }
    }
    
    //0x92: read absolute position to zero_offset (angle in deg) 
    //  Waits for reply
    void get_pos_abs(FlexCAN can, uint32_t device){
        CAN_message_t msg;
       
        // Define the message
        msg.id = parsing::id_assignment(device);
        msg.len = 8; // Data length code (8 bytes)

        msg.buf[0] = 0x92;
        for(int i =1; i<8;i++){
            msg.buf[i] = 0x00;
        }
        if (can.write(msg)) {
            Serial.println("Read absolute position command");
        }
        else {
            Serial.println("Error sending encoder reset message");
        }

        //Wait for reply
        while (true){
            if (can.read(msg)){
                #ifdef DEBUG
                Serial.println("Received message");
                #endif
                if((msg.id ==0x240+device)&&msg.buf[0]==0x92){
                    Serial.println("GOT POS");

                    //read 4-8 bytes daug
                    std::array<uint8_t,4> data = {};
                    for(int i = 0; i<4;i++){
                        data[i]=msg.buf[i+4]; //plus 4 for where the data field starts
                    }
                    double angle = static_cast<double>(parsing::array_to_int(data)/100.0);
                    Serial.print("The motor is at ");
                    Serial.print(angle);
                    Serial.println(" degrees absolute");
                    break;
                }
            }
            else{
                //Serial.println("not receiving message");

            }
        }
    }
    
    //0xA8: Incremental position control  ('deg' unit is 0.01 degree)
    void pos_inc (FlexCAN can, uint32_t device, int32_t deg, int32_t rpm){
        assert(rpm<=MAX_SPEED&&rpm>=(-MAX_SPEED)&&rpm!=0);
        // //1.Set throttle
        // static uint32_t lastMicros = 0;
        // uint32_t now = micros();  
        // if (now - lastMicros < POS_FREQ) {
        // // too soon — just exit, no blocking, no CAN write
        // return;
        // }
        // lastMicros = now;                // stamp the send-time

        //2.Build msg
        CAN_message_t msg;
        msg.id = parsing::id_assignment(device);
        msg.len = 8; 
        int32_t dps = parsing::rpm_to_dps (rpm); //parses max moving rpm to hex msg fields
        std::array<uint8_t, 4> speed = parsing::int_to_array(dps);
        msg.buf[0] = 0xA8;
        msg.buf[1] = 0x00;

        for(int i =2; i<4;i++){
            msg.buf[i] = speed[i-2]; //receive data;
        }

        std::array<uint8_t, 4> data = parsing::int_to_array(deg);  //parses move deg to hex msg field
        for(int i =4; i<8;i++){   
            msg.buf[i] = data[i-4]; //receive data;
        }
        
        if (can.write(msg)) {
            Serial.println("Incremental position command");
        }
        else {
            Serial.println("Error sending postion message");
        }
    }

    //0xA4: Absolute position control ('deg' unit is 0.01 dps)
    void pos_abs (FlexCAN can, uint32_t device, int32_t deg, int32_t rpm){
         assert(rpm<=MAX_SPEED&&rpm>=(-MAX_SPEED)&&rpm!=0);

        //  //1.Set throttle
        // static uint32_t lastMicros = 0;
        // uint32_t now = micros();  
        // if (now - lastMicros < POS_FREQ) {
        // // too soon — just exit, no blocking, no CAN write
        //     return;
        // }
        // lastMicros = now;                // stamp the send-time

        CAN_message_t msg;
        msg.id = parsing::id_assignment(device);
        msg.len = 8; 
        int32_t dps = parsing::rpm_to_dps (rpm); //parses max moving rpm to hex msg fields
        std::array<uint8_t, 4> speed = parsing::int_to_array(dps);
        msg.buf[0] = 0xA4;
        msg.buf[1] = 0x00;

        for(int i =2; i<4;i++){
            msg.buf[i] = speed[i-2]; //receive data;
        }

        std::array<uint8_t, 4> data = parsing::int_to_array(deg);  //parses move deg to hex msg field
        for(int i =4; i<8;i++){   
            msg.buf[i] = data[i-4]; //receive data;
        }
        
        if (can.write(msg)) {
            // Serial.println("Absolute position command");
        }
        else {
            Serial.println("Error absolute postion message");
        }

    }

}

