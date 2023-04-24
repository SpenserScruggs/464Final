#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

#include <Arduino.h>
#include <Servo.h>

void assignServoData(int servoNumber, float servoData[4][4], float slope, float bias, float min, float max); 

int servoParameters(float th, int servoNumber, float servoData[][4]);

void thCalc(float xyzPos[], float thetas[]);

void move(float angles[], Servo servo1, Servo servo2, Servo servo3, Servo servo4, float servoData[4][4]);

void transform(int duration_in_milliseconds, float current_pos[], float new_pos[], Servo servo1, Servo servo2, Servo servo3, float servoData[4][4]);

void claw(float open_or_closed, Servo servo4, float angles[], float servoData[4][4]);

#endif