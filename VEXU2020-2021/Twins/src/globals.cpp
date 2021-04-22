#include "globals.h"

// Twin function declarations


//controller declarations
pros::Controller controllerAlpha(pros::E_CONTROLLER_MASTER);
pros::Controller controllerBeta(pros::E_CONTROLLER_PARTNER);
std::vector<pros::Controller> controllerPair{controllerAlpha, controllerBeta};

// Standard port declarations
//Left robot ports
pros::Motor wheelFrontLeftAlpha(A_LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelBackLeftAlpha(A_LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelFrontRightAlpha(A_RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelBackRightAlpha(A_RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor leftIntakeAlpha(A_LEFT_INTAKE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightIntakeAlpha(A_RIGHT_INTAKE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor bottomRollerAlpha(A_BOTTOM_ROLLER, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor inserterAlpha(A_INSERTER_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);


pros::Motor wheelFrontLeftBeta(B_LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelBackLeftBeta(B_LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelFrontRightBeta(B_RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelBackRightBeta(B_RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor leftIntakeBeta(B_LEFT_INTAKE, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightIntakeBeta(B_RIGHT_INTAKE, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor bottomRollerBeta(B_BOTTOM_ROLLER, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor inserterBeta(B_INSERTER_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);


// 3 wire port declearations
pros::Imu inertialSensorAlpha(A_INERTIAL_SENSOR_PORT);

pros::Imu inertialSensorBeta(B_INERTIAL_SENSOR_PORT);

std::vector<pros::Imu> inertialSensorPair = {inertialSensorAlpha, inertialSensorBeta};

// Motor grouping declarations
std::vector<pros::Motor> wheelMotorVectorAlpha =
{wheelFrontLeftAlpha, wheelBackLeftAlpha, wheelFrontRightAlpha, wheelBackRightAlpha};
std::vector<pros::Motor> leftWheelMotorVectorAlpha = {wheelFrontLeftAlpha, wheelBackLeftAlpha};
std::vector<pros::Motor> rightWheelMotorVectorAlpha = {wheelFrontRightAlpha, wheelBackRightAlpha};
std::vector<pros::Motor> intakeMotorVectorAlpha = {leftIntakeAlpha, rightIntakeAlpha};


std::vector<pros::Motor> wheelMotorVectorBeta =
{wheelFrontLeftBeta, wheelBackLeftBeta, wheelFrontRightBeta, wheelBackRightBeta};
std::vector<pros::Motor> leftWheelMotorVectorBeta = {wheelFrontLeftBeta, wheelBackLeftBeta};
std::vector<pros::Motor> rightWheelMotorVectorBeta = {wheelFrontRightBeta, wheelBackRightBeta};
std::vector<pros::Motor> intakeMotorVectorBeta = {leftIntakeBeta, rightIntakeBeta};


std::vector<std::vector<pros::Motor>> wheelVectorPair = {wheelMotorVectorAlpha, wheelMotorVectorBeta};
std::vector<std::vector<pros::Motor>> leftWheelVectorPair = {leftWheelMotorVectorAlpha, leftWheelMotorVectorBeta};
std::vector<std::vector<pros::Motor>> rightWheelVectorPair = {rightWheelMotorVectorAlpha, rightWheelMotorVectorBeta};
std::vector<std::vector<pros::Motor>> intakeMotorVectorPair = {intakeMotorVectorAlpha, intakeMotorVectorBeta};

std::vector<pros::Motor> bottomRollerPair = {bottomRollerAlpha, bottomRollerBeta};
std::vector<pros::Motor> inserterRollerPair = {inserterAlpha, inserterBeta};
//drive base class

FourWheelDrive* driveBaseAlpha;
FourWheelDrive* driveBaseBeta;

// Needs to be set in initialize
std::vector<FourWheelDrive*> driveBasePair = {driveBaseAlpha, driveBaseBeta};

//Constants
const int inserterConst = 110;
const int inserterRestingConst = -40;
const int intakeConst = 85;
const int loopDelay = 20;

//pros declarations
std::uint32_t now = pros::millis();

//globals

//sanity correction
