#include "../include/helperFunctions.h"

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

void setOuttakeContain(pros::Motor inserterRoller)
{
  // Set everything to an intaking but not inserting speeds
  inserterRoller = inserterRestingConst;
}


void setOuttakeInsert(pros::Motor inserterRoller)
{
  // Set everything to an intaking but not inserting speeds
  inserterRoller = inserterConst;
}

void setIntakeIn(std::vector<pros::Motor> intakeMotorVector, pros::Motor bottomRoller)
{
  setMotors(intakeMotorVector, intakeConst);
  bottomRoller = intakeConst;
}

void setIntakeOut(std::vector<pros::Motor> intakeMotorVector, pros::Motor bottomRoller)
{
  setMotors(intakeMotorVector, -intakeConst);
  bottomRoller = -intakeConst;
}

void setIntakeContain(std::vector<pros::Motor> intakeMotorVector, pros::Motor bottomRoller)
{
  setMotors(intakeMotorVector, 0);
  bottomRoller = 0;
}
