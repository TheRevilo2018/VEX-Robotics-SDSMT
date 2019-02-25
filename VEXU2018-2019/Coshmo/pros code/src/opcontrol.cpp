
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

	pros::Motor wheelLeft1(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelLeft2(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelLeft3(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelLeft4(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelRight1(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelRight2(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelRight3(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor wheelRight4(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor liftMotor(11, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor launchMotorLeft(12, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor anglerMotor(13, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor intakeTop(17, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor launchMotorRight(19, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor intakeBottom(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int intakePercent = 0;
	int liftPos = 0;
	int minLiftPos = 0;
	int anglerPos = 0;
	int debounceButtonB = 0;
	int debounceButtonY = 0;
	int debounceButtonDOWN = 0;
	int debounceButtonUP = 0;
	int loopDelay = 20;
	bool holdMode = false;
	bool turboMode = false;

	std::vector<pros::Motor> wheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3, wheelLeft4, wheelRight1, wheelRight2, wheelRight3, wheelRight4 };
	std::vector<pros::Motor> leftWheelMotorVector = {wheelLeft1, wheelLeft2, wheelLeft3, wheelLeft4 };
	std::vector<pros::Motor> rightWheelMotorVector = {wheelRight1, wheelRight2, wheelRight3, wheelRight4 };
	std::vector<pros::Motor> intakeMotors = {intakeTop, intakeBottom};
	std::vector<int*> debounceButtons = {&debounceButtonY, &debounceButtonUP, &debounceButtonDOWN, &debounceButtonB};

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
            doubleLaunch(launchMotorLeft, launchMotorRight, anglerMotor, intakeMotors);
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
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			launchMotorLeft = 127;
			launchMotorRight = 127;
		}
		else
		{
			launchMotorLeft = 0;
			launchMotorRight = 0;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
    	liftPos = 1000;
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
    	anglerPos = 60;
    }
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			anglerPos = 30;
		}
		else
		{
			anglerPos = 0;
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
		//anglerMotor = anglerPos;
		anglerMotor.move_absolute(anglerPos, 50);
		pros::delay(loopDelay);
	}
}
