#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"
#include "TFMiniPlus.h"
#include "Wire.h"

TFMiniPlus mini;

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();
int servoHigh = 434;
int servoLow = 70;

uint8_t scanH;
uint8_t scanV;
uint8_t minScanV;
uint8_t maxScanV;
uint8_t minScanH;
uint8_t maxScanH;
uint8_t scanDelay;
uint16_t range;
uint16_t strength;
uint8_t inc = 1;
bool start = false;

// stepper
bool direction = true;
uint8_t stepper_clock = 3;
uint8_t stepper_dir = 2;

void setup() {
  // serial config
  Serial.begin(115200);
  Serial3.begin(115200);

  // PWM generator for the servos
  Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();
  driver.begin();
  driver.setPWMFreq(50);
  Wire.setClock(400000);

  mini.begin(&Serial3);
  if (mini.setFrameRate(0) && mini.setMeasurementTo(TFMINI_MEASUREMENT_MM)) {
    Serial.println("System Ready");
  }

  pinMode(stepper_clock, OUTPUT);
  pinMode(stepper_dir, OUTPUT);
  digitalWrite(stepper_dir, HIGH);
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

  driver.setPWM(0, 0, map(scanV, 0, 180, servoLow, servoHigh));
  digitalWrite(stepper_clock, HIGH);
  delayMicroseconds(100);
  digitalWrite(stepper_clock, LOW);

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
    scanH += inc;

    if (scanH >= maxScanH || scanH <= minScanH) {
      inc *= -1;
      digitalWrite(stepper_dir, !digitalRead(stepper_dir));
      scanV = scanV + 1;
    }
  }
  delay(scanDelay);
}