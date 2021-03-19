#include "globals.h"

//controller declarations
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//motor declarations
pros::Motor wheelLeft1(LEFT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelLeft2(LEFT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelLeft3(LEFT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelRight1(RIGHT_WHEEL_FRONT_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelRight2(RIGHT_WHEEL_MIDDLE_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor wheelRight3(RIGHT_WHEEL_BACK_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor rightArm(RIGHT_ARM_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftArm(LEFT_ARM_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor bottomDrum(LOWER_DRUM_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor topDrum(UPPER_DRUM_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor pooper(POOPER_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);


//sensor declearations
pros::Imu inertialSensor(INERTIAL_SENSOR_PORT);
pros::ADIAnalogIn lightSensor(LIGHT_SENSOR_PORT);
pros::ADIDigitalIn trayBumperLeft(LEFT_TRAY_BUMPER_PORT);
pros::ADIDigitalIn trayBumperRight(RIGHT_TRAY_BUMPER_PORT);
pros::ADIDigitalOut actuator(ACTUATOR_PORT);
pros::Vision visionSensor (VISION_SENSOR_PORT);

// Vision Sensor Signatures
pros::vision_signature_s_t RED_BALL_SIG = pros::Vision::signature_from_utility(RED_BALL_SIG_INDEX, 7607, 9741, 8674, -1573, -153, -863, 0.900, 0);
pros::vision_signature_s_t BLUE_BALL_SIG = pros::Vision::signature_from_utility(BLUE_BALL_SIG_INDEX, -3099, -1713, -2406, 7985, 11737, 9861, 1.600, 0);
pros::vision_signature_s_t BACKPLATE_SIG = pros::Vision::signature_from_utility(BACKPLATE_SIG_INDEX, -1237, 1, -618, 179, 2291, 1234, 1.100, 0);


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
const int inserterRestingConst = -40;
const int intakeConst = 85;
const int pooperConst = 85;
const int loopDelay = 20;
Color colorToPoop = red;
