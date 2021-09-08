#include "../include/helperFunctions.h"

//take in a vecor of motors, and set their speed to a value
void setMotors(std::vector<motor> & motors, double speed)
{
  for(auto motor : motors)
  {
    motor = speed;
  }
}

//take in a vector of motors, and set their brake type to a given type
void setBrakes(std::vector<motor> & motors, brakeType mode)
{
  for(int i = 0; i < motors.size(); i++)
  {
    motors[i].setBrake(mode);
  }
}

//take in a vector of motors, and call the move relative function for all of them with a given distance and speed
void setMotorsRelative(std::vector<motor> & motors, double distance, double speed)
{
  for(auto motor : motors)
  {
    motor.spinTo(distance, rotationUnits::deg, speed);
  }
}

bool pressButton(bool press, bool &debounce)
{
	if(press)
    {
        if(!debounce)
        {
            debounce = true;
            return true;
        }
    }
    else
    {
        debounce = false;
    }

    return false;
}


