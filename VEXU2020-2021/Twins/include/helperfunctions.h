#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "main.h"

const double ROTATION_MUL = 845;
const int STOP_AMOUNT = 100;

void setMotors(std::vector<pros::Motor> & motors, double speed);
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
bool pressButton(bool press, bool &debounce);

#endif
