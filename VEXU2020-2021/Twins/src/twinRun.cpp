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
    std::uint32_t debounceButtonA = 0;
    std::uint32_t debounceButtonB = 0;
    std::uint32_t debounceButtonX = 0;
    std::uint32_t debounceButtonY = 0;
    std::uint32_t debounceButtonDOWN = 0;
    std::uint32_t debounceButtonUP = 0;
    std::uint32_t debounceButtonLEFT = 0;
    std::uint32_t debounceButtonRIGHT = 0;
    std::uint32_t debounceButtonR1 = 0;
    std::uint32_t debounceButtonR2 = 0;
    std::uint32_t debounceButtonL1 = 0;
    int loopDelay = 20;

    while (true)
    {
        //ball controls
        // Outakes for bottom
        
  		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
  		{
  			if(pressButton(debounceButtonR1))
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
  		}
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
        {
            if(pressButton(debounceButtonR2))
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
        }
		
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        {
            inserterPercent = inserterConst;
        }
        else
        {
            inserterPercent = inserterRestingConst;
        }

        /*if(alpha.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        {
            if(pressButton(debounceButtonL1))
            {
                if (inserterPercent <= 0)
                {
                    inserterPercent = inserterConst;
                }
                else
                {
                    inserterPercent = inserterRestingConst;
                }
            }
        }*/

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
          bottomRoller = intakeConst;
          inserterRoller = inserterPercent;
          pros::delay(loopDelay);
    }
  }
}
