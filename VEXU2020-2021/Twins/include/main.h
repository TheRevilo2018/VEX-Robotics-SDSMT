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

//Motor port defines
// Alpha
#define A_RIGHT_WHEEL_BACK_PORT 1
#define A_LEFT_WHEEL_FRONT_PORT 2
#define A_RIGHT_WHEEL_FRONT_PORT 9
#define A_LEFT_WHEEL_BACK_PORT 10

#define A_RIGHT_INTAKE 4
#define A_BOTTOM_ROLLER 5
#define A_INSERTER_PORT 7
#define A_LEFT_INTAKE 8

#define A_INERTIAL_SENSOR_PORT 21

// Beta
#define B_RIGHT_WHEEL_BACK_PORT 18
#define B_LEFT_WHEEL_FRONT_PORT 14
#define B_RIGHT_WHEEL_FRONT_PORT 13
#define B_LEFT_WHEEL_BACK_PORT 19

#define B_RIGHT_INTAKE 11
#define B_BOTTOM_ROLLER 17
#define B_INSERTER_PORT 15
#define B_LEFT_INTAKE 16

#define B_INERTIAL_SENSOR_PORT 12

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

// Twin function declarations


//controller declarations
static pros::Controller alpha(pros::E_CONTROLLER_MASTER);
static pros::Controller beta(pros::E_CONTROLLER_PARTNER);
static std::vector<pros::Controller> controllerPair{alpha, beta};

// Standard port declarations
//Left robot ports
static pros::Motor wheelFrontLeftAlpha(A_LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelBackLeftAlpha(A_LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelFrontRightAlpha(A_RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelBackRightAlpha(A_RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

static pros::Motor leftIntakeAlpha(A_LEFT_INTAKE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor rightIntakeAlpha(A_RIGHT_INTAKE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor bottomRollerAlpha(A_BOTTOM_ROLLER, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor inserterAlpha(A_INSERTER_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);


static pros::Motor wheelFrontLeftBeta(B_LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelBackLeftBeta(B_LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelFrontRightBeta(B_RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor wheelBackRightBeta(B_RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

static pros::Motor leftIntakeBeta(B_LEFT_INTAKE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor rightIntakeBeta(B_RIGHT_INTAKE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor bottomRollerBeta(B_BOTTOM_ROLLER, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
static pros::Motor inserterBeta(B_INSERTER_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);


// 3 wire port declearations
static pros::Imu inertialSensorAlpha(A_INERTIAL_SENSOR_PORT);

static pros::Imu inertialSensorBeta(B_INERTIAL_SENSOR_PORT);

static std::vector<pros::Imu> inertialSensorPair = {inertialSensorAlpha, inertialSensorBeta};

// Motor grouping declarations
static std::vector<pros::Motor> wheelMotorVectorAlpha =
    {wheelFrontLeftAlpha, wheelBackLeftAlpha, wheelFrontRightAlpha, wheelBackRightAlpha};
static std::vector<pros::Motor> leftWheelMotorVectorAlpha = {wheelFrontLeftAlpha, wheelBackLeftAlpha};
static std::vector<pros::Motor> rightWheelMotorVectorAlpha = {wheelFrontRightAlpha, wheelBackRightAlpha};
static std::vector<pros::Motor> intakeMotorVectorAlpha = {leftIntakeAlpha, rightIntakeAlpha};


static std::vector<pros::Motor> wheelMotorVectorBeta =
    {wheelFrontLeftBeta, wheelBackLeftBeta, wheelFrontRightBeta, wheelBackRightBeta};
static std::vector<pros::Motor> leftWheelMotorVectorBeta = {wheelFrontLeftBeta, wheelBackLeftBeta};
static std::vector<pros::Motor> rightWheelMotorVectorBeta = {wheelFrontRightBeta, wheelBackRightBeta};
static std::vector<pros::Motor> intakeMotorVectorBeta = {leftIntakeBeta, rightIntakeBeta};


static std::vector<std::vector<pros::Motor>> wheelVectorPair = {wheelMotorVectorAlpha, wheelMotorVectorBeta};
static std::vector<std::vector<pros::Motor>> leftWheelVectorPair = {leftWheelMotorVectorAlpha, leftWheelMotorVectorBeta};
static std::vector<std::vector<pros::Motor>> rightWheelVectorPair = {rightWheelMotorVectorAlpha, rightWheelMotorVectorBeta};
static std::vector<std::vector<pros::Motor>> intakeMotorVectorPair = {intakeMotorVectorAlpha, intakeMotorVectorBeta};

static std::vector<pros::Motor> bottomRollerPair = {bottomRollerAlpha, bottomRollerBeta};
static std::vector<pros::Motor> inserterRollerPair = {inserterAlpha, inserterBeta};
//drive base class

//position constants

//pros declarations
static std::uint32_t now = pros::millis();

//globals

//sanity correction

#endif  // _PROS_MAIN_H_
