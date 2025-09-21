#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu(0x68);

// --- DMP state ---
bool     dmpReady   = false;
uint8_t  devStatus  = 0;
uint16_t packetSize = 0;
uint16_t fifoCount  = 0;
uint8_t  fifoBuffer[64];

Quaternion   q;
VectorFloat  gravity;
float        ypr[3];   // library gives Yaw(Z), Pitch(Y), Roll(X)
float        rpy[3];   // we'll reorder to Roll, Pitch, Yaw

void setup() {
  Serial.begin(115200);
  Wire.begin();              // Teensy 4.1: SDA=18, SCL=19
  Wire.setClock(100000);     // keep conservative if wiring is long
  delay(200);

  mpu.initialize();
  devStatus = mpu.dmpInitialize();

  // (optional) quick offsets — tune later:
  // mpu.setXAccelOffset(...); mpu.setYAccelOffset(...); mpu.setZAccelOffset(...);
  // mpu.setXGyroOffset(...);  mpu.setYGyroOffset(...);  mpu.setZGyroOffset(...);

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    dmpReady   = true;
    packetSize = mpu.dmpGetFIFOPacketSize();

    // (optional) lower the DMP output rate to make polling easy (e.g., ~50 Hz)
    // mpu.setRate(19); // DMP base 200 Hz / (1 + Rate) -> 200/20 = 10 Hz (for some firmware)
    // Note: setRate semantics can vary by firmware blob; if unsure, leave default.

    Serial.println("DMP ready (polling FIFO, printing R,P,Y).");
  } else {
    Serial.print("DMP init failed, code = ");
    Serial.println(devStatus);
    while (1) {}
  }
}

void loop() {
  if (!dmpReady) return;

  fifoCount = mpu.getFIFOCount();
  if (fifoCount == 1024) {        // FIFO overflow
    mpu.resetFIFO();
    return;
  }
  if (fifoCount < packetSize) return;  // nothing new yet

  // read exactly one packet
  mpu.getFIFOBytes(fifoBuffer, packetSize);

  // quaternion -> gravity -> YPR (yaw, pitch, roll)
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

  // Reorder to RPY (roll, pitch, yaw), convert to degrees
  rpy[0] =  ypr[2] * 180.0f / M_PI;  // Roll  (X)
  rpy[1] =  ypr[1] * 180.0f / M_PI;  // Pitch (Y)
  rpy[2] =  ypr[0] * 180.0f / M_PI;  // Yaw   (Z)

  // Serial.print("RPY (deg): ");
  Serial.print(rpy[0]); Serial.print(", ");
  Serial.print(rpy[1]); Serial.print(", ");
  Serial.println(rpy[2]);
}
