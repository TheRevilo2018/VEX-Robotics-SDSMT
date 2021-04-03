#include "../include/twinRun.h"

namespace twin
{
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

    // Screen posting might break async, check it
    pros::lcd::set_text(5, "Calling op_control: " + std::to_string(pros::millis()));
    const int inserterConst = 110;
    const int inserterRestingConst = -40;
    const int intakeConst = 85;

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
    int loopDelay = 20;

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


        if(pressButton(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1), debounceButtonL1))
        {
          if(inserterPercent == inserterConst)
          {
            inserterPercent = inserterRestingConst;
          }
          else
          {
            inserterPercent = inserterConst;
          }
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
