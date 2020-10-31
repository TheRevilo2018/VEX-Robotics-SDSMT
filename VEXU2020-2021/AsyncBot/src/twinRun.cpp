#include "../include/twinRun.h"

namespace twin
{
  void opcontrolTask(void* param)
  {
    int pairIndex = (int)param;
    // Screen posting might break async, check it
    pros::lcd::set_text(5, "Calling op_control: " + std::to_string(pros::millis()));
    int turnThreshold = 10;
    int driveThreshold = 10;
    int leftMotorPercent = 0;
    int rightMotorPercent = 0;
    std::uint32_t debounceButtonA = 0;
    std::uint32_t debounceButtonB = 0;
    std::uint32_t debounceButtonX = 0;
    std::uint32_t debounceButtonY = 0;
    std::uint32_t debounceButtonDOWN = 0;
    std::uint32_t debounceButtonUP = 0;
    std::uint32_t debounceButtonLEFT = 0;
    std::uint32_t debounceButtonRIGHT = 0;
    std::uint32_t debounceButtonR1 = 0;
    int loopDelay = 20;
    bool trayLock = false;
    int liftIndex = 0;
    bool trayHitting = false;

    while (true)
    {
      if(abs(alpha.get_analog(ANALOG_LEFT_Y)) > driveThreshold || abs(alpha.get_analog(ANALOG_RIGHT_X)) > turnThreshold)
          {
            leftMotorPercent = alpha.get_analog(ANALOG_LEFT_Y);
            rightMotorPercent = alpha.get_analog(ANALOG_LEFT_Y);

            if(alpha.get_analog(ANALOG_RIGHT_X) > turnThreshold)
            {
              leftMotorPercent += abs(alpha.get_analog(ANALOG_RIGHT_X));
              rightMotorPercent -= abs(alpha.get_analog(ANALOG_RIGHT_X));
            }
            else
            {
              leftMotorPercent -= abs(alpha.get_analog(ANALOG_RIGHT_X));
              rightMotorPercent += abs(alpha.get_analog(ANALOG_RIGHT_X));
            }
          }
          else
          {
            leftMotorPercent = 0;
            rightMotorPercent = 0;
          }

          setMotors(leftWheelMotorVector, leftMotorPercent);
          setMotors(rightWheelMotorVector, rightMotorPercent);
          pros::delay(loopDelay);
    }
  }
}
