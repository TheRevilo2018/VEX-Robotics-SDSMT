#include "../include/helperfunctions.h"

//take in a vecor of motors, and set their speed to a value
void setMotors(std::vector<pros::Motor> & motors, double speed)
{
  for(auto motor : motors)
  {
    motor = speed;
  }
}

//take in a vector of motors, and set their brake type to a given type
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType)
{
  for(auto motor: motors)
  {
    motor.set_brake_mode(brakeType);
  }
}

//tqke in a vector of motors, and call the move relative function for all of them with a given distance and speed
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed)
{
  for(auto motor : motors)
  {
    motor.move_relative(distance, speed);
  }
}

bool pressButton(std::uint32_t  & debounceTime)
{
	std::uint32_t pressTime = pros::millis();
	if(pressTime - debounceTime >= DEBOUNCE_DELAY)
	{
		debounceTime = pressTime;
		return true;
	}
	return false;
}


// Prevents inifinite rotation and bounding into 360 degrees
float degreeBoundingHelper(float inDegrees)
{
  float inRadians = degreesToRadians(inDegrees);
  return radiansToDegrees(atan2(sin( inRadians), cos(inRadians)));
}

float degreesToRadians(float radians)
{
  return radians * M_PI / 180.0;
}

float radiansToDegrees(float degrees)
{
  return degrees * 180.0 / M_PI;
}

float bindToMagnitude(float value, float MAX_MAGNITUDE)
{
  if(value > MAX_MAGNITUDE)
  {
    value = MAX_MAGNITUDE;
  }
  else if(value < -MAX_MAGNITUDE)
  {
    value = -MAX_MAGNITUDE;
  }
  return value;
}