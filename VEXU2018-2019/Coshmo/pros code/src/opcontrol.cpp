
#include "helperfunctions.h"
#include "main.h"

/*
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
	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int intakePercent = 0;
	int liftPos = 0;
	int minLiftPos = 0;
	int anglerPos = 0;
	int anglerIndex = 0;
	int debounceButtonA = 0;
	int debounceButtonB = 0;
	int debounceButtonX = 0;
	int debounceButtonY = 0;
	int debounceButtonDOWN = 0;
	int debounceButtonUP = 0;
	int debounceButtonLEFT = 0;
	int debounceButtonRIGHT = 0;
	int loopDelay = 20;
	bool holdMode = false;
	bool turboMode = false;

	std::vector<int*> debounceButtons = {&debounceButtonX, &debounceButtonY,  &debounceButtonB, &debounceButtonA,  &debounceButtonUP, &debounceButtonDOWN, &debounceButtonLEFT, &debounceButtonRIGHT};
	liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while (true)
	{
		for(auto button : debounceButtons)
		{
			if (*button > 0)
			{
				*button -= loopDelay;
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    {
        if(debounceButtonB <= 0)
        {    //call hold mode
            doubleLaunch(launchMotors, anglerMotor, intakeMotors);
            debounceButtonB = 200;
        }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        if(debounceButtonDOWN <= 0)
        {    //call hold mode
            holdMode = !holdMode;
            debounceButtonDOWN = 200;
        }
    }
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
    {
        if(debounceButtonUP <= 0)
        {
            turboMode = !turboMode;
            debounceButtonUP = 200;
        }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        if(debounceButtonLEFT <= 0)
        {
						autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -360, 50);
            debounceButtonLEFT = 200;
        }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
    {
        if(debounceButtonRIGHT <= 0)
				{
						highScore(leftWheelMotorVector, rightWheelMotorVector, liftMotor);
            debounceButtonRIGHT = 200;
        }
    }
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
    	liftPos = 1500;
			minLiftPos = liftMotor.get_position();
    }
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			liftPos = 0;
			minLiftPos = liftMotor.get_position();
		}
		else
		{
			//liftPos = liftMotor.get_position();
			liftPos = minLiftPos;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
			if(debounceButtonX <= 0)
			{
    		launch(launchMotors, anglerMotor, anglerPos);
				debounceButtonX = 200;
			}
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			if(debounceButtonY <= 0)
			{
				autoDriveDistance( leftWheelMotorVector, rightWheelMotorVector, -1000, 50);
				debounceButtonY = 200;
			}
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			if(debounceButtonA <= 0)
			{
				anglerIndex = (anglerIndex + 1) % 3;
				anglerPos = anglerPositions[anglerIndex];
				debounceButtonA = 200;
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
				intakePercent = 100;
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			intakePercent = -100;
		}
		else
		{
			intakePercent = 0;
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
             leftMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
             rightMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
      }
      else
      {
          leftMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
          rightMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 2.0);
      }
		}
		else
		{
			leftMotorPercent = 0;
			rightMotorPercent = 0;
		}

		if(!turboMode)
		{
			leftMotorPercent *= .8;
			rightMotorPercent *= .8;
		}
		else
		{
			leftMotorPercent *= .9;
			rightMotorPercent *= .9;
		}

		setMotors(leftWheelMotorVector, leftMotorPercent);
		setMotors(rightWheelMotorVector, rightMotorPercent);
		setMotors(intakeMotors, intakePercent);
		liftMotor.move_absolute(liftPos, 127);
		anglerMotor.move_absolute(anglerPos, 50);
		pros::delay(loopDelay);
	}
}
