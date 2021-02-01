#ifndef _FOUR_WHEEL_DRIVE
#define _FOUR_WHEEL_DRIVE

#include "api.h"
#include <vector>

enum DIRECTION {FORWARD, BACKWARD};

class FourWheelDrive
{
    std::vector<pros::Motor> *rightMotors;
    std::vector<pros::Motor> *leftMotors;

    //pros::ADIGyro gyro;

    const double ROTATION_MUL = 845;
    const int STOP_AMOUNT = 100;
    DIRECTION direction = FORWARD;
    int numMotors;

public:
    FourWheelDrive(std::vector<pros::Motor> &right, std::vector<pros::Motor> &left);
    ~FourWheelDrive();

    void setMotorsRelative(std::vector<pros::Motor> *motors, double distance, double speed);
    void setMotorsRelative(double distance, double speed);
    void setBrakes(std::vector<pros::Motor> *motors,  pros::motor_brake_mode_e_t brakeType);
    void setBrakes(pros::motor_brake_mode_e_t brakeType);

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

};
#endif
