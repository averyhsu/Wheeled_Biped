#include <Wire.h>

#define MPU_ADDR 0x68
#define PWR_MGMT_1 0x6B

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);  // Give device time to boot

  Serial.println("🧪 Attempting soft reset of MPU6050...");

  // Write 0x80 to PWR_MGMT_1 to trigger reset
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x80);  // Reset bit
  byte result = Wire.endTransmission();

  Serial.print("Soft reset result: ");
  Serial.println(result);  // 0 = success, 2 = NACK on address, etc.

  // Optional: tell user what it means
  switch (result) {
    case 0:
      Serial.println("✅ Reset command sent successfully.");
      break;
    case 1:
      Serial.println("❌ Error 1: Data too long to fit in transmit buffer.");
      break;
    case 2:
      Serial.println("❌ Error 2: Received NACK on transmit of address.");
      break;
    case 3:
      Serial.println("❌ Error 3: Received NACK on transmit of data.");
      break;
    case 4:
      Serial.println("❌ Error 4: Unknown error.");
      break;
    default:
      Serial.println("❌ Unknown result code.");
      break;
  }
}

void loop() {
  // Nothing needed
}

