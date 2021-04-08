#include "../include/twinRun.h"

namespace twin
{
void autonomousTaskAlpha(void * param)
{
    // Resolve the motors we'll be using locally
    int pairIndex = (int)param;
    auto controller = controllerPair[pairIndex];
    auto wheelMotorVector = wheelVectorPair[pairIndex];
    auto leftWheelMotorVector = leftWheelVectorPair[pairIndex];
    auto rightWheelMotorVector = rightWheelVectorPair[pairIndex];
    auto intakeMotorVector = intakeMotorVectorPair[pairIndex];

    auto Imu = inertialSensorPair[pairIndex];

    auto bottomRoller = bottomRollerPair[pairIndex];
    auto inserterRoller = inserterRollerPair[pairIndex];

    auto driveBase = driveBasePair[pairIndex];

    setIntakeIn(intakeMotorVector, bottomRoller);
    driveBase->driveTilesPID(0.75);
    pros::delay(100);
    driveBase->turnDegreesAbsolutePID(-90);
    pros::delay(100);
    driveBase->driveTilesPID(3.0);
    pros::delay(100);
    driveBase->turnDegreesAbsolutePID(-90 - 45);
    pros::delay(100);
    driveBase->driveTilesPID(0.75);
    setOuttakeInsert(inserterRoller);
    pros::delay(300);


    int temp = 0;
    while(true)
    {
        pros::lcd::set_text(5, "Alpha" + std::to_string(temp));
        temp++;
        pros::delay(loopDelay);
    }


}
void autonomousTaskBeta(void * param)
{
    // Resolve the motors we'll be using locally
    int pairIndex = (int)param;
    auto controller = controllerPair[pairIndex];
    auto wheelMotorVector = wheelVectorPair[pairIndex];
    auto leftWheelMotorVector = leftWheelVectorPair[pairIndex];
    auto rightWheelMotorVector = rightWheelVectorPair[pairIndex];
    auto intakeMotorVector = intakeMotorVectorPair[pairIndex];

    auto Imu = inertialSensorPair[pairIndex];

    auto bottomRoller = bottomRollerPair[pairIndex];
    auto inserterRoller = inserterRollerPair[pairIndex];

    auto driveBase = driveBasePair[pairIndex];

    setIntakeIn(intakeMotorVector, bottomRoller);
    driveBase->driveTilesPID(2.0);
    pros::delay(100);
    driveBase->turnDegreesAbsolutePID(90 + 25);
    pros::delay(100);
    driveBase->driveTilesPID(0.5);
    pros::delay(100);
    setOuttakeInsert(inserterRoller);
    pros::delay(300);

    int temp = 0;
    while(true)
    {
        pros::lcd::set_text(7, "Beta" + std::to_string(temp));
        temp++;
        pros::delay(loopDelay);
    }


}
void opcontrolTask(void* param)
{
    // Resolve the motors we'll be using locally
    int pairIndex = (int)param;
    auto controller = controllerPair[pairIndex];
    auto wheelMotorVector = wheelVectorPair[pairIndex];
    auto leftWheelMotorVector = leftWheelVectorPair[pairIndex];
    auto rightWheelMotorVector = rightWheelVectorPair[pairIndex];
    auto intakeMotorVector = intakeMotorVectorPair[pairIndex];

    auto Imu = inertialSensorPair[pairIndex];

    auto bottomRoller = bottomRollerPair[pairIndex];
    auto inserterRoller = inserterRollerPair[pairIndex];

    int turnThreshold = 10;
    int driveThreshold = 10;
    int leftMotorPercent = 0;
    int rightMotorPercent = 0;
    int intakePercent = 0;
    int inserterPercent = inserterRestingConst;
    bool debounceButtonA = false;
    bool debounceButtonB = false;
    bool debounceButtonX = false;
    bool debounceButtonY = false;
    bool debounceButtonDOWN = false;
    bool debounceButtonUP = false;
    bool debounceButtonLEFT = false;
    bool debounceButtonRIGHT = false;
    bool debounceButtonR1 = false;
    bool debounceButtonR2 = false;
    bool debounceButtonL1 = false;

    while (true)
    {
        //ball controls
        // Outakes for bottom

        if(pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1), debounceButtonR1))
        {
            if (intakePercent <= 0)
            {
                intakePercent = intakeConst;
            }
            else
            {
                intakePercent = 0;
            }
        }
        else if (pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2), debounceButtonR2))
        {
            if ( intakePercent >= 0)
            {
                intakePercent = -intakeConst;
            }
            else
            {
                intakePercent = 0;
            }
        }


        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        {
          inserterPercent = inserterConst;
        }
        else
        {
          inserterPercent = inserterRestingConst;
        }

        //drive controls
        if(abs(controller.get_analog(ANALOG_LEFT_Y)) > driveThreshold || abs(controller.get_analog(ANALOG_RIGHT_X)) > turnThreshold)
        {
            leftMotorPercent = controller.get_analog(ANALOG_LEFT_Y);
            rightMotorPercent = controller.get_analog(ANALOG_LEFT_Y);

            if(controller.get_analog(ANALOG_RIGHT_X) > turnThreshold)
            {
                leftMotorPercent += abs(controller.get_analog(ANALOG_RIGHT_X));
                rightMotorPercent -= abs(controller.get_analog(ANALOG_RIGHT_X));
            }
            else
            {
                leftMotorPercent -= abs(controller.get_analog(ANALOG_RIGHT_X));
                rightMotorPercent += abs(controller.get_analog(ANALOG_RIGHT_X));
            }
        }
        else
        {
            leftMotorPercent = 0;
            rightMotorPercent = 0;
        }

        setMotors(leftWheelMotorVector, leftMotorPercent);
        setMotors(rightWheelMotorVector, rightMotorPercent);
        setMotors(intakeMotorVector, intakePercent);
        bottomRoller = intakePercent;
        inserterRoller = inserterPercent;
        pros::delay(loopDelay);
    }
}
}
