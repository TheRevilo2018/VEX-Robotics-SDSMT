#include "helperfunctions.h"


void setMotors(std::vector<pros::Motor> & motors, double speed)
{
  for(auto motor : motors)
  {
    motor = speed;
  }
}
