#include <ServoCalibration.h>
#include <Arduino.h>

int servoParameters(float th, float slope, float bias, int max, int min)
{
	return constrain((int)(slope * th + bias), min, max);
}