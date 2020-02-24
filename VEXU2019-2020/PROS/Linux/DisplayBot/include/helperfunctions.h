#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "main.h"

void setMotors(std::vector<pros::Motor> & motors, double speed);
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
bool pressButton(std::uint32_t  & debounceTime);

#endif
