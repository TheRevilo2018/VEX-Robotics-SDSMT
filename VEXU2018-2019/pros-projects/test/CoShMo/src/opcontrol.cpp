
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
	int bottomIntakePercent = 0;
	int topIntakePercent = 0;
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

	while (true)
	{
		for(auto button : debounceButtons)
		{
			if (*button > 0)
			{
				*button -= loopDelay;
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
    	liftPos = liftPositions[3];
			minLiftPos = liftMotorLeft.get_position();
    }
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			liftPos = liftPositions[0];
			minLiftPos = liftMotorLeft.get_position();
		}
		else
		{
			liftPos = minLiftPos;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
				topIntakePercent = 90;
				bottomIntakePercent = 100;
				//put ball into upper section if already one ball loaded
				if(lightSensor.get_value() < NO_BALL_LIGHT_VALUE)
				{
					topIntakePercent = 100;
				}
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
				topIntakePercent = -100;
				bottomIntakePercent = -100;
		}
		else
		{
			topIntakePercent = 0;
			bottomIntakePercent = 0;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        if(debounceButtonDOWN <= 0)
        {
					autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 4000, 60); //a
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
						autonomous();
            debounceButtonLEFT = 200;
        }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
    {
        if(debounceButtonRIGHT <= 0)
				{
					  highScore(leftWheelMotorVector, rightWheelMotorVector,liftMotors, actuatorState);
            debounceButtonRIGHT = 200;
        }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
				if(debounceButtonB <= 0)
				{    //call hold mode
						doubleLaunch(launchMotors, anglerMotor, intakeMotors, manualAnglerPositions); //aa
						debounceButtonB = 200;
				}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
			if(debounceButtonX <= 0)
			{
    		launch(launchMotors, anglerMotor, anglerPos, false);
				debounceButtonX = 200;
			}
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			if(debounceButtonY <= 0)
			{
				actuatorState = !actuatorState;
				debounceButtonY = 200;
			}
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			if(debounceButtonA <= 0)
			{
				anglerIndex = (anglerIndex + 1) % 3;
				anglerPos = manualAnglerPositions[anglerIndex];
				debounceButtonA = 200;
			}
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
        leftMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 1.25);
      	rightMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 1.25);
      }
      else
      {
        leftMotorPercent -= fabs(master.get_analog(ANALOG_RIGHT_X) / 1.25);
        rightMotorPercent += fabs(master.get_analog(ANALOG_RIGHT_X) / 1.25);
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
		intakeTop = topIntakePercent;
		intakeBottom = bottomIntakePercent;
		liftMotorLeft.move_absolute(liftPos, 127);
		liftMotorRight.move_absolute(liftPos, 127); //a
		anglerMotor.move_absolute(anglerPos, 100);
		actuator.set_value(actuatorState);
		pros::lcd::set_text(1, "Launcher Light Sensor: " + std::to_string(lightSensor.get_value()));
		pros::lcd::set_text(2, "Lift Motor Postion: " + std::to_string( liftMotorLeft.get_position()));
		pros::lcd::set_text(3, "Launch Motor Brake Type: " + std::to_string( launchMotorLeft.get_brake_mode())); //a
		pros::lcd::set_text(4, "Gyro Value: " + std::to_string( gyro.get_value())); //a
		pros::lcd::set_text(5, "Angler Position: " + std::to_string( anglerMotor.get_position())); //aaaaa

		pros::delay(loopDelay);
	}
}
