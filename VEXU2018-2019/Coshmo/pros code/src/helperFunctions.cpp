#include "helperFunctions.h"


void setMotors(std::vector<pros::Motor> & motors, double speed)
{
  for(auto motor : motors)
  {
    motor = speed;
  }
}

void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType)
{
  for(auto motor: motors)
  {
    motor.set_brake_mode(brakeType);
  }
}

void doubleLaunch(pros::Motor & launchMotorLeft, pros::Motor & launchMotorRight, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors)
{
  anglerMotor.move_absolute(30, 50);
  pros::delay(200);
  launchMotorLeft.move_relative(720, 127);
  launchMotorRight.move_relative(720, 127);
  pros::delay(1000);
  setMotors(intakeMotors, 127);
  anglerMotor.move_absolute(60, 50);
  pros::delay(200);
  launchMotorLeft.move_relative(720, 127);
  launchMotorRight.move_relative(720, 127);
  pros::delay(1000);
  return;
}
