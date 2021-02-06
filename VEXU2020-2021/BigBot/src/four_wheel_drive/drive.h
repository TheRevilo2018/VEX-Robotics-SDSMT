#ifndef _FOUR_WHEEL_DRIVE
#define _FOUR_WHEEL_DRIVE

#include "../../include/api.h"
#include "../logger/logger.h"
#include <vector>
#include <sstream>
#include "math.h"

enum DIRECTION {FORWARD, BACKWARD};

class FourWheelDrive
{
    std::vector<pros::Motor> *rightMotors;
    std::vector<pros::Motor> *leftMotors;
    pros::Imu *inertialSensor;
    pros::Controller *master;

    Logger logger;

    //pros::ADIGyro gyro;

    //calibration values
    std::stringstream fileStream;

    double maxActualSpeed;
    double maxInstructedSpeed;
    double minSpeed;
    double LRHandicap;
    double maxAccelerationForward;
    double maxAccelerationBackward;
    double distanceMultiplier;

    const double ROTATION_MUL = 845;
    const int STOP_AMOUNT = 100;
    const int LOOP_DELAY = 20;


    DIRECTION direction = FORWARD;
    int numMotors; //number of motors on ONE side

public:
    FourWheelDrive(std::vector<pros::Motor>&, std::vector<pros::Motor>&,
        pros::Imu & , pros::Controller & );

    void readCalibration();
    void writeCalibration();
    void calibrateAll(pros::Controller & master);
    void calibrateMinSpeed();
    void calibrateMaxSpeed();
    void calibrateMaxAcceleration(pros::Controller & master, double returnSpeed);
    void driveTillColide(double speed);

    void setMotorsRelative(std::vector<pros::Motor> *motors, double distance, double speed);
    void setMotorsRelative(double distance, double speed);
    void setBrakes(std::vector<pros::Motor> *motors,  pros::motor_brake_mode_e_t brakeType);
    void setBrakes(pros::motor_brake_mode_e_t brakeType);
    double getAllSpeed();
    double getAllPosition();

    void driveDist(double target, DIRECTION direction, double maxSpeed = 100);
    double distReq(double speed, DIRECTION direction);
    void setDirection(DIRECTION direction);
    void autoTurnRelative(std::vector<pros::Motor> *leftWheelMotorVector,
        std::vector<pros::Motor> *rightWheelMotorVector, double amount);
    void drive(std::vector<pros::Motor> *leftWheelMotorVector,
        std::vector<pros::Motor> *rightWheelMotorVector, int distance);

private:
    void setMotors(std::vector<pros::Motor> *motors, double speed);
    void setMotors(double speed);
    void setZeroPosition(std::vector<pros::Motor> * motors);
    void setZeroPosition();

    void correctDist (std::vector<pros::Motor> *leftMotors, std::vector<pros::Motor> *rightMotors,
        double target, double speed, DIRECTION direction);
        bool panic(pros::Controller & master);



    void checkGyro();
    void correctGyroCalibration(float accel);

};
#endif
