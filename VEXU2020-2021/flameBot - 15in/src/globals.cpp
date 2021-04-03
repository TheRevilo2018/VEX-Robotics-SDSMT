#include "globals.h"

//controller declarations
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//motor declarations
pros::Motor wheelLeft1(LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelLeft2(LEFT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelLeft3(LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelRight1(RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelRight2(RIGHT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelRight3(RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor rightArm(RIGHT_ARM_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftArm(LEFT_ARM_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor bottomDrum(LOWER_DRUM_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor topDrum(UPPER_DRUM_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor pooper(POOPER_PORT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);


//sensor declearations
pros::Imu inertialSensor(INERTIAL_SENSOR_PORT);
pros::ADIAnalogIn lightSensor(LIGHT_SENSOR_PORT);
pros::ADIDigitalIn trayBumperLeft(LEFT_TRAY_BUMPER_PORT);
pros::ADIDigitalIn trayBumperRight(RIGHT_TRAY_BUMPER_PORT);
pros::ADIDigitalOut actuator(ACTUATOR_PORT);
pros::Optical opticalSensor (OPTICAL_SENSOR_PORT);

//motor grouping declarations
std::vector<pros::Motor> wheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3, wheelRight1, wheelRight2, wheelRight3};
std::vector<pros::Motor> leftWheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3 };
std::vector<pros::Motor> rightWheelMotorVector = {wheelRight1, wheelRight2, wheelRight3};
std::vector<pros::Motor> intakeMotorVector = {rightArm, leftArm};


//drive base class
FourWheelDrive* driveBase;

//pros declarations
std::uint32_t now = pros::millis();

//globals
bool actuatorState = false;
const int inserterConst = 110;
const int bottomDrumConst = 80;
const int inserterRestingConst = -60;
const int intakeConst = 100;
const int pooperConst = 100;
const int loopDelay = 20;
Color colorToPoop = blue;
const int seenBufferSize = 4;
std::vector<Color> seenBuffer(seenBufferSize, NA);
