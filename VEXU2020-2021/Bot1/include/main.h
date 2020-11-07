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

//sensor port defines
#define LEFT_TRAY_BUMPER_PORT 'A'
#define RIGHT_TRAY_BUMPER_PORT 'B'
#define LIGHT_SENSOR_PORT 'C'
#define ACTUATOR_PORT 'H'
#define INERTIAL_SENSOR_PORT 3

//Motor port defines
#define RIGHT_WHEEL_FRONT_PORT 1
#define INERTIAL_SENSOR_PORT 3
#define RIGHT_WHEEL_MIDDLE_PORT 6
#define RIGHT_WHEEL_BACK_PORT 10
#define LEFT_WHEEL_FRONT_PORT 12
#define LEFT_WHEEL_MIDDLE_PORT 16
#define LEFT_WHEEL_BACK_PORT 20

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

//controller declarations
static pros::Controller master(pros::E_CONTROLLER_MASTER);
static pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//motor declarations
static pros::Motor wheelLeft1(LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelLeft2(LEFT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelLeft3(LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelRight1(RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelRight2(RIGHT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelRight3(RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//sensor declearations
static pros::Imu inertialSensor(INERTIAL_SENSOR_PORT);
static pros::ADIAnalogIn lightSensor(LIGHT_SENSOR_PORT);
static pros::ADIDigitalIn trayBumperLeft(LEFT_TRAY_BUMPER_PORT);
static pros::ADIDigitalIn trayBumperRight(RIGHT_TRAY_BUMPER_PORT);
static pros::ADIDigitalOut actuator(ACTUATOR_PORT);

//motor grouping declarations
static std::vector<pros::Motor> wheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3, wheelRight1, wheelRight2, wheelRight3};
static std::vector<pros::Motor> leftWheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3 };
static std::vector<pros::Motor> rightWheelMotorVector = {wheelRight1, wheelRight2, wheelRight3};

//drive base class

//position constants
static std::vector<int> liftPositions = {1440, 1860};
static std::vector<int> trayPositions = {220, 230};


//pros declarations
static std::uint32_t now = pros::millis();

//globals
static bool actuatorState = false;
//sanity correction

#endif  // _PROS_MAIN_H_
