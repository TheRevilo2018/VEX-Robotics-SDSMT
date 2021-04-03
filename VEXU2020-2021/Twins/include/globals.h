#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "../src/four_wheel_Drive/drive.h"


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
extern pros::Controller controllerAlpha;
extern pros::Controller controllerBeta;
extern std::vector<pros::Controller> controllerPair;

// Standard port declarations
//Left robot ports
extern pros::Motor wheelFrontLeftAlpha;
extern pros::Motor wheelBackLeftAlpha;
extern pros::Motor wheelFrontRightAlpha;
extern pros::Motor wheelBackRightAlpha;

extern pros::Motor leftIntakeAlpha;
extern pros::Motor rightIntakeAlpha;
extern pros::Motor bottomRollerAlpha;
extern pros::Motor inserterAlpha;


extern pros::Motor wheelFrontLeftBeta;
extern pros::Motor wheelBackLeftBeta;
extern pros::Motor wheelFrontRightBeta;
extern pros::Motor wheelBackRightBeta;

extern pros::Motor leftIntakeBeta;
extern pros::Motor rightIntakeBeta;
extern pros::Motor bottomRollerBeta;
extern pros::Motor inserterBeta;


// 3 wire port declearations
extern pros::Imu inertialSensorAlpha;;
extern pros::Imu inertialSensorBeta;

extern std::vector<pros::Imu> inertialSensorPair;

// Motor grouping declarations
extern std::vector<pros::Motor> wheelMotorVectorAlpha;
extern std::vector<pros::Motor> leftWheelMotorVectorAlpha;
extern std::vector<pros::Motor> rightWheelMotorVectorAlpha;
extern std::vector<pros::Motor> intakeMotorVectorAlpha;

extern std::vector<pros::Motor> wheelMotorVectorBeta;
extern std::vector<pros::Motor> leftWheelMotorVectorBeta;
extern std::vector<pros::Motor> rightWheelMotorVectorBeta;
extern std::vector<pros::Motor> intakeMotorVectorBeta;


extern std::vector<std::vector<pros::Motor>> wheelVectorPair;
extern std::vector<std::vector<pros::Motor>> leftWheelVectorPair;
extern std::vector<std::vector<pros::Motor>> rightWheelVectorPair;
extern std::vector<std::vector<pros::Motor>> intakeMotorVectorPair;

extern std::vector<pros::Motor> bottomRollerPair;
extern std::vector<pros::Motor> inserterRollerPair;


//drive base class
extern FourWheelDrive* driveBaseAlpha;
extern FourWheelDrive* driveBaseBeta;

extern std::vector<FourWheelDrive*> driveBasePair;

//Constants
extern const int inserterConst;
extern const int inserterRestingConst;
extern const int intakeConst;
extern const int loopDelay;

//pros declarations
extern std::uint32_t now;

//globals

//sanity correction

#endif
