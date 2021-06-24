#include "../include/twinRun.h"

namespace twin
{
void autonomousTaskAlpha(void * param)
{
    int count = 0;
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

    // Insert into center red goal

    driveBase->swingDrivePID(-1.7, 0);
    pros::delay(500);
    //release cord
    pros::delay(8000);
    driveBase->turnDegreesAbsolutePID(-48);
    driveBase->driveTilesPID(1.7);
    setOuttakeUnlock(inserterRoller);
    setIntakeHold(intakeMotorVector);
    /*
    driveBase->turnDegreesAbsolutePID(0);
    driveBase->swingDrivePID(0.7, 0);
    driveBase->turnDegreesAbsolutePID(-55);
    driveBase->swingDrivePID(1.5, 0);
    */
    pros::delay(500);
    driveBase->swingDrivePID(0.5, 0); //was 0.5
    setOuttakeInsertAll(inserterRoller, bottomRoller);


    while(true)
    {
        pros::lcd::set_text(7, "Alpha" + std::to_string(count));
        count++;
        pros::delay(loopDelay);
    }


}
void autonomousTaskBeta(void * param)
{
    int count = 0;
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

    driveBase->swingDrivePID(-1.7, 0);
    pros::delay(500);
    setOuttakeUnlock(inserterRoller);
    setOuttakeContain(inserterRoller);
    pros::delay(1500);
    driveBase->turnDegreesAbsolutePID(0);
    driveBase->swingDrivePID(0.9, 0);
    driveBase->turnDegreesAbsolutePID(59);
    setIntakeIn(intakeMotorVector, bottomRoller);
    driveBase->swingDrivePID(0.9, 0);
    setIntakeHold(intakeMotorVector);
    driveBase->swingDrivePID(0.3, 0);
    setOuttakeInsertAll(inserterRoller, bottomRoller);

    while(true)
    {
        pros::lcd::set_text(8, "Beta" + std::to_string(count));
        count++;
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

    auto driveBase = driveBasePair[pairIndex];

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
                intakePercent = intakeHold;
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
                intakePercent = intakeHold;
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

        if (pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A), debounceButtonA))
        {
            setOuttakeContain(inserterRoller);
            setIntakeContain(intakeMotorVector, bottomRoller);
        }
        if (pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B), debounceButtonB))
        {
            driveBase->driveTilesPID(3);
        }
        if (pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X), debounceButtonX))
        {
            driveBase->swingDrivePID(3, 0);
        }
        if (pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y), debounceButtonY))
        {
            setOuttakeInsertAll(inserterRoller, bottomRoller);
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
        bottomRoller = 60;
        inserterRoller = inserterPercent;
        pros::delay(loopDelay);
    }
}
}
