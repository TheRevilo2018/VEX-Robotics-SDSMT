#include "drive.h"

using namespace std;

//calibration
void FourWheelDrive::readCalibration()
{
	char buf[2048]; // This just needs to be larger than the contents of the file

	FILE* usd_file_read = fopen("/usd/calibration.txt", "r");
    if(usd_file_read == NULL)
    {
      Brain.Screen.setCursor(0, 0);
      Brain.Screen.print("File couldn't be opened");
    }
	else
	{
		fread(buf, 1, 2048, usd_file_read); // passing 1 because a `char` is 1 byte, and 2048 b/c it's the length of buf
		fclose(usd_file_read); // always close files when you're done with them

		fileStream.str() = string(buf);

		fileStream >> maxSpeed;
		fileStream >> minSpeed;
		fileStream >> speedBias;

		fileStream >> LRBiasHigh;
		fileStream >> LRBiasLow;
		fileStream >> LRBiasHighBack;
		fileStream >> LRBiasLowBack;
		fileStream >> maxAccelerationForward;
		fileStream >> maxAccelerationBackward;

    Brain.Screen.setCursor(6, 0);
    Brain.Screen.print("file input sucessful");
	}

	midSpeed = (maxSpeed + minSpeed) / 2;
}

void FourWheelDrive::writeCalibration()
{
	const string DELIM = " ";
	fileStream.clear();

	fileStream << maxSpeed << DELIM;
	fileStream << minSpeed << DELIM;
	fileStream << speedBias << DELIM;

	fileStream << LRBiasHigh << DELIM;
	fileStream << LRBiasLow << DELIM;
	fileStream << LRBiasHighBack << DELIM;
	fileStream << LRBiasLowBack << DELIM;
	fileStream << maxAccelerationForward << DELIM;
	fileStream << maxAccelerationBackward;


    FILE* usd_file_write = fopen("/usd/calibration.txt", "w");
    fputs(fileStream.str().c_str(), usd_file_write);
    fclose(usd_file_write);
}

