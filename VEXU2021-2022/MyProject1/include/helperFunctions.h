#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "globals.h"

const double ROTATION_MUL = 845;
const int STOP_AMOUNT = 100;

void setMotors(std::vector<motor> & motors, double speed);
void setMotorsRelative(std::vector<motor> & motors, double distance, double speed);
void setBrakes(std::vector<motor> & motors, brakeType mode);
bool pressButton(bool press, bool &debounce);

#endif
