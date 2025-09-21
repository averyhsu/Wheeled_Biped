#include "Wire.h"
#include "imu_class.hpp"
IMU imu;

void setup() {
  Serial.begin(115200);
  Wire.begin();              // Teensy 4.1: SDA=18, SCL=19
  Wire.setClock(100000);     // keep conservative if wiring is long
  imu.initialize();
}

void loop() {
  if (float* rpy = imu.poll()) {
    Serial.print(rpy[0]); Serial.print(", ");
    Serial.print(rpy[1]); Serial.print(", ");
    Serial.println(rpy[2]);
  }
}
