#include <Ultrasonic.h>
#include <Servo.h>

Ultrasonic ultrasonic(3);
Servo servoV;
Servo servoH;
int scanH = 0;
int scanV = 50    ;
void setup()
{
  Serial.begin(9600);
  servoH.attach(5);
  servoV.attach(6);
}
void loop()
{
  if(scanV > 180) {
    return;
  }
  servoV.write(scanV);
  servoH.write(scanH);
  ultrasonic.MeasureInCentimeters();
  int range = ultrasonic.RangeInCentimeters;
  Serial.println(String(scanH)+","+String(scanV)+","+String(range));
  scanH = (scanH+1)%180;
  if(scanH == 0) {
    scanV = scanV+1;
  }
  delay(50);
}
