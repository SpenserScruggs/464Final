#include <inverseKinematics.h>
#include <Servo.h>

int Min = 700;
int Max = 2600;
int open = 90;
int close = 20;
Servo servo1, servo2, servo3, servo4;
float servoData[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
float angles[4] = {0, 0, 0, close}; 
float home[3] = { 50, 100, 127.5 }; // home position
float startPos[3] = { 50, 100, 127.5 };

void sort(String input){
  float xblue = (input.substring(0, 3)).toInt() * 1.0;
  float yblue = 100 - (input.substring(3, 6)).toInt() * 1.0;
  float xred = (input.substring(6, 9)).toInt() * 1.0;
  float yred = 100 - (input.substring(9, 12)).toInt() * 1.0;

  //blue
  float step1[3] = {xblue, yblue, 127.5};
  transform(2000, startPos, step1, servo1, servo2, servo3, servoData);
  claw(open, servo4, angles, servoData);

  float step2[3] = {xblue, yblue, 30};
  transform(2000, startPos, step2, servo1, servo2, servo3, servoData);
  claw(close, servo4, angles, servoData);

  transform(2000, startPos, step1, servo1, servo2, servo3, servoData);

  float step3[3] = {100, 110, 127.5};
  transform(2000, startPos, step3, servo1, servo2, servo3, servoData);
  claw(open, servo4, angles, servoData);

  //red

  float step4[3] = {xred, yred, 127.5};
  transform(2000, startPos, step4, servo1, servo2, servo3, servoData);
  claw(open, servo4, angles, servoData);

  float step5[3] = {xred, yred, 30};
  transform(2000, startPos, step5, servo1, servo2, servo3, servoData);
  claw(close, servo4, angles, servoData);

  transform(2000, startPos, step4, servo1, servo2, servo3, servoData);

  float step6[3] = {100, -110, 127.5};
  transform(2000, startPos, step6, servo1, servo2, servo3, servoData);
  claw(open, servo4, angles, servoData);

  transform(2000, startPos, home, servo1, servo2, servo3, servoData);
  claw(close, servo4, angles, servoData);

  Serial.flush();
}

void setup() {
  // put your setup code here, to run once:
  Serial.flush();
  Serial.begin(9600);
  Serial.setTimeout(5);
  servo1.attach(5, Min, Max);
  servo2.attach(6, Min, Max);
  servo3.attach(9, Min, Max);
  servo4.attach(10, Min, Max);

  assignServoData(1, servoData, 11.2472, 1478.7398, 700, 2600);
  assignServoData(2, servoData, 11.2826, 1745.8116, 700, 2600);
  assignServoData(3, servoData, 11.2121, 1610.8116, 700, 2600);
  assignServoData(4, servoData, 11.2472, 1668.7398, 700, 2600);

  thCalc(startPos, angles);
  move(angles, servo1, servo2, servo3, servo4, servoData);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() == 0){
  }
  sort(Serial.readString());
}
