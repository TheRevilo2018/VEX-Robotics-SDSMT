#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	FourWheelDrive tempBase(rightWheelMotorVector, leftWheelMotorVector, inertialSensor, master);

	driveBase = &tempBase;

	visionSensor.clear_led();
	visionSensor.set_signature(RED_BALL_SIG_INDEX, &RED_BALL_SIG);
	visionSensor.set_signature(BLUE_BALL_SIG_INDEX, &BLUE_BALL_SIG);
	visionSensor.set_signature(BACKPLATE_SIG_INDEX, &BACKPLATE_SIG);


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
		while(true)
		{
			autoIntake();
		}
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

	int topDrumLastVal = 0;
	int pooperLastVal = 0;
	int currentEjectTime = 0;
	int MAX_EJECT_TIME = 200;
	bool ejecting = false;
	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int intakePercent = 0;
	int pooperPercent = 0;
	int inserterPercent = inserterRestingConst;

	const int seenBufferSize = 6;
	std::vector<Color> seenBuffer(seenBufferSize, NA);

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


	if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R1))
	{
		if(master.get_digital(DIGITAL_X))
		{
			driveBase->showOff();
		}
		{
			driveBase->calibrateAll();
		}
	}

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

			auto lastSeenBall = getBallColor();
			pros::lcd::set_text(4, "Got Color: " + std::to_string(lastSeenBall));

			std::rotate(seenBuffer.begin(), seenBuffer.begin()+1, seenBuffer.end());
			seenBuffer[0] = lastSeenBall;
			int ejectTotal = 0;
			for(int i = 0; i < seenBufferSize; i++)
			{
				if(seenBuffer[i] == colorToPoop)
				{
					ejectTotal++;
				}
			}

			if(ejectTotal > seenBufferSize/2)
			{
				ejecting = true;
				topDrumLastVal = inserterPercent;
				pooperLastVal = pooperPercent;
			}
			// Check for ball to auto-poop
			if(ejecting)
			{
				setIntakePoop();
				if(currentEjectTime > MAX_EJECT_TIME)
				{
					ejecting = false;
					currentEjectTime = 0;
					inserterPercent = topDrumLastVal;
					pooperPercent = pooperLastVal;
				}
				else
				{
					currentEjectTime += loopDelay;
				}
			}
			else
			{
				// Run bottom drum idle speed
				// Run top drum on variable speed
				topDrum = inserterPercent;
				pooper = pooperPercent;
			}
			setMotors(leftWheelMotorVector, leftMotorPercent);
			setMotors(rightWheelMotorVector, rightMotorPercent);
			setMotors(intakeMotorVector, intakePercent);

			bottomDrum = intakeConst;
 			pros::delay(loopDelay);
 		}
 }
