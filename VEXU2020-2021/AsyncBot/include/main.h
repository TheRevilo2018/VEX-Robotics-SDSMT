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

// Data structure includes just in case
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

// Actual code includes
#include "constants.h"
#endif

//3 wire port defines
#define GYRO_PORT 'G'

//Motor port defines
#define RIGHT_WHEEL_FRONT_PORT 9
#define RIGHT_WHEEL_BACK_PORT 2
#define LEFT_WHEEL_FRONT_PORT 10
#define LEFT_WHEEL_BACK_PORT 1

#define LEFT_INTAKE 11
#define RIGHT_INTAKE 20
#define BOTTOM_ROLLER 19
#define INSERTER 18

#define INERTIAL_SENSOR_PORT 12

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

// Twin function declarations


//controller declarations
static pros::Controller alpha(pros::E_CONTROLLER_MASTER);
static pros::Controller beta(pros::E_CONTROLLER_PARTNER);

// Standard port declarations
//Left robot ports
static pros::Motor wheelFrontLeft(LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelBackLeft(LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelFrontRight(RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelBackRight(RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

static pros::Motor leftIntake(LEFT_INTAKE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor rightIntake(RIGHT_INTAKE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor bottomRoller(BOTTOM_ROLLER, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor inserter(INSERTER, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);


// 3 wire port declearations
static pros::Imu inertialSensor(INERTIAL_SENSOR_PORT);

// Motor grouping declarations
static std::vector<pros::Motor> wheelMotorVector =
    {wheelFrontLeft, wheelBackLeft, wheelFrontRight, wheelBackRight};
static std::vector<pros::Motor> leftWheelMotorVector = {wheelFrontLeft, wheelBackLeft};
static std::vector<pros::Motor> rightWheelMotorVector = {wheelFrontRight, wheelBackRight};
static std::vector<pros::Motor> intakeMotorVector = {leftIntake, rightIntake};

//drive base class

//position constants

//pros declarations
static std::uint32_t now = pros::millis();

//globals
static bool actuatorState = false;
//sanity correction

#endif  // _PROS_MAIN_H_
