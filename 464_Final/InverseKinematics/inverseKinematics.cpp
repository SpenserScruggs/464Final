#include "inverseKinematics.h"
#include "Arduino.h"
#include "Servo.h"

float pi = 3.141593;

// dimensions in mm
int l1 = 65;
int l2 = 80;
int l3 = 80;

int dr = 60;
int dz = 17.5;

void assignServoData(int servoNumber, float servoData[4][4], float slope, float bias, float min, float max)
{
	servoData[servoNumber -1][0] = slope;
	servoData[servoNumber -1][1] = bias;
	servoData[servoNumber -1][2] = min;
	servoData[servoNumber -1][3] = max;
}

int servoParameters(float th, int servoNumber, float servoData[][4])
{
	return constrain((int)(servoData[servoNumber - 1][0] * th + servoData[servoNumber - 1][1]), (int)servoData[servoNumber - 1][2], (int)servoData[servoNumber - 1][3]);
}

void thCalc(float xyzPos[], float thetas[])
{
	if (sqrt(xyzPos[0] * xyzPos[0] + xyzPos[1] * xyzPos[1] + (xyzPos[2]-l1) * (xyzPos[2]-l1)) < l2+l3+dr && sqrt(xyzPos[0] * xyzPos[0] + xyzPos[1] * xyzPos[1] + (xyzPos[2]-l1) * (xyzPos[2]-l1)) > 80 && xyzPos[0] > 0 && xyzPos[2] >= -dz)	{
		thetas[0] = atan2(xyzPos[1], xyzPos[0]);

		float x = xyzPos[0] - dr * cos(thetas[0]);
		float y = xyzPos[1] - dr * sin(thetas[0]);
		float z = xyzPos[2] + dz;
  
		float r = sqrt(x * x + y * y);
		float rp = sqrt(x * x + y * y + (z - l1) * (z - l1));

		thetas[2] = pi - acos((rp * rp - l3 * l3 - l2 * l2) / (-2 * l3 * l2));

		thetas[1] = atan2((l3 * sin(thetas[2])), (l2 + l3 * cos(thetas[2]))) + asin((z - l1) / (rp));

		thetas[0] = thetas[0] * 180 / pi;
		thetas[1] = 90 - thetas[1] * 180 / pi;
		thetas[2] = 90 - thetas[2] * 180 / pi - thetas[1];
	}
}

void move(float angles[], Servo servo1, Servo servo2, Servo servo3, Servo servo4, float servoData[4][4])
{
	servo1.writeMicroseconds(servoParameters(angles[0], 1, servoData));
	servo2.writeMicroseconds(servoParameters(angles[1], 2, servoData));
	servo3.writeMicroseconds(servoParameters(angles[2], 3, servoData));
	servo4.writeMicroseconds(servoParameters(angles[3], 4, servoData));	
}

void transform(int duration_in_milliseconds, float current_pos[], float new_pos[], Servo servo1, Servo servo2, Servo servo3, float servoData[4][4])
{
	float steps = 100;
	
	float stepping[3] = {current_pos[0], current_pos[1], current_pos[2]};

	float time_delay = (float)duration_in_milliseconds / steps;
	
	float d1 = (new_pos[0] - current_pos[0]) / steps;
	float d2 = (new_pos[1] - current_pos[1]) / steps;
	float d3 = (new_pos[2] - current_pos[2]) / steps;

	float angles[3] = { 0, 0, 0 };

	for (int i = 0; i < steps; i++){
		stepping[0] += d1;
		stepping[1] += d2;
		stepping[2] += d3;
		
		thCalc(stepping, angles);

		servo1.writeMicroseconds(servoParameters(angles[0], 1, servoData));
		servo2.writeMicroseconds(servoParameters(angles[1], 2, servoData));
		servo3.writeMicroseconds(servoParameters(angles[2], 3, servoData));

  		Serial.print(angles[0]); Serial.print("\t");
  		Serial.print(angles[1]); Serial.print("\t");
  		Serial.print(angles[2]); Serial.println("\t");

		delay((int)time_delay);
	}

	current_pos[0] = new_pos[0];
	current_pos[1] = new_pos[1];
	current_pos[2] = new_pos[2];
}

void claw(float open_or_closed, Servo servo4, float angles[], float servoData[4][4])
{
	angles[3] = open_or_closed;	
	servo4.writeMicroseconds(servoParameters(angles[3], 4, servoData));
}

