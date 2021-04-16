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

	driveBase = new FourWheelDrive(rightWheelMotorVector, leftWheelMotorVector, inertialSensor, master);

	opticalSensor.set_led_pwm(50);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	delete driveBase;
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
	const double DELAY_TIME = 20;
	const double CYCLE_TIME = 1800;
	bool skills = false;

	//lets the sensor calibrate
	pros::delay(2000);

	unfold();

	setMotors(intakeMotorVector, intakeConst);
	bottomDrum = intakeConst;

	if(skills)
	{
		setOuttakePoop();

	  	//goal 1
		// Back ball into first goal
		driveBase->driveTilesPID(-0.35 );
		pros::delay(DELAY_TIME);

		//goal 2
		//move forward, grab ball, and cycle the bottom left goal
		driveBase->driveTilesPID(0.35 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(28);
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(1.9 );
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(-0.6 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(-45);
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(0.85 );
		autoCycle(CYCLE_TIME);
		pros::delay(DELAY_TIME);


		//goal 3
		// Back away from goal, turn to grab next ball, turn to left goal and cycle
		driveBase->driveTilesPID(-2.2 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(90);
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(1 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(0);
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(1.46 );
		autoCycle(CYCLE_TIME);
		pros::delay(DELAY_TIME);

		//goal 4
		//Back away from goal, turn to get next ball, turn toward top left goal, autoCycle
		driveBase->driveTilesPID(-0.92 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(92 );
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(2 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(0);
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(0.83 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(55 );
		pros::delay(DELAY_TIME);
		goalApproch(driveBase, 0.8, 75);
		driveBase->driveTilesPID(-0.1 );
		pros::delay(DELAY_TIME);
		autoCycle(CYCLE_TIME);
		pros::delay(DELAY_TIME);

		//goal 5
		// Back away from goal, turn to grab next ball, turn to left goal and cycle
		driveBase->driveTilesPID(-1 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(180);
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(1.95 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(90 );
		pros::delay(DELAY_TIME);
		goalApproch(driveBase, 0.8, 75);
		autoCycle(CYCLE_TIME);
		pros::delay(DELAY_TIME);

		//goal 6
		//Back away from goal, turn to get next ball, turn toward top left goal, autoCycle
		driveBase->driveTilesPID(-0.8 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(180 );
		pros::delay(DELAY_TIME);
		driveBase->driveTilesPID(1.8 );
		pros::delay(DELAY_TIME);
		driveBase->turnDegreesAbsolutePID(130 );
		pros::delay(DELAY_TIME);
		goalApproch(driveBase, 1.5, 75);
		driveBase->driveTilesPID(-0.1);
		pros::delay(DELAY_TIME);
		autoCycle(CYCLE_TIME*2);
		pros::delay(DELAY_TIME);

		driveBase->driveTilesPID(-1);
	}
	else
	{
		setOuttakeContain();

		//grab first ball
		setIntakeRun();
		driveBase->driveTilesPID(2.4);

		//grab second ball
		driveBase->turnDegreesAbsolutePID(-86);
		driveBase->driveTilesPID(-1.07);
		setIntakeHold();
		driveBase->turnDegreesAbsolutePID(0);

		//line up the goal
		setIntakeStop();
		driveBase->driveTilesPID(-0.5);
		driveBase->turnDegreesAbsolutePID(-90);
		driveBase->driveTilesPID(-0.7);
		driveBase->turnDegreesAbsolutePID(0);
		setIntakeHold();
		pros::delay(500);
		driveBase->driveTilesPID(0.6);
		setOuttakeTwo();

		//pick up last ball
		driveBase->driveTilesPID(-0.4);
		driveBase->turnDegreesAbsolutePID(-123);
		driveBase->driveTilesPID(2.8);
		setIntakeRun();
		pros::delay(1000);

		//shoot last goal
		//driveBase->turnDegreesAbsolutePID(-135);
		setIntakeHold();
		driveBase->driveTilesPID(0.5);
		setOuttakeInsert();
		pros::delay(2000);
		setOuttakeContain();

		//set for driver control
		driveBase->driveTilesPID(-1);
		driveBase->turnDegreesAbsolutePID(0);
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
	unfold();

	int topDrumLastVal = 0;
	int pooperLastVal = 0;
	int currentEjectTime = 0;
	int MAX_EJECT_TIME = 200;
	bool ejecting = false;
	int turnThreshold = 10;
	int driveThreshold = 10;
	int leftMotorPercent = 0;
	int rightMotorPercent = 0;
	int intakePercent = -intakeRest;
	int pooperPercent = 0;
	int inserterPercent = inserterRestingConst;


 	bool debounceButtonA = false;
 	bool debounceButtonB = false;
 	bool debounceButtonX = false;
 	bool debounceButtonY = false;
 	bool debounceButtonDOWN = false;
 	bool debounceButtonUP = false;
 	bool debounceButtonLEFT = false;
 	bool debounceButtonRIGHT = false;
 	bool debounceButtonR1 = false;
	bool debounceButtonL1 = false;
	bool debounceButtonR2 = false;
	bool debounceButtonL2 = false;


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
			if(pressButton(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1), debounceButtonR1))
	  		{
	          	if (intakePercent <= 0)
	          	{
	            	intakePercent = intakeConst;
	          	}
	            else
	            {
	                intakePercent = -intakeRest;
	            }
	        }

			// toggle score
			if(pressButton(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1), debounceButtonL1))
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

			//toggle eject
			else if(pressButton(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2), debounceButtonL2))
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

			if (pressButton(master.get_digital(pros::E_CONTROLLER_DIGITAL_A), debounceButtonA))
			{
				driveBase->turnDegreesAbsolutePID(90);
			}

			if (pressButton(master.get_digital(pros::E_CONTROLLER_DIGITAL_B), debounceButtonB))
			{
				driveBase->turnDegreesAbsolutePID(0);
			}

			if (pressButton(master.get_digital(pros::E_CONTROLLER_DIGITAL_X), debounceButtonX))
			{
				autoCycle();
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

			pros::lcd::set_text(3, "distance: " + std::to_string(opticalSensor.get_proximity()));

			setMotors(leftWheelMotorVector, leftMotorPercent);
			setMotors(rightWheelMotorVector, rightMotorPercent);
			setMotors(intakeMotorVector, intakePercent);
			pooper = pooperPercent;
			topDrum = inserterPercent;
			bottomDrum = bottomDrumConst;
 			pros::delay(loopDelay);
 		}
 }
