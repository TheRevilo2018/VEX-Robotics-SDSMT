#include "main.h"
#include "helperfunctions.h"
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
	//middleLightSensor.calibrate();
	setBrakes(liftMotors, pros::E_MOTOR_BRAKE_COAST);
	setBrakes(launchMotors, pros::E_MOTOR_BRAKE_COAST);
	anglerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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
	int bottomIntakePercent = 0;
	int topIntakePercent = 0;
	int intakePercent = 0;
	int liftPos = 0;
	int minLiftPos = 0;
	int anglerPos = 0;
	int anglerIndex = 0;
	std::uint32_t debounceButtonA = 0;
	std::uint32_t debounceButtonB = 0;
	std::uint32_t debounceButtonX = 0;
	std::uint32_t debounceButtonY = 0;
	std::uint32_t debounceButtonDOWN = 0;
	std::uint32_t debounceButtonUP = 0;
	std::uint32_t debounceButtonLEFT = 0;
	std::uint32_t debounceButtonRIGHT = 0;
	int loopDelay = 20;
	bool holdMode = false;
	bool turboMode = false;
  bool yep = false;

	while (true)
	{

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    {
      if(pressButton(debounceButtonB))
			{
        yep = !yep;
      }
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			if(pressButton(debounceButtonA))
			{
						autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 180, 90);
			}
		}

    if(yep)
    {
      setMotors(intakeMotors, -120);
    }
    else
    {
      setMotors(intakeMotors, 0);
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

		pros::delay(loopDelay);
	}
}
