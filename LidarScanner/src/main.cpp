#include <Arduino.h>
#include "Servo.h"
#include "TFMiniPlus.h"

TFMiniPlus mini;
Servo servoV;
Servo servoH;
uint8_t scanH;
uint8_t scanV;
uint8_t minScanV;
uint8_t maxScanV;
uint8_t minScanH;
uint8_t maxScanH;
uint8_t scanDelay;
uint16_t range;
uint16_t strength;
bool start = false;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);

  servoH.attach(5);
  servoV.attach(6);
  servoV.write(scanV);
  servoH.write(scanH);

  mini.begin(&Serial3);
  if (mini.setFrameRate(0) && mini.setMeasurementTo(TFMINI_MEASUREMENT_MM)) {
    Serial.println("System Ready");
  }
}
void loop() {
  if (Serial.available()) {
    uint8_t buffer[6];
    Serial.readBytes(&buffer[0], 6);
    if (buffer[0] == 0xFF) {
      minScanH = buffer[1];
      maxScanH = buffer[2];
      minScanV = buffer[3];
      maxScanV = buffer[4];
      scanDelay = buffer[5];

      scanH = minScanH;
      scanV = minScanV;
      start = true;
    }
  }

  if (!start) {
    return;
  }

  if (scanV > maxScanV) {
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
    start = false;
    return;
  }

  servoV.write(map(scanV, 0, 165, 0, 180));
  servoH.write(map(scanH, 0, 165, 0, 180));

  mini.triggerDetection();

  if (mini.readData()) {
    range = mini.getDistance();
    strength = mini.getSignalStrength();

    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(scanH);
    Serial.write(scanV);
    Serial.write(uint8_t(range >> 8));
    Serial.write(uint8_t(range));
    Serial.write(uint8_t(strength >> 8));
    Serial.write(uint8_t(strength));
    scanH = (scanH + 1);
    if (scanH > maxScanH) {
      scanH = minScanH;
    }
    if (scanH == minScanH) {
      scanV = scanV + 1;
    }
  }
  delay(scanDelay);
}