#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "../src/four_wheel_Drive/drive.h"


//sensor port defines
#define LEFT_TRAY_BUMPER_PORT 'A'
#define RIGHT_TRAY_BUMPER_PORT 'B'
#define LIGHT_SENSOR_PORT 'C'
#define ACTUATOR_PORT 'H'
#define INERTIAL_SENSOR_PORT 21
#define VISION_SENSOR_PORT 14
//Motor port defines
//drive
#define RIGHT_WHEEL_FRONT_PORT 5
#define RIGHT_WHEEL_MIDDLE_PORT 15
#define RIGHT_WHEEL_BACK_PORT 18
#define LEFT_WHEEL_FRONT_PORT 19
#define LEFT_WHEEL_MIDDLE_PORT 8
#define LEFT_WHEEL_BACK_PORT 10
//non-drive
#define POOPER_PORT 13
#define UPPER_DRUM_PORT 1
#define LOWER_DRUM_PORT 3
#define LEFT_ARM_PORT 20
#define RIGHT_ARM_PORT 16

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

//controller declarations
extern pros::Controller master;
extern pros::Controller partner;

//motor declarations
extern pros::Motor wheelLeft1;
extern pros::Motor wheelLeft2;
extern pros::Motor wheelLeft3;
extern pros::Motor wheelRight;
extern pros::Motor wheelRight;
extern pros::Motor wheelRight;

extern pros::Motor rightArm;
extern pros::Motor leftArm;
extern pros::Motor bottomDrum;
extern pros::Motor topDrum;
extern pros::Motor pooper;


//sensor declearations
extern pros::Imu inertialSensor;
extern pros::ADIAnalogIn lightSensor;
extern pros::ADIDigitalIn trayBumperLeft;
extern pros::ADIDigitalIn trayBumperRight;
extern pros::ADIDigitalOut actuator;
extern pros::Vision visionSensor;

// Vision Sensor Signatures
#define RED_BALL_SIG_INDEX 1
#define BLUE_BALL_SIG_INDEX 2
#define BACKPLATE_SIG_INDEX 3
extern pros::vision_signature_s_t RED_BALL_SIG;
extern pros::vision_signature_s_t BLUE_BALL_SIG;
extern pros::vision_signature_s_t BACKPLATE_SIG;


//motor grouping declarations
extern std::vector<pros::Motor> wheelMotorVector;
extern std::vector<pros::Motor> leftWheelMotorVector;
extern std::vector<pros::Motor> rightWheelMotorVector;
extern std::vector<pros::Motor> intakeMotorVector;


//drive base class
extern FourWheelDrive* driveBase;

//pros declarations
extern  std::uint32_t now;

// Enums
enum Color { red='R', blue='B', NA='N'};

//globals
extern bool actuatorState;
extern const int inserterConst;
extern const int inserterRestingConst;
extern const int intakeConst;
extern const int pooperConst;
extern const int loopDelay;
extern Color colorToPoop;


#endif
