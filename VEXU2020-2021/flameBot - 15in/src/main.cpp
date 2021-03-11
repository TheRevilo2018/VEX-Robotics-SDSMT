#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
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
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
		unfold();
}

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
 	pros::lcd::set_text(2, "Calling op_control: " + std::to_string(pros::millis()));

	const int inserterConst = 110;
	const int inserterRestingConst = -40;
	const int intakeConst = 85;
	const int pooperConst = 85;

	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int intakePercent = 0;
	int pooperPercent = 0;
	int inserterPercent = inserterRestingConst;

 	std::uint32_t debounceButtonA = 0;
 	std::uint32_t debounceButtonB = 0;
 	std::uint32_t debounceButtonX = 0;
 	std::uint32_t debounceButtonY = 0;
 	std::uint32_t debounceButtonDOWN = 0;
 	std::uint32_t debounceButtonUP = 0;
 	std::uint32_t debounceButtonLEFT = 0;
 	std::uint32_t debounceButtonRIGHT = 0;
 	std::uint32_t debounceButtonR1 = 0;
	std::uint32_t debounceButtonL1 = 0;
	std::uint32_t debounceButtonR2 = 0;
	std::uint32_t debounceButtonL2 = 0;
 	int loopDelay = 20;

 		while (true)
 		{
			//toggle in
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
	  		{
	  			if(pressButton(debounceButtonR1))
	  			{
	          		if (intakePercent <= 0)
	          		{
	            		intakePercent = intakeConst;
	          		}
	          		else
	          		{
	            		intakePercent = 0;
	          		}
	  			}
	  		}
			//toggle out
	        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
	        {
	            if(pressButton(debounceButtonR2))
	            {
	                if ( intakePercent >= 0)
	                {
	                    intakePercent = -intakeConst;
	                  }
	                else
	                {
	                    intakePercent = 0;
	                  }
	            }
	        }

			// toggle score
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
	        {
	            if(pressButton(debounceButtonL1))
	            {
	                if (inserterPercent <= 0)
	                {
	                    inserterPercent = inserterConst;
						pooperPercent = -pooperConst;
	                }
	                else
	                {
	                    inserterPercent = inserterRestingConst;
						pooperPercent = 0;
	                }
	            }
	        }

			//toggle eject
			else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
			{
				if(pressButton(debounceButtonL2))
				{
					if (pooperPercent <= 0)
					{
						inserterPercent = -inserterConst;
						pooperPercent = pooperConst;
					}
					else
					{
						inserterPercent = inserterRestingConst;
						pooperPercent = 0;
					}
				}
			}

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

 			setMotors(leftWheelMotorVector, leftMotorPercent);
 			setMotors(rightWheelMotorVector, rightMotorPercent);
			setMotors(intakeMotorVector, intakePercent);
			// Run bottom drum idle speed
			bottomDrum = intakeConst;
			// Run top drum on variable speed
			topDrum = inserterPercent;
			pooper = pooperPercent;
 			pros::delay(loopDelay);
 		}
 }
