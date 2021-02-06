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
    fileStream >> LRHandicap;
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

void FourWheelDrive::calibrateAll(pros::Controller & master)
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
    master.set_text(0, 2, "calibrated drive ");
		lcd::set_text(2, "status:" + to_string(inertialSensor->get_status()));
		lcd::set_text(3,  strerror(errno));

 		checkGyro();

    //calibrateMinSpeed();
    //calibrateMaxAcceleration(master, 10);
	maxAccelerationForward = 5; //remove once actual is found
    //calibrateMaxSpeed();
    //calibrateDrift(master)

    //writeCalibration();
    //lcd::set_text(6, "calibration complete");
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

void FourWheelDrive::calibrateMaxSpeed()
{
	const int LOOPS = 10;
	double tempInstructedSpeed = 0;
	double tempActualSpeed = 0;
	maxActualSpeed = 0;
	maxInstructedSpeed = 0;
	int count = 0;
    lcd::set_text(4, "calibrating max speed");

	while(count < LOOPS)
	{
		setMotors(tempInstructedSpeed);
		delay(LOOP_DELAY);
		tempActualSpeed = getAllSpeed();
		lcd::set_text(5, "act: " + to_string(maxActualSpeed)
		 	+ " inst: " + to_string(tempInstructedSpeed));
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
		lcd::set_text(6, "act: " + to_string(maxActualSpeed)
		 	+ " inst: " + to_string(maxInstructedSpeed));
		if(tempActualSpeed >= tempActualMax)
		{
			tempInstructedSpeed += maxAccelerationForward;
			tempActualMax = tempActualSpeed;
			maxInstructedSpeed = tempInstructedSpeed;
		}
	}

	setMotors(0);
	maxInstructedSpeed = tempActualSpeed;

	lcd::set_text(7, "calibrating max speed finished");
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
        delay(LOOP_DELAY);
    }

    minSpeed = speed;
    setMotors(0);
}

void FourWheelDrive::calibrateMaxAcceleration(pros::Controller & master, double returnSpeed)
{
    const double GYRO_TOLERENCE = 8;
    const int NUM_LOOPS = 30;
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
    lcd::set_text(4, "calibrating max acceleration");

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
		lcd::set_text(1, strerror(errno));

		//drive forward
        count = 0;
        lcd::set_text(5, "max accel forwards: " + to_string(maxAccelerationForward));
        while(!panic(master) && count < NUM_LOOPS)
        {
            speed += maxAccelerationForward;
            setMotors(speed);
            forwardComplete = (inertialSensor->get_pitch() > GYRO_TOLERENCE) || forwardComplete;
            delay(LOOP_DELAY);
			double tempval = inertialSensor->get_accel().x;
			loopForwardRecorded += tempval;
            count++;
        }
		lcd::set_text(2, strerror(errno));
		//stop
        while(!panic(master) && speed > 0)
        {
            speed -= maxAccelerationBackward;
            setMotors(speed);
            backwardComplete = (inertialSensor->get_pitch() < -GYRO_TOLERENCE) || backwardComplete;
            delay(LOOP_DELAY);
			double tempval = inertialSensor->get_accel().x;
			loopBackwardRecorded += tempval;
        }

		//drive backward
        count = 0;
        lcd::set_text(6, "max accel backwards: " + to_string(maxAccelerationBackward));
        while(!panic(master) && count < NUM_LOOPS)
        {
            speed -= maxAccelerationBackward;
            setMotors(speed);
            backwardComplete = (inertialSensor->get_pitch() < -GYRO_TOLERENCE) || backwardComplete;
            delay(LOOP_DELAY);
			double tempval = inertialSensor->get_accel().x;
			loopBackwardRecorded += tempval;
            count++;
        }
		//stop
        while(!panic(master) && speed < 0)
        {
            speed += maxAccelerationForward;
            setMotors(speed);
            forwardComplete = (inertialSensor->get_pitch() > GYRO_TOLERENCE) || forwardComplete;
            delay(LOOP_DELAY);
			double tempval = inertialSensor->get_accel().x;
			loopForwardRecorded += tempval;
        }

		loopForwardRecorded = loopForwardRecorded / (NUM_LOOPS*2);
		loopBackwardRecorded = loopBackwardRecorded / (NUM_LOOPS*2);

		lcd::set_text(3, "loop accel forwards: " + to_string(loopForwardRecorded));
		lcd::set_text(4, "loop accel backwards: " + to_string(loopBackwardRecorded));

		if(maxForwardRecorded <= loopForwardRecorded)
			{maxForwardRecorded = loopForwardRecorded;}
		else
			{forwardComplete = true;}
		if(maxBackwardRecorded >= loopBackwardRecorded)
			{maxBackwardRecorded = loopBackwardRecorded;}
		else
			{backwardComplete = true;}
    }
}











void FourWheelDrive::driveTillCollide(double speed)
{
    setMotors(speed);
    delay(5 * LOOP_DELAY);

    while (fabs(getAllSpeed()) > fabs(0.1 * speed))
    {
        delay(LOOP_DELAY);
    }

    setMotors(0);
}

bool FourWheelDrive::panic(pros::Controller & master)
{
    return master.get_digital(E_CONTROLLER_DIGITAL_A) || master.get_digital(E_CONTROLLER_DIGITAL_B);
}
