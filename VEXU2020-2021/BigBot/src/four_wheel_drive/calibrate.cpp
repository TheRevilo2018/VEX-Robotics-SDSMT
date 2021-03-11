#include "drive.h"

using namespace pros;
using namespace std;

//calibration
void FourWheelDrive::readCalibration()
{
	FILE* usd_file_read = fopen("/usd/calibration.txt", "r");
    if(usd_file_read == NULL)
    {
        pros::lcd::set_text(6, "file couldn't open");
    }
	char buf[2048]; // This just needs to be larger than the contents of the file
	fread(buf, 1, 2048, usd_file_read); // passing 1 because a `char` is 1 byte, and 50 b/c it's the length of buf
	fclose(usd_file_read); // always close files when you're done with them

    fileStream.str() = string(buf);

    fileStream >> maxInstructedSpeed;
    fileStream >> minSpeed;
    fileStream >> LRBias;
    fileStream >> maxAccelerationForward;
    fileStream >> maxAccelerationBackward;
    fileStream >> distanceMultiplier;
}

void FourWheelDrive::writeCalibration()
{
    FILE* usd_file_write = fopen("/usd/calibration.txt", "w");
    fputs(fileStream.str().c_str(), usd_file_write);
    fclose(usd_file_write);
}

void FourWheelDrive::calibrateAll()
{
    int count = 0;
    lcd::set_text(2, "Calling calibration");
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
    //master->set_text(0, 2, "calibrated drive ");
	lcd::set_text(2, "status:" + to_string(inertialSensor->get_status()));
	lcd::set_text(3,  strerror(errno));

	//correctGyroCalibration(-0.02, -0.01);

	waitForUser("calibrate min speed");
	calibrateMinSpeed();
	waitForUser("calibrate max acceleration");
    calibrateMaxAcceleration(10);
	maxAccelerationForward = 5; //remove once actual is found
	maxAccelerationBackward = 5;
	waitForUser("calibrate max speed");
    calibrateMaxSpeed();
    calibrateDrift();
	accelerate(-80);


    //writeCalibration();
	lcd::clear();
    lcd::set_text(3, "Calibration complete");
}


