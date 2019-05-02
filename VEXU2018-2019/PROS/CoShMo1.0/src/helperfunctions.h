#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

#include "main.h"

void setMotors(std::vector<pros::Motor> & motors, double speed);
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed);
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType);
void doubleLaunch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors);
void launch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, int height);
void highScore(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, pros::Motor & liftMotor);
void autoDriveDistance(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double distance, double speed);
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount, double speed);
void longDoubleLaunch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors);
void flipCrown(pros::Motor & liftMotor);
void drive(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, int distance);
void turnRight(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount);
void turnLeft(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount);


#endif
