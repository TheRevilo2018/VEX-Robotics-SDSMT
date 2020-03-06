#include "../include/main.h"
#include "../include/helperfunctions.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous()
{
	int blue = 1;
	int red = 2;

	switch(blue)
	{
			case(0):
			{
				/*
				unFold();
				driveDist(0.5, BACKWARD, -1);
				cubeRun(1.5, 2);
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -60);
				cubeSet();

				//     #
				//grab ###
				cubeRun(2.5, 3);
				cubeSet();

				//grab third next to pole
				//autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -5);
				//cubeRun(1.1, 3);
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 80);
				//cubeSet();
				driveDist(2.4, BACKWARD, 4);
				driveDist(0.4, FORWARD, -1);
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 85);
				driveDist(3.1, FORWARD, 4);
				depositStack();
				break;
				*/
			}
			//blue auton
			case (1):
			{
				unFold();
				pros::delay(3000);

				//align on wall
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -60);
				driveDist(1.0, BACKWARD, -1);

				//grab corner cube
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 20);
				setMotors(intakeMotors, 100);
				driveDist(2.0, FORWARD, -1);

				//grab cube between first and goal
				driveDist(0.7, BACKWARD, -1);
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -70);
				driveDist(1.9, FORWARD, -1);
				driveDist(0.5, BACKWARD, -1);

				//back up and grab cube near middle tower
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -20);
				driveDist(0.8, FORWARD, -1);

				pros::delay(500);
				setMotors(intakeMotors, 0);

				//back up, spin and deposit
				//driveDist(3.0, BACKWARD, -1);
				//autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -70);
				///driveDist(3.0, FORWARD, -1);
				//depositStack();
				break;
			}
			//red auton
			case(2):
			{
				unFold();
				pros::delay(3000);

				//align on wall
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 60);
				driveDist(1.0, BACKWARD, -1);

				//grab corner cube
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -20);
				setMotors(intakeMotors, 100);
				driveDist(2.0, FORWARD, -1);

				//back up and grab cube near middle tower
				driveDist(0.7, BACKWARD, -1);
				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 70);
				driveDist(1.9, FORWARD, -1);
				driveDist(0.5, BACKWARD, -1);

				autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 20);
				driveDist(0.8, FORWARD, -1);

				pros::delay(500);
				setMotors(intakeMotors, 0);
				break;
			}
		}
	}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(2, "Calling initialize: " + std::to_string(pros::millis()));
	//visionSensor.clear_led();

	//2911 for no ball
	//1896 for ball
	lightSensor.calibrate();
	setBrakes(intakeMotors, pros::E_MOTOR_BRAKE_HOLD);
	setBrakes(trayMotors, pros::E_MOTOR_BRAKE_HOLD);
	setBrakes(liftMotors, pros::E_MOTOR_BRAKE_HOLD);
	//middleLightSensor.calibrate();
	}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::lcd::set_text(3, "Calling disabled: " + std::to_string(pros::millis()));
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pros::lcd::set_text(4, "Calling competition_initialize: " + std::to_string(pros::millis()));
}



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
	pros::lcd::set_text(5, "Calling op_control: " + std::to_string(pros::millis()));
	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int intakeSpeed = 0;
	int traySpeed = 0;
	int liftSpeed = 0;
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


	setBrakes(trayMotors, pros::E_MOTOR_BRAKE_COAST);
	setBrakes(liftMotors, pros::E_MOTOR_BRAKE_COAST);

	while (true)
	{

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			if(pressButton(debounceButtonX))
			{
				intakeSpeed = 120;
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			if(pressButton(debounceButtonA))
			{
				intakeSpeed = -60;
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    {
      if(pressButton(debounceButtonB))
			{
				intakeSpeed = -120;
      }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			if(pressButton(debounceButtonY))
			{
				intakeSpeed = 60;
			}
		}

		//UP is unbound
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			if(pressButton(debounceButtonDOWN))
			{
				intakeSpeed = 0;
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
			if(pressButton(debounceButtonRIGHT))
			{
				depositStack();
			}
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			if(pressButton(debounceButtonLEFT))
			{
				//unFold();
			}
		}

		trayHitting = (trayBumperLeft.get_value() == 1 || trayBumperRight.get_value() == 1);
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && trayLeft.get_position() < TRAY_MAX_HEIGHT && trayRight.get_position() < TRAY_MAX_HEIGHT)
    {
			traySpeed = 100;
    }
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !trayHitting)
		{
			traySpeed = -100;
		}
		else
		{
			traySpeed = 0;
		}


		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
			if(pressButton(debounceButtonR1))
			{
				trayLock = true;
				liftLeft.move_absolute(liftPositions[liftIndex], 120);
				liftRight.move_absolute(liftPositions[liftIndex], 120);
				trayLeft.move_absolute(trayPositions[liftIndex], 120);
				trayRight.move_absolute(trayPositions[liftIndex], 120);
				liftIndex += 1;
				liftIndex = std::min(1, liftIndex);
			}
    }

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			//unlock automatic control of tray and lift, reset index to medium position, and move down
			trayLock = false;
			liftSpeed = -120;
			liftIndex = 0;
		}
		else
		{
			liftSpeed = 0;
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

				setMotors(leftWheelMotorVector, leftMotorPercent);
				setMotors(rightWheelMotorVector, rightMotorPercent);
				setMotors(intakeMotors, intakeSpeed);

				if(!trayLock)
				{
					setMotors(trayMotors, traySpeed);
					setMotors(liftMotors, liftSpeed);
				}

				pros::lcd::set_text(3, "leftLift: " + std::to_string(liftLeft.get_position()));
				pros::lcd::set_text(4, "rightLift: " + std::to_string(liftRight.get_position()));
				pros::lcd::set_text(5, "trayLeft: " + std::to_string(trayLeft.get_position()));
				pros::lcd::set_text(6, "trayRight: " + std::to_string(trayRight.get_position()));
				pros::lcd::set_text(6, "gyro: " + std::to_string(gyro.get_value()));
				pros::delay(loopDelay);
	}
}
