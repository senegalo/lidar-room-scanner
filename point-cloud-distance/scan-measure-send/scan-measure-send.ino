#include <Ultrasonic.h>
#include <Servo.h>

Ultrasonic ultrasonic(3);
Servo servoV;
Servo servoH;
int scanH = 45;
int scanV = 105    ;
void setup()
{
  Serial.begin(9600);
  servoH.attach(5);
  servoV.attach(6);
  servoV.write(scanV);
  servoH.write(scanH);
}
void loop()
{
  if(scanV > 135) {
    return;
  }
  servoV.write(map(scanV, 0, 165, 0, 180));
  servoH.write(map(scanH, 0, 165, 0, 180));
  ultrasonic.MeasureInCentimeters();
  int range = ultrasonic.RangeInCentimeters;
  Serial.println(String(scanH)+","+String(scanV)+","+String(range));
  
  scanH = (scanH+1);
  if(scanH > 135) {
    scanH = 45;
  }
  if(scanH == 45) {
    scanV = scanV+1;
  }
  delay(50);
}
