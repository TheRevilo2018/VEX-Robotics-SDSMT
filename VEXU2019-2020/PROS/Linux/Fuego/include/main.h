/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
//#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */

//data structure includes just in case
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
#include <fstream>
#endif

//3 wire port defines
#define LEFT_TRAY_BUMPER_PORT 'A'
#define RIGHT_TRAY_BUMPER_PORT 'B'
#define LIGHT_SENSOR_PORT 'C'
#define ACTUATOR_PORT 'H'
#define GYRO_PORT 'G'

//Motor port defines
//1
//2
#define LEFT_LIFT_PORT 3
#define LEFT_WHEEL_BOTTOM_PORT 4
#define LEFT_WHEEL_MIDDLE_PORT 5

#define LEFT_INTAKE_PORT 6
//7
#define LEFT_TRAY_PORT 8
//9
#define LEFT_WHEEL_TOP_PORT 10

#define RIGHT_LIFT_PORT 12
#define RIGHT_INTAKE_PORT 13
#define RIGHT_WHEEL_MIDDLE_PORT 14
#define RIGHT_WHEEL_BOTTOM_PORT 15

#define RIGHT_TRAY_PORT 16
//17
#define RIGHT_INTAKE_2_PORT 18
#define LEFT_INTAKE_1_PORT 19
#define RIGHT_WHEEL_TOP_PORT 20

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON pros::E_CONTROLLER_DIGITAL_UP
#define TRAY_MAX_HEIGHT 567
#define TRAY_MIDDLE_HEIGHT 260

//controller declarations
static pros::Controller master(pros::E_CONTROLLER_MASTER);
static pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//standard port declarations
static pros::Motor wheelLeft1(LEFT_WHEEL_TOP_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelLeft2(LEFT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelLeft3(LEFT_WHEEL_BOTTOM_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelRight1(RIGHT_WHEEL_TOP_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelRight2(RIGHT_WHEEL_BOTTOM_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelRight3(RIGHT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor intakeLeft(LEFT_INTAKE_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor intakeRight(RIGHT_INTAKE_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor trayLeft(LEFT_TRAY_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor trayRight(RIGHT_TRAY_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor liftLeft(LEFT_LIFT_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor liftRight(RIGHT_LIFT_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

//3 wire port declearations
static pros::ADIAnalogIn lightSensor(LIGHT_SENSOR_PORT);
static pros::ADIDigitalIn trayBumperLeft(LEFT_TRAY_BUMPER_PORT);
static pros::ADIDigitalIn trayBumperRight(RIGHT_TRAY_BUMPER_PORT);
static pros::ADIDigitalOut actuator(ACTUATOR_PORT);
static pros::ADIGyro gyro (GYRO_PORT);

//motor grouping declarations
static std::vector<pros::Motor> wheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3, wheelRight1, wheelRight2, wheelRight3};
static std::vector<pros::Motor> leftWheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3 };
static std::vector<pros::Motor> rightWheelMotorVector = {wheelRight1, wheelRight2, wheelRight3};
static std::vector<pros::Motor> intakeMotors = {intakeLeft, intakeRight};
static std::vector<pros::Motor> trayMotors = {trayLeft, trayRight};
static std::vector<pros::Motor> liftMotors = {liftLeft, liftRight};

//position constants
static std::vector<int> liftPositions = {480, 620};
static std::vector<int> trayPositions = {220, 230};


//pros declarations
static std::uint32_t now = pros::millis();

//globals
static bool actuatorState = false;
//sanity correction

#endif  // _PROS_MAIN_H_
