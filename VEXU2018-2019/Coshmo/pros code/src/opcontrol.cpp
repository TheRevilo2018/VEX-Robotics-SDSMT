#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <ctype.h>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>
#include "helperFunctions.h"
#include "main.h"

#define LEFT_WHEEL1_PORT 1
#define LEFT_WHEEL2_PORT 2
#define LEFT_WHEEL3_PORT 3
#define RIGHT_WHEEL1_PORT 11
#define RIGHT_WHEEL2_PORT 12
#define RIGHT_WHEEL3_PORT 13

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Controller partner(pros::E_CONTROLLER_PARTNER);
	pros::Motor leftWheel1(1, true);
	pros::Motor leftWheel2(2, false);
	pros::Motor leftWheel3(3, true);
	pros::Motor rightWheel1(11, false);
	pros::Motor rightWheel2(12, true);
	pros::Motor rightWheel3(13, false);
	std::vector<pros::Motor> wheelMotorVector = {leftWheel1, leftWheel2, leftWheel3, rightWheel1, rightWheel2, rightWheel3 };
	std::vector<pros::Motor> leftWheelMotorVector = {leftWheel1, leftWheel2, leftWheel3 };
	std::vector<pros::Motor> rightWheelMotorVector = {rightWheel1, rightWheel2, rightWheel3 };
	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	bool holdMode = false;


	while (true)
	{

		if(abs(master.get_analog(ANALOG_LEFT_Y)) > driveThreshold || abs(master.get_analog(ANALOG_RIGHT_X)) > turnThreshold)
		{
			leftMotorPercent = master.get_analog(ANALOG_LEFT_Y);
			rightMotorPercent = master.get_analog(ANALOG_LEFT_Y);

			if(master.get_analog(ANALOG_RIGHT_X) > turnThreshold)
      {
             leftMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
             rightMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
      }
      else
      {
          leftMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
          rightMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
      }
		}
		else
		{
			leftMotorPercent = 0;
			rightMotorPercent = 0;
		}


		setMotors(leftWheelMotorVector, leftMotorPercent);
		setMotors(rightWheelMotorVector, rightMotorPercent);
		pros::delay(20);
	}
}