/*void FourWheelDrive::calibrateAll()
{
    int count = 0;
      Brain.Screen.setCursor(6, 0);
      Brain.Screen.print("Calling calibration");
    lcd::set_text(2, );
    inertialSensor->reset();
	lcd::set_text(2, "status: " + to_string(inertialSensor->get_status()));
	lcd::set_text(3,  strerror(errno));

	pros::delay(2000);

	while(inertialSensor->is_calibrating())
    {
        lcd::set_text(4, "is calibrating   " + to_string(count));
        delay(LOOP_DELAY);
        count++;
    }

	lcd::set_text(2, "status:" + to_string(inertialSensor->get_status()));
	lcd::set_text(3,  strerror(errno));

	calibrateMinSpeed();
    calibrateMaxAcceleration();
    calibrateMaxSpeed();
    calibrateDrift();

    writeCalibration();

	showOff();
}


void FourWheelDrive::calibrateMinSpeed()
{
    double speed = 0;
    int count = 0;
    waitForUser("calibrate min speed");

    while(count < 250)
    {
        if (getAllSpeed() > 0)
        {
            count++;
        }
        else
        {
            speed = speed + 0.02;
            lcd::set_text(5, "min speed: " + to_string(speed));
            setMotors(speed);
            count = 0;
        }
		lcd::set_text(7, strerror(errno));
        delay(LOOP_DELAY);
    }

    minSpeed = speed;
    setMotors(0);
}


void FourWheelDrive::calibrateMaxAcceleration()
{
    const double PITCH_TOLERENCE = 10;
    const int NUM_LOOPS = 30;
	const int COMPLETE = 3;
    int forwardComplete = 0;
    int backwardComplete = 0;
    double speed = 0;
    int count = 0;
	double stationaryPitch = 0;
	double maxPitch = 0;
	double minPitch = 0;

	double totalLoopAccelForward = 0;
	double totalLoopAccelBackward = 0;
	double maxLoopAccelForward = -1000;
	double maxLoopAccelBackward = 1000;


    maxAccelerationForward = 0;
    maxAccelerationBackward = 0;
    setBrakes(E_MOTOR_BRAKE_COAST);

	waitForUser("calibrate max acceleration");

	for (int i = 0; i < NUM_LOOPS; i++)
	{
		stationaryPitch += inertialSensor->get_pitch();
		delay(LOOP_DELAY);
	}
	stationaryPitch /= NUM_LOOPS;

    //part 1
    while(forwardComplete <= COMPLETE || backwardComplete <= COMPLETE)
    {
        if (forwardComplete == 0)
        	{maxAccelerationForward += 0.5;}
        if (backwardComplete == 0)
        	{maxAccelerationBackward += 0.5;}

		totalLoopAccelForward = 0;
		totalLoopAccelBackward = 0;

		//drive forward
        count = 0;
        lcd::set_text(2, "max accel forwards: " + to_string(maxAccelerationForward));
		lcd::set_text(3, "max accel backwards: " + to_string(maxAccelerationBackward));
        while(count < NUM_LOOPS)
        {
            speed += maxAccelerationForward;
			setMotors(speed);

			float pitch = inertialSensor->get_pitch();
			if (pitch > (stationaryPitch + PITCH_TOLERENCE))
			{
				forwardComplete = true;
				maxPitch = pitch;
			}

			totalLoopAccelForward += inertialSensor->get_accel().x;
            count++;

			lcd::set_text(4, "pitch: " + to_string(pitch) + " max: " + to_string(maxPitch));
			delay(LOOP_DELAY);
        }
		//stop
        while(speed > 0)
        {
            speed -= maxAccelerationBackward;
            setMotors(speed);

			float pitch = inertialSensor->get_pitch();
			if (pitch < (stationaryPitch - PITCH_TOLERENCE))
			{
				backwardComplete = true;
				minPitch = pitch;
			}

			delay(LOOP_DELAY);
			lcd::set_text(4, "pitch: " + to_string(pitch) + " max: " + to_string(maxPitch));
        }

		setMotors(0);
		delay(200);

		//drive backward
        count = 0;
        while(count < NUM_LOOPS)
        {
            speed -= maxAccelerationBackward;
			setMotors(speed);

			float pitch = inertialSensor->get_pitch();
			if (pitch < (stationaryPitch - PITCH_TOLERENCE))
			{
				backwardComplete = true;
				minPitch = pitch;
			}

			totalLoopAccelBackward += inertialSensor->get_accel().x;
            count++;

		 	delay(LOOP_DELAY);
			lcd::set_text(4, "pitch: " + to_string(pitch) + " max: " + to_string(maxPitch));
        }
		//stop
        while(speed < 0)
        {

            speed += maxAccelerationForward;
            setMotors(speed);

			float pitch = inertialSensor->get_pitch();
			if (pitch > (stationaryPitch + PITCH_TOLERENCE))
			{
				forwardComplete = true;
				maxPitch = pitch;
			}

			delay(LOOP_DELAY);
			lcd::set_text(4, "pitch: " + to_string(pitch) + " max: " + to_string(maxPitch));
        }

		setMotors(0);
		delay(200);

		lcd::set_text(5, "loop accel forwards: " + to_string(totalLoopAccelForward));
		lcd::set_text(6, "loop accel backwards: " + to_string(totalLoopAccelBackward));
		lcd::set_text(7, strerror(errno));

		if(maxLoopAccelForward <= totalLoopAccelForward)
		{
			maxLoopAccelForward = totalLoopAccelForward;
			forwardComplete = 0;
		}
		else
		{
			forwardComplete++;
		}

		if(maxLoopAccelBackward >= totalLoopAccelBackward)
		{
			maxLoopAccelBackward = totalLoopAccelBackward;
			backwardComplete = 0;
		}
		else
		{
			backwardComplete++;
		}

		if(master->get_digital(E_CONTROLLER_DIGITAL_A))
		{
			lcd::set_text(5, "wait for user");
			while(master->get_digital(E_CONTROLLER_DIGITAL_A))
			{
				delay(LOOP_DELAY);
			}
			waitForUser("paused accel function");
		}
    }

	lcd::set_text(1, "max acceleration calibration finished");
}


void FourWheelDrive::calibrateMaxSpeed()
{
	const int LOOPS = 25;
	double tempInstructedSpeed = 0;
	double tempOutputSpeed = 0;
	double maxOutputSpeed = 0;
	maxSpeed = 0;
	int count = 0;

    waitForUser("calibrate max speed");

	while(count < LOOPS)
	{
		rawSetMotors(tempInstructedSpeed);
		delay(LOOP_DELAY);
		tempOutputSpeed = getAllSpeed();
		lcd::set_text(4, "act: " + to_string(maxOutputSpeed)
		 	+ " inst: " + to_string(tempInstructedSpeed));
		lcd::set_text(7, strerror(errno));

		tempInstructedSpeed += maxAccelerationForward * 0.5;
		if(tempOutputSpeed > maxOutputSpeed)
		{
			count = 0;
			maxOutputSpeed = tempOutputSpeed;
		}
		else
		{
			count++;
		}
	}

	rawSetMotors(0);
	delay(LOOP_DELAY * 100);
	maxOutputSpeed = maxOutputSpeed * 0.95;
	tempOutputSpeed = getAllSpeed();
	waitForUser("calibrate max speed");

	tempInstructedSpeed = 0;
	double tempOutputMax = 0;

	while (tempOutputSpeed < maxOutputSpeed)
	{
		rawSetMotors(tempInstructedSpeed);
		delay(LOOP_DELAY);
		tempOutputSpeed = getAllSpeed();
		lcd::set_text(5, "act: " + to_string(maxOutputSpeed)
		 	+ " inst: " + to_string(maxSpeed));
		lcd::set_text(7, strerror(errno));
		if(tempOutputSpeed >= tempOutputMax)
		{
			tempInstructedSpeed += maxAccelerationForward * 0.5;
			tempOutputMax = tempOutputSpeed;
			maxSpeed = tempInstructedSpeed;
		}
	}

	rawSetMotors(0);
	speedBias = maxSpeed / maxOutputSpeed;
	//max safe speed
	maxSpeed = maxSpeed * 0.9;
	midSpeed = (maxSpeed + minSpeed) / 2;

	lcd::set_text(6, "Speed bias: " + to_string(speedBias));
	lcd::set_text(7, "calibrating max speed finished");
}

void FourWheelDrive::calibrateDrift()
{
	calibrateDriftLoop(midSpeed, LRBiasLow);
	calibrateDriftLoop(-midSpeed, LRBiasLowBack);
	calibrateDriftLoop(maxSpeed, LRBiasHigh);
	calibrateDriftLoop(-maxSpeed, LRBiasHighBack);

}

void FourWheelDrive::calibrateDriftLoop(double testSpeed, double &bias)
{
	const double CHANGE_TOLERANCE = 0.01;
	int numLoops = 100;
	double rightSide = 0;
	double leftSide = 0;
	double proposedChange = 0;

	do
	{
		waitForUser("calibrate drift bias");
		bias += proposedChange;
		lcd::set_text(6, "new bias: " + to_string(bias));

		accelerate(testSpeed);
		setZeroPosition();
		for(int i = 0; i < numLoops; i++)
		{
			delay(LOOP_DELAY);
		}

		rightSide = getPosition(rightMotors);
		leftSide = getPosition(leftMotors);
		proposedChange = (leftSide / rightSide) - 1;

		lcd::set_text(4, "right position: " + to_string(rightSide));
		lcd::set_text(5, "left position: " + to_string(leftSide));

		accelerate(0);

		lcd::set_text(7, "calibrating drift loop");
	} while(fabs(proposedChange) > CHANGE_TOLERANCE);
	lcd::set_text(7, "calibrate drift loop complete");
}





void FourWheelDrive::showOff()
{
	waitForUser("rock back and forth");
	while(true)
	{
		accelerate(maxSpeed);
		delay(500);
		accelerate(-maxSpeed);
		delay(500);
	}
}

void FourWheelDrive::waitForUser(string message)
{
	lcd::set_text(1, "Waiting for user");
	lcd::set_text(2, message);
	lcd::set_text(3, "press A to continue");

	while(!master->get_digital(E_CONTROLLER_DIGITAL_A))
	{
		delay(LOOP_DELAY);
	}

	lcd::set_text(1, "running");
	lcd::set_text(2, message);
	lcd::set_text(3, "please wait");
}

bool FourWheelDrive::panic()
{
    return master->get_digital(E_CONTROLLER_DIGITAL_A) || master->get_digital(E_CONTROLLER_DIGITAL_B);
}
*/