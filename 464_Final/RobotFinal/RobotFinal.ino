#include <inverseKinematics.h>
#include <Servo.h>

int Min = 700;
int Max = 2600;
int open = 90;
int close = 20;
Servo servo1, servo2, servo3, servo4;
float servoData[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
float angles[4] = {0, 0, 0, close}; 
float xyzPos[3] = {140, 0, 127.5}; // home position

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo1.attach(5, Min, Max);
  servo2.attach(6, Min, Max);
  servo3.attach(9, Min, Max);
  servo4.attach(10, Min, Max);

  assignServoData(1, servoData, 11.2472, 1478.7398, 700, 2600);
  assignServoData(2, servoData, 11.2826, 1745.8116, 700, 2600);
  assignServoData(3, servoData, 11.2121, 1610.8116, 700, 2600);
  assignServoData(4, servoData, 11.2472, 1668.7398, 700, 2600);

  thCalc(xyzPos, angles);
  move(angles, servo1, servo2, servo3, servo4, servoData);
  delay(1000);

  float newxyz1[3] = {100, 0, 100};
  transform(2000, xyzPos, newxyz1, servo1, servo2, servo3, servoData);
  claw(open, servo4, angles, servoData);

  float newxyz2[3] = {150, 0, 0};
  transform(2000, xyzPos, newxyz2, servo1, servo2, servo3, servoData);
  claw(close, servo4, angles, servoData);

  float newxyz3[3] = {140, 0, 127.5};
  transform(2000, xyzPos, newxyz3, servo1, servo2, servo3, servoData);

  float newxyz4[3] = {100, 100, 127.5};
  transform(2000, xyzPos, newxyz4, servo1, servo2, servo3, servoData);

  float newxyz5[3] = {100, 100, 0};
  transform(2000, xyzPos, newxyz5, servo1, servo2, servo3, servoData);
  claw(open, servo4, angles, servoData);

  transform(2000, xyzPos, newxyz4, servo1, servo2, servo3, servoData);
  claw(close, servo4, angles, servoData);
  transform(2000, xyzPos, newxyz3, servo1, servo2, servo3, servoData);
}

void loop() {
  // put your main code here, to run repeatedly:

}
