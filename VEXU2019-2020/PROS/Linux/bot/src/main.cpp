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


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
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
	pros::lcd::set_text(2, "Starting...");

	pros::lcd::register_btn1_cb(on_center_button); //aaa
	//visionSensor.clear_led();

	//2911 for no ball
	//1896 for ball
	lightSensor.calibrate();
	//middleLightSensor.calibrate();
	setBrakes(liftMotors, pros::E_MOTOR_BRAKE_COAST);
	setBrakes(launchMotors, pros::E_MOTOR_BRAKE_COAST);
	anglerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	pros::lcd::set_text(1, "Launcher Light Sensor: " + std::to_string(lightSensor.get_value()));
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}



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
  bool yep = false;

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
			{
        yep = !yep;
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

		pros::delay(loopDelay);
	}
}
