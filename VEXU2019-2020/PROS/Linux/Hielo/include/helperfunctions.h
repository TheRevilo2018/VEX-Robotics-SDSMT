#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "main.h"

const double ROTATION_MUL = 845;
const int STOP_AMOUNT = 100;

void setMotors(std::vector<pros::Motor> & motors, double speed);
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
void driveDist(double target, DIRECTION direction, int numCubes, double maxSpeed = 100);
void cubeRun(double target, int numCubes);
void correctDist (std::vector<pros::Motor> leftMotors, std::vector<pros::Motor> rightMotors, double target, double speed, double gyroVal);
double distReq(double speed, int numCubes, DIRECTION direction);
void setDirection(DIRECTION direction);
//void autoDriveDistance(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double distance, double speed);
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector,
    std::vector<pros::Motor> & rightWheelMotorVector, double amount);
void drive(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, int distance);
bool pressButton(std::uint32_t  & debounceTime);
void cubeSet();
void depositStack();
void unFold();
void gyroHold(int time);

#endif
