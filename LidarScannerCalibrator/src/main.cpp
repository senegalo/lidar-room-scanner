#include <Arduino.h>
#include "Servo.h"
#include "TFMiniPlus.h"

TFMiniPlus mini;
Servo servoV;
Servo servoH;
int scanH = 45;
int scanV = 105;
long measurement = 0;
int del = 500;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);

  mini.begin(&Serial3);
  if (mini.setFrameRate(0) && mini.setMeasurementTo(TFMINI_MEASUREMENT_MM)) {
    Serial.println("System Ready");
  }

  servoH.attach(5);
  servoV.attach(6);
  servoV.write(scanV);
  servoH.write(scanH);
}
void loop() {
  if (Serial.available()) {
    // HHHVVVDDD
    measurement = Serial.parseInt();
    scanH = measurement / 1000000;
    scanV = (measurement - scanH * 1000000) / 1000;
    del = measurement - scanV * 1000 - scanH * 1000000;
    servoV.write(map(scanV, 0, 165, 0, 180));
    servoH.write(map(scanH, 0, 165, 0, 180));
  }
  mini.triggerDetection();
  if (mini.readData()) {
    Serial.print(String(scanH) + "," + String(scanV) + "," + String(del));
    Serial.print(",");
    Serial.print(mini.getDistance());
    Serial.print(",");
    Serial.println(mini.getSignalStrength());
  }
  delay(del);
}