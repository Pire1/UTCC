#include <Wire.h>        // Wire library สำหรับ I2C
#include <TFLI2C.h>      // TF Luna I2C library 

TFLI2C tflI2C;       //โมเดลที่ใช้สื่อสารกับSensor

int16_t tfDist;                    // ระยะทาง (cm)
int16_t tfAddr = TFL_DEF_ADR;      // ที่อยู่ I2C ของเซนเซอร์

const int buzzerPin = 8;           // ขา buzzer (เช่น D8)
const int threshold = 500;          // ระยะที่ต้องการให้ buzzer ทำงาน (cm)

void setup() {
  Serial.begin(115200);     // เปิด Serial Monitor
  Wire.begin();             // เริ่มต้น I2C
  pinMode(buzzerPin, OUTPUT); // ตั้งขา buzzer เป็น OUTPUT
}

void loop() {
  if (tflI2C.getData(tfDist, tfAddr)) {
    Serial.println(String(tfDist) + " cm / " + String(tfDist / 2.54) + " inches");

    if (tfDist < threshold) {
      digitalWrite(buzzerPin, HIGH);  // เปิดเสียงถ้าใกล้เกินไป
    } else {
      digitalWrite(buzzerPin, LOW);   // ปิดเสียงถ้าไกลพอ
    }
  } else {
    Serial.println("Failed to read from LiDAR");
    digitalWrite(buzzerPin, LOW); // ความปลอดภัย: ปิด buzzer ถ้าอ่านไม่ได้
  }

  delay(50); // รอ 50 ms
}

