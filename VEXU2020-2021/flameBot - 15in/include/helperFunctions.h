#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "globals.h"

const double ROTATION_MUL = 845;
const int STOP_AMOUNT = 100;

void setMotors(std::vector<pros::Motor> & motors, double speed);
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
bool pressButton(bool press, bool &debounce);
void unfold();
void autoCycle(int time = 3000);
Color getBallColor();
bool isHoldingBall();
void setOuttakeInsert();
void setOuttakePoop();
void setOuttakeContain();
void setIntakeRun();
void setIntakeStop();
void setIntakeHold();
void setOuttakeTwo();
void setOuttakeOne();
void goalApproch(FourWheelDrive*  driveBase, float numTiles, float speed);

#endif
