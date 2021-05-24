#include "drive.h"


// Prevents inifinite rotation and bounding into 360 degrees
float FourWheelDrive::degreeBoundingHelper(float inDegrees)
{
  float inRadians = degreesToRadians(inDegrees);
  return radiansToDegrees(atan2(sin( inRadians), cos(inRadians)));
}

float FourWheelDrive::degreesToRadians(float radians)
{
  return radians * M_PI / 180.0;
}

float FourWheelDrive::radiansToDegrees(float degrees)
{
  return degrees * 180.0 / M_PI;
}

float FourWheelDrive::bindToMagnitude(float value, float MAX_MAGNITUDE)
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

void FourWheelDrive::setAllBrakeMode(std::vector<pros::Motor> *motors, pros::motor_brake_mode_e_t mode)
{
    int size = (int)motors->size();

    for( int i = 0; i < size; i++)
    {
        motors->at(i).set_brake_mode(mode);
    }
}

void FourWheelDrive::setAllBrakeMode(pros::motor_brake_mode_e_t mode)
{
    setAllBrakeMode(rightMotors, mode);
    setAllBrakeMode(leftMotors, mode);
}
