#include <Arduino.h>
#include "Servo.h"

Servo servoV;
Servo servoH;
int scanH = 45;
int scanV = 105;
long measurement = 0;
int del = 500;

void setup() {
  Serial.begin(115200);

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
  Serial.println(String(scanH) + "," + String(scanV) + "," + String(del));
  delay(del);
}