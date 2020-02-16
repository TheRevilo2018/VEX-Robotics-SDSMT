#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "main.h"

void setMotors(std::vector<pros::Motor> & motors, double speed);
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
void doubleLaunch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors, std::vector<int> & anglerPos);
void launch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, int height, bool fast);
void highScore(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector,  std::vector<pros::Motor> & liftMotors, bool & actuatorState);
void autoDriveDistance(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double distance, double speed);
void customMoveAbsolute(pros::Motor motor, double value);
void customMoveAbsolute(std::vector<pros::Motor> motors, double value);
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount, double speed);
void longDoubleLaunch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors);
void drive(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, int distance);
void autoTurnLeft(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount);
void autoTurnRight(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount);
bool pressButton(std::uint32_t  & debounceTime);

#endif
