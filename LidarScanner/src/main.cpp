#include <Arduino.h>
#include "Servo.h"
#include "TFMiniPlus.h"

TFMiniPlus mini;
Servo servoV;
Servo servoH;
int scanH = 45;
int scanV = 105;
int range;
int strength;

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
  if (scanV > 120) {
    return;
  }
  servoV.write(map(scanV, 0, 165, 0, 180));
  servoH.write(map(scanH, 0, 165, 0, 180));

  mini.triggerDetection();

  if (mini.readData()) {
    range = mini.getDistance();
    strength = mini.getSignalStrength();
    Serial.println(String(scanH) + "," + String(scanV) + "," + String(range) +
                   "," + String(strength));

    scanH = (scanH + 1);
    if (scanH > 135) {
      scanH = 45;
    }
    if (scanH == 45) {
      scanV = scanV + 1;
    }
  }
  delay(50);
}