#include <Wire.h>    // Wire library สำหรับ I2C
#include <TFLI2C.h>      // TF Luna I2C library 

TFLI2C tflI2C;   //โมเดลที่ใช้สื่อสารกับSensor
int16_t tfDist;   // ระยะทาง (cm)
int16_t tfAddr = TFL_DEF_ADR;   // ที่อยู่ I2C ของเซนเซอร์

const int buzzerPin = 8;
const int minDist = 50;     // ใกล้ที่สุดที่สนใจ (cm)
const int maxDist = 500;    // ไกลที่สุดที่สนใจ (cm)
const int minFreq = 50;    // ความถี่ต่ำสุด (Hz)
const int maxFreq = 2000;   // ความถี่สูงสุด (Hz)

void setup() {
  Serial.begin(115200);
  Wire.begin();  //เริ่มI2C
  pinMode(buzzerPin, OUTPUT);   // ตั้งขา buzzer เป็น OUTPUT
}

void loop() {
  if (tflI2C.getData(tfDist, tfAddr)) {
    Serial.print("Distance: ");  
    Serial.print(tfDist);   //ระยะทาง
    Serial.println(" cm");

    if (tfDist > 0 && tfDist < maxDist) {
      // Mapping ระยะเป็นความถี่: ยิ่งใกล้ ยิ่งเสียงสูง
      int freq = map(tfDist, maxDist, minDist, minFreq, maxFreq);
      freq = constrain(freq, minFreq, maxFreq);  // ป้องกันความถี่เกินขอบเขต

      tone(buzzerPin, freq);
    } else {
      noTone(buzzerPin);
    }

  } else {
    Serial.println("Failed to read from LiDAR");
    noTone(buzzerPin);
  }

  delay(50);
}