void FourWheelDrive::calibrateMinSpeed()
{
    double speed = 0;
    int count = 0;
    lcd::set_text(4, "calibrating min speed");

    while(count < 100)
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


void FourWheelDrive::calibrateMaxAcceleration(double returnSpeed)
{
    const double GYRO_TOLERENCE = 10;
    const int NUM_LOOPS = 50;
    const int IN_BETWEEN = LOOP_DELAY * 10;
    bool forwardComplete = false;
    bool backwardComplete = false;
    double speed = 0;
    int count = 0;

	double maxForwardRecorded = -100;
	double maxBackwardRecorded = 100;
	double loopForwardRecorded = 0;
	double loopBackwardRecorded = 0;

    maxAccelerationForward = 0;
    maxAccelerationBackward = 0;
    setBrakes(E_MOTOR_BRAKE_COAST);
    lcd::set_text(1, "calibrating max acceleration");

    //part 1
    while(!(forwardComplete && backwardComplete))
    {
        if (!forwardComplete)
        	{maxAccelerationForward += 0.1;}
        if (!backwardComplete)
        	{maxAccelerationBackward += 0.1;}

		loopForwardRecorded = 0;
		loopBackwardRecorded = 0;

		inertialSensor->get_pitch();
		double tempval = inertialSensor->get_accel().x;
		loopForwardRecorded = tempval;

		//drive forward
        count = 0;
        lcd::set_text(2, "max accel forwards: " + to_string(maxAccelerationForward));
        while(count < NUM_LOOPS)
        {
            speed += maxAccelerationForward;
			float pitch = inertialSensor->get_pitch();

            setMotors(speed);
            forwardComplete = (pitch > GYRO_TOLERENCE) || forwardComplete;
			double tempval = inertialSensor->get_accel().x;
			loopForwardRecorded += tempval;
            count++;

			lcd::set_text(4, "Gyro pitch: " + to_string(pitch));
			delay(LOOP_DELAY);
        }
		//stop
        while(speed > 0)
        {
            speed -= maxAccelerationBackward;
            setMotors(speed);
			float pitch = inertialSensor->get_pitch();
            backwardComplete = (pitch < -GYRO_TOLERENCE) || backwardComplete;

			double tempval = inertialSensor->get_accel().x;
			loopBackwardRecorded += tempval;

			delay(LOOP_DELAY);
			lcd::set_text(4, "Gyro pitch: " + to_string(pitch));
        }

		//drive backward
        count = 0;
        lcd::set_text(3, "max accel backwards: " + to_string(maxAccelerationBackward));
        while(count < NUM_LOOPS)
        {
            speed -= maxAccelerationBackward;
			float pitch = inertialSensor->get_pitch();
            setMotors(speed);
            backwardComplete = (pitch < -GYRO_TOLERENCE) || backwardComplete;
			double tempval = inertialSensor->get_accel().x;
			loopBackwardRecorded += tempval;
            count++;

		 	delay(LOOP_DELAY);
			lcd::set_text(4, "Gyro pitch: " + to_string(pitch));
        }
		//stop
        while(speed < 0)
        {
			float pitch = inertialSensor->get_pitch();
            speed += maxAccelerationForward;
            setMotors(speed);
            forwardComplete = (pitch > GYRO_TOLERENCE) || forwardComplete;

			double tempval = inertialSensor->get_accel().x;
			loopForwardRecorded += tempval;

			delay(LOOP_DELAY);
			lcd::set_text(4, "Gyro pitch: " + to_string(pitch));
        }

		loopForwardRecorded = loopForwardRecorded / (NUM_LOOPS*2);
		loopBackwardRecorded = loopBackwardRecorded / (NUM_LOOPS*2);

		lcd::set_text(5, "loop accel forwards: " + to_string(loopForwardRecorded));
		lcd::set_text(6, "loop accel backwards: " + to_string(loopBackwardRecorded));
		lcd::set_text(7, strerror(errno));

		if(maxForwardRecorded <= loopForwardRecorded)
			{maxForwardRecorded = loopForwardRecorded;}
		else
			{forwardComplete = true;}
		if(maxBackwardRecorded >= loopBackwardRecorded)
			{maxBackwardRecorded = loopBackwardRecorded;}
		else
			{backwardComplete = true;}
    }

	lcd::set_text(1, "max acceleration calibration finished");
}


void FourWheelDrive::calibrateMaxSpeed()
{
	const int LOOPS = 10;
	double tempInstructedSpeed = 0;
	double tempActualSpeed = 0;
	maxActualSpeed = 0;
	maxInstructedSpeed = 0;
	int count = 0;
    lcd::set_text(3, "calibrating max speed");

	while(count < LOOPS)
	{
		setMotors(tempInstructedSpeed);
		delay(LOOP_DELAY);
		tempActualSpeed = getAllSpeed();
		lcd::set_text(4, "act: " + to_string(maxActualSpeed)
		 	+ " inst: " + to_string(tempInstructedSpeed));
		lcd::set_text(7, strerror(errno));

		tempInstructedSpeed += maxAccelerationForward;
		if(tempActualSpeed > maxActualSpeed)
		{
			count = 0;
			maxActualSpeed = tempActualSpeed;
		}
		else
		{
			count++;
		}
	}

	setMotors(0);
	delay(LOOP_DELAY * 100);
	maxActualSpeed = maxActualSpeed * 0.95;
	tempActualSpeed = getAllSpeed();

	tempInstructedSpeed = 0;
	double tempActualMax = 0;

	while (tempActualSpeed < maxActualSpeed)
	{
		setMotors(tempInstructedSpeed);
		delay(LOOP_DELAY);
		tempActualSpeed = getAllSpeed();
		lcd::set_text(5, "act: " + to_string(maxActualSpeed)
		 	+ " inst: " + to_string(maxInstructedSpeed));
		lcd::set_text(7, strerror(errno));
		if(tempActualSpeed >= tempActualMax)
		{
			tempInstructedSpeed += maxAccelerationForward;
			tempActualMax = tempActualSpeed;
			maxInstructedSpeed = tempInstructedSpeed;
		}
	}

	setMotors(0);
	maxInstructedSpeed = tempActualSpeed;

	lcd::set_text(6, "calibrating max speed finished");
}

void FourWheelDrive::calibrateDrift()
{
	calibrateDriftLoop(75, LRBias);
}

void FourWheelDrive::calibrateDriftLoop(double testSpeed, double &bias)
{
	const double CHANGE_TOLERANCE = 0.005;
	int numLoops = 100;
	double rightSide = 0;
	double leftSide = 0;
	double proposedChange = 0;

	do
	{
		waitForUser("calibrate drift bias");
		bias += proposedChange;

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
		lcd::set_text(6, "anticipated bias: " + to_string(bias));

		accelerate(0);
	} while(fabs(proposedChange) > CHANGE_TOLERANCE);
	lcd::set_text(7, "calibrate drift loop complete");
}





















void FourWheelDrive::accelerate(double targetSpeed)
{
	const double TOLERANCE = 0.5;

	double currSpeed = getAllSpeed();
	if(currSpeed < targetSpeed)
	{
		while(currSpeed < targetSpeed - TOLERANCE)
		{
			currSpeed += maxAccelerationForward;
			setMotors(currSpeed);
			delay(LOOP_DELAY);
		}
	}
	else
	{
		while(currSpeed > targetSpeed + TOLERANCE)
		{
			currSpeed -= maxAccelerationBackward;
			setMotors(currSpeed);
			delay(LOOP_DELAY);
		}
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

void FourWheelDrive::checkGyro()
{
	int count = 0;
	double pitch = 0;
	lcd::set_text(5, "Starting Gyro Checks");

	lcd::set_text(6, strerror(errno));

	delay(LOOP_DELAY);
	pitch = inertialSensor->get_pitch();

	lcd::set_text(7, strerror(errno));

	while( pitch != infinity())
	{
		lcd::set_text(2, "status:" + to_string(inertialSensor->get_status()));
		lcd::set_text(3, strerror(errno));
		pitch = inertialSensor->get_pitch();
		lcd::set_text(1, "pitch: " + to_string(pitch));
		lcd::set_text(6, "num pitch sensor loops: " + to_string(count));
		lcd::set_text(4, "status:" + to_string(inertialSensor->get_status()));
		lcd::set_text(5, strerror(errno));
		delay(LOOP_DELAY);
		count++;
	}


	lcd::set_text(5, "pitch sensor loops done");
}

void FourWheelDrive::addStream(std::stringstream &gyroStream, float lastSpeed)
{
	float speed = getAllSpeed();

	gyroStream << inertialSensor->get_status()
			<< ", " << (speed - lastSpeed)
			<< ", " << speed
			<< ", " << inertialSensor->get_accel().x
			<< ", " << inertialSensor->get_accel().y
			<< ", " << inertialSensor->get_accel().z
			<< ", " << inertialSensor->get_pitch()
			<< ", " << inertialSensor->get_yaw()
			<< ", " << inertialSensor->get_gyro_rate().x
			<< ", " << inertialSensor->get_gyro_rate().y
			<< ", " << inertialSensor->get_gyro_rate().z
			<< ", " << leftMotors->front().get_current_draw()
			<< ", " << leftMotors->front().get_power()
			<< "\n";
}

void FourWheelDrive::correctGyroCalibration(float accel, float jerk)
{
	const int stationary = 100;
	const int moving = 350;
	float speed = 0;
	float intercept = 0;
	float mod = 0;
	float totalMod = 0;
	float lastSpeed = 0;

	float pitch;
	float accelMeter;
	std::stringstream gyroStream;

	//gyroStream << "Stationary, pitch, x, y, z\n";

	/*for(int i = 0; i < stationary; i++)
	{
		addStream(gyroStream);
		delay(LOOP_DELAY);
	}*/
	intercept = intercept / stationary;
	lcd::set_text(2, "intercept: " + to_string(intercept));
	lcd::set_text(0, "accel: " + to_string(accel));

	gyroStream << "status, ecode accel, speed, xAccel, yAccel, zAccel, " <<
					"pitch, yaw, gyro_x, gyro_y, gyro_z, motor current draw, motor power\n";


	for( int i = 0; i < moving; i++)
	{
		speed += accel;
		accel += jerk;
		setMotors(speed);
		delay(LOOP_DELAY);

		pitch = inertialSensor->get_pitch();
		accelMeter = inertialSensor->get_accel().x;

		addStream(gyroStream, lastSpeed);
		lastSpeed = getAllSpeed();

		mod = (-pitch - intercept) / accelMeter;
		totalMod += mod;

		lcd::set_text(3, "mod: " + to_string(pitch) + " i: " + to_string(i));

	}
	mod = totalMod / moving;
	setMotors(0);
	lcd::set_text(3, "mod: " + to_string(pitch));

	delay(1000);

	ofstream usd_file_write("/usd/slope.csv", ofstream::out);
	if(usd_file_write.is_open())
	{
		lcd::set_text(5, "file opened");
		usd_file_write << gyroStream.str();
		usd_file_write.close();
	}
	else
	{
		lcd::set_text(5, "file failed to open");
	}


	lcd::set_text(7, "finished output");
}

bool FourWheelDrive::panic()
{
    return master->get_digital(E_CONTROLLER_DIGITAL_A) || master->get_digital(E_CONTROLLER_DIGITAL_B);
}
