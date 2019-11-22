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
  int mode = 4;
  switch(mode)
  {
    case(0):
    {
      //red long autonomous
      //forward to grab ball under capaaa
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2050, 60);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
      pros::delay(300);
      setMotors(intakeMotors, 0);

      //back up and turn around to grab cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -600, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1450);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -750, 60); //a
      pros::delay(180);

      //grab cap, turn to platform and drop on platform
      actuatorState = true;
      actuator.set_value(actuatorState);
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[2], 127);
      liftMotorRight.move_absolute(liftPositions[2], 127);
      pros::delay(400);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 510);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -200, 70); //a
      pros::delay(180);
      actuatorState = false;
      actuator.set_value(actuatorState);
      pros::delay(180);

      //back up, turn and align on platform
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 300, 40); //a
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127);
      pros::delay(400);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 200);
      pros::delay(180);
      //align
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
      pros::delay(180);

      //back away from platform and grab second cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 30); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1380);
      pros::delay(180);
      //TODO
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -500, 40); //a
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(400);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -350, 40); //aa

      /*
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -850, 40); //a
      pros::delay(180);

      */

      actuatorState = true;
      actuator.set_value(actuatorState);
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(400);
      //move into position for highscore from second cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 680);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1200, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 725);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1500, 40); //a
      pros::delay(180);

      //score the pole and align on platform
      highScore(leftWheelMotorVector, rightWheelMotorVector,liftMotors, actuatorState);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127);
      pros::delay(400);
      autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 130);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1200, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 140);
      pros::delay(180);
      //align
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
      pros::delay(180);

      //back up and realign
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 300, 40); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1350);
      pros::delay(180);
      //realign after spinning
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 800, 30); //a
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -400, 40); //a
      pros::delay(180);
      autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 230);
      pros::delay(180);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aaa
      anglerMotor.move_absolute(0, 100);
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 222);
      pros::delay(180);
      /*
      \
      liftMotorLeft.move_absolute(liftPositions[1], 127); //aa
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2700, 90); //a
      pros::delay(180);
      */
      break;
    }
    case(1):
    {
      //red short autonomous
      //forward to grab ball under cap
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2050, 60);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
      pros::delay(300);
      setMotors(intakeMotors, 0);

      //back up and turn around to grab cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -600, 60); //aa
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 440);
      pros::delay(180);
      pros::delay(30000);

      doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aa
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 60); //aaaa
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 340);
      pros::delay(180);


      //raise arm to get on platform correctly, then lower it after
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127); //aaaaaa
      pros::delay(400);
      setMotors(leftWheelMotorVector, 80);
      setMotors(rightWheelMotorVector, 80);
      pros::delay(1350);
      setMotors(leftWheelMotorVector, 0);
      setMotors(rightWheelMotorVector, 0);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127); //aaaaa
      pros::delay(400);
      anglerMotor.move_absolute(0, 100);
      pros::delay(400);
      anglerMotor = 0;
      pros::delay(200);
      break;

      case (2):
      {
        //blue short autonomous
        //forward to grab ball under cap
        setMotors(intakeMotors, 100);
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2050, 60);
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
        pros::delay(300);
        setMotors(intakeMotors, 0);

        //back up and turn around to grab cap
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -600, 60); //aa
        pros::delay(180);
        autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 365);
        pros::delay(180);
        pros::delay(30000); //TODO

        doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aa
        pros::delay(200);
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 170, 60); //aaaaaa
        pros::delay(180);
        autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 130);
        pros::delay(180);


        //raise arm to get on platform correctly, then lower it after
        liftMotorLeft.move_absolute(liftPositions[1], 127);
        liftMotorRight.move_absolute(liftPositions[1], 127); //aaaaaaaa
        pros::delay(400);
        setMotors(leftWheelMotorVector, 80);
        setMotors(rightWheelMotorVector, 80);
        pros::delay(1475);
        setMotors(leftWheelMotorVector, 0);
        setMotors(rightWheelMotorVector, 0);
        liftMotorLeft.move_absolute(liftPositions[0], 127);
        liftMotorRight.move_absolute(liftPositions[0], 127); //aaaaa
        pros::delay(400);
        anglerMotor.move_absolute(0, 100);
        pros::delay(400);
        anglerMotor = 0;
        pros::delay(200);
        break;
      }
      case(4):
      {
        doubleLaunch(launchMotors, anglerMotor, intakeMotors, anglerPositions); //aa
        pros::delay(15000);
        break;
      }
    }
  }
}


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2); //aaa
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
	setBrakes(launchMotors, pros::E_MOTOR_BRAKE_COAST); //aaaaa
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
            turboMode = !turboMode; //a
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
				//anglerPos += 10;

				anglerIndex = (anglerIndex + 1) % 3; //a
				anglerPos = manualAnglerPositions[anglerIndex]; //aaa
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
		liftMotorRight.move_absolute(liftPos, 127); //aaaaaaaaa
		if(anglerMotor.get_position() != 0 || anglerPos != 0)
		{
			anglerMotor.move_absolute(anglerPos, 100);
		}
		else
		{
			anglerMotor = 0;
		}
		actuator.set_value(actuatorState);
		pros::lcd::set_text(1, "Launcher Light Sensor: " + std::to_string(lightSensor.get_value()));
		pros::lcd::set_text(2, "Lift Motor Postion: " + std::to_string( liftMotorLeft.get_position()));
		pros::lcd::set_text(3, "Launch Motor Brake Type: " + std::to_string( launchMotorLeft.get_brake_mode())); //a
		pros::lcd::set_text(4, "Gyro Value: " + std::to_string( gyro.get_value())); //a
		pros::lcd::set_text(5, "Angler Position: " + std::to_string( anglerMotor.get_position())); //aaaaa

		pros::delay(loopDelay);
	}
}
