
#include "helperFunctions.h"
#include "main.h"

#define LEFT_WHEEL1_PORT 1
#define LEFT_WHEEL2_PORT 2
#define LEFT_WHEEL3_PORT 3
#define RIGHT_WHEEL1_PORT 11
#define RIGHT_WHEEL2_PORT 12
#define RIGHT_WHEEL3_PORT 13
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Controller partner(pros::E_CONTROLLER_PARTNER);
	pros::Motor leftWheel1(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor leftWheel2(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor leftWheel3(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rightWheel1(11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rightWheel2(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rightWheel3(13, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor launchMotorLeft(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor launchMotorRight(20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

	std::vector<pros::Motor> wheelMotorVector = {leftWheel1, leftWheel2, leftWheel3, rightWheel1, rightWheel2, rightWheel3 };
	std::vector<pros::Motor> leftWheelMotorVector = {leftWheel1, leftWheel2, leftWheel3 };
	std::vector<pros::Motor> rightWheelMotorVector = {rightWheel1, rightWheel2, rightWheel3 };
	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int debounceButtonY = 0;
	int debounceButtonR1 = 0;
	int loopDelay = 20;
	bool holdMode = false;


	while (true)
	{
		if(debounceButtonY > 0)
		{
			debounceButtonY -= loopDelay;
		}
		if(debounceButtonR1 > 0)
		{
			debounceButtonR1 -= loopDelay;
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        if(debounceButtonY <= 0)
        {    //call hold mode
            holdMode = !holdMode;
            debounceButtonY = 200;
        }
    }
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			launchMotorLeft = 100;
			launchMotorRight = 100;
		}
		else
		{
			launchMotorLeft = 0;
			launchMotorRight = 0;
		}
		if(!holdMode)
    {
        setBrakes(wheelMotorVector, pros::E_MOTOR_BRAKE_COAST );
    }
    else
    {
    	setBrakes(wheelMotorVector, pros::E_MOTOR_BRAKE_HOLD );
    }

		if(abs(master.get_analog(ANALOG_LEFT_Y)) > driveThreshold || abs(master.get_analog(ANALOG_RIGHT_X)) > turnThreshold)
		{
			leftMotorPercent = master.get_analog(ANALOG_LEFT_Y);
			rightMotorPercent = master.get_analog(ANALOG_LEFT_Y);

			if(master.get_analog(ANALOG_RIGHT_X) > turnThreshold)
      {
             leftMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
             rightMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
      }
      else
      {
          leftMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
          rightMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
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
