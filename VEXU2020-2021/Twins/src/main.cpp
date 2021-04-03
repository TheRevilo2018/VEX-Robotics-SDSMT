#include "../include/main.h"
#include "../include/helperfunctions.h"
#include "../include/twinRun.h"
#include "four_wheel_drive/drive.h"
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

	auto rightWheelVectorsAlpha = rightWheelVectorPair[0];
	auto leftWheelVectorsAlpha = leftWheelVectorPair[0];
	FourWheelDrive driveBaseAlpha(rightWheelVectorsAlpha, leftWheelVectorsAlpha);

	int blue = 1;
	int red = 2;

	driveBaseAlpha.driveDist(4.0, FORWARD);

	rightWheelVectorsAlpha[2].set_zero_position(0);

	pros::lcd::set_text(6, "auton finished " + std::to_string(rightWheelVectorsAlpha[2].get_position()));


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
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(2, "Calling initialize: " + std::to_string(pros::millis()));
	//visionSensor.clear_led();

	//2911 for no ball
	//1896 for ball
	inertialSensorAlpha.reset();
	inertialSensorBeta.reset();
	//middleLightSensor.calibrate();

	inserterAlpha.set_brake_mode(MOTOR_BRAKE_HOLD);
	inserterBeta.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
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
	pros::Task opControlAlpha(twin::opcontrolTask, (void*)0,
	 TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Alpha op control");
	pros::Task opControlBeta(twin::opcontrolTask, (void*)1,
	TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Beta op control");
}
