#include "../include/main.h"
#include "../include/helperfunctions.h"
#include "four_wheel_drive/drive.h"

using namespace std;
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

	FourWheelDrive driveBase(rightWheelMotorVector, leftWheelMotorVector, inertialSensor, master);

	int blue = 1;
	int red = 2;

	rightWheelMotorVector[2].set_zero_position(0);

	pros::lcd::set_text(6, "auton finished " + std::to_string(rightWheelMotorVector[2].get_position()));


	switch(blue)
	{
			case(0):
			{
			}
			//blue auton
			case (1):
			{
				break;
			}
			//red auton
			case(2):
			{
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
	pros::lcd::set_text(0, "Calling initialize: " + std::to_string(pros::millis()));
	//visionSensor.clear_led();
	//2911 for no ball
	//1896 for ball
	//lightSensor.calibrate();
	//middleLightSensor.calibrate();
	}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::lcd::set_text(6, "Calling disabled: " + std::to_string(pros::millis()));
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
	pros::lcd::set_text(1, "Calling competition_initialize: " + std::to_string(pros::millis()));
}

void calibrate()
{
	FourWheelDrive driveBase(rightWheelMotorVector, leftWheelMotorVector, inertialSensor, master);
	driveBase.calibrateAll();
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
	FourWheelDrive driveBase(rightWheelMotorVector, leftWheelMotorVector, inertialSensor, master);
	pros::lcd::set_text(2, "Calling op_control: " + std::to_string(pros::millis()));
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

	if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R1))
	{
		calibrate();
	}
	else
	{
		while (true)
		{
			if(abs(master.get_analog(ANALOG_LEFT_Y)) > driveThreshold || abs(master.get_analog(ANALOG_RIGHT_X)) > turnThreshold)
			{
				leftMotorPercent = master.get_analog(ANALOG_LEFT_Y);
				rightMotorPercent = master.get_analog(ANALOG_LEFT_Y);

				if(master.get_analog(ANALOG_RIGHT_X) > turnThreshold)
		      	{
		        	leftMotorPercent += abs(master.get_analog(ANALOG_RIGHT_X));
		      		rightMotorPercent -= abs(master.get_analog(ANALOG_RIGHT_X));
		      	}
		      	else
		      	{
		        	leftMotorPercent -= abs(master.get_analog(ANALOG_RIGHT_X));
		        	rightMotorPercent += abs(master.get_analog(ANALOG_RIGHT_X));
		      	}
			}
			else
			{
				leftMotorPercent = 0;
				rightMotorPercent = 0;
			}

			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
			{
			 	if(pressButton(debounceButtonA))
			 	{
					driveBase.driveTilesPID(4.0, 75);
			 	}
			}

			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
			{
			 	if(pressButton(debounceButtonB))
			 	{
					driveBase.turnDegreesPID(90, 75);
			 	}
			}

			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
			{
			 	if(pressButton(debounceButtonX))
			 	{
					driveBase.turnDegreesPID(-90, 75);
			 	}
			}


			setMotors(leftWheelMotorVector, leftMotorPercent);
			setMotors(rightWheelMotorVector, rightMotorPercent);
			pros::delay(loopDelay);
		}
	}
}
