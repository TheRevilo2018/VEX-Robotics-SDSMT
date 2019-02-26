#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include "main.h"


void setMotors(std::vector<pros::Motor> & motors, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
void doubleLaunch(pros::Motor & launchMotorLeft, pros::Motor & launchMotorRight, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors);

#endif
