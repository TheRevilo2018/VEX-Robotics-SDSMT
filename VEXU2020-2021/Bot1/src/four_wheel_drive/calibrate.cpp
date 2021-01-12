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

    fileStream >> maxSpeed;
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

void FourWheelDrive::calibrateAll(pros::Controller master)
{
    int count = 0;
    lcd::set_text(3, "calling calibration");
    inertialSensor->reset();
    while(inertialSensor->is_calibrating())
    {
        lcd::set_text(7, "is calibrating   " + to_string(count));
        delay(LOOP_DELAY);
        count++;
    }
    master.set_text(0, 2, "calibrate drive");

    //calibrateMinSpeed();
    calibrateMaxAcceleration(master, 10);
    //max speed
    //calibrateDrift(master)

    //writeCalibration();
    //lcd::set_text(6, "calibration complete");
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

void FourWheelDrive::calibrateMaxAcceleration(pros::Controller master, double returnSpeed)
{
    const double GYRO_TOLERENCE = 5;
    const int NUM_LOOPS = 50;
    const int IN_BETWEEN = LOOP_DELAY * 10;
    bool forwardComplete = false;
    bool backwardComplete = false;
    double speed = 0;
    int count = 0;

    maxAccelerationForward = 0;
    maxAccelerationBackward = 0;
    setBrakes(E_MOTOR_BRAKE_COAST);
    lcd::set_text(4, "calibrating max acceleration");

    //part 1
    while(!(forwardComplete && backwardComplete))
    {
        if (!forwardComplete)
        {
            maxAccelerationForward += 0.1;
        }
        if (!backwardComplete)
        {
            maxAccelerationBackward += 0.1;
        }

        count = 0;
        lcd::set_text(5, "max accel forwards: " + to_string(maxAccelerationForward));
        while(!panic(master) && count < NUM_LOOPS)
        {
            speed += maxAccelerationForward;
            setMotors(speed);
            forwardComplete = (inertialSensor->get_pitch() > GYRO_TOLERENCE) || forwardComplete;
            delay(LOOP_DELAY);
            count++;
        }
        while(!panic(master) && speed > 0)
        {
            speed -= maxAccelerationBackward;
            setMotors(speed);
            backwardComplete = (inertialSensor->get_pitch() < -GYRO_TOLERENCE) || backwardComplete;
            delay(LOOP_DELAY);
        }

        count = 0;
        lcd::set_text(6, "max accel backwards: " + to_string(maxAccelerationBackward));
        while(!panic(master) && count < NUM_LOOPS)
        {
            speed -= maxAccelerationBackward;
            setMotors(speed);
            backwardComplete = (inertialSensor->get_pitch() < -GYRO_TOLERENCE);
            delay(LOOP_DELAY);
            count++;
        }
        while(!panic(master) && speed < 0)
        {
            speed += maxAccelerationForward;
            setMotors(speed);
            forwardComplete = (inertialSensor->get_pitch() > GYRO_TOLERENCE);
            delay(LOOP_DELAY);
        }
    }
}

void FourWheelDrive::driveTillColide(double speed)
{
    setMotors(speed);
    delay(5 * LOOP_DELAY);

    while (fabs(getAllSpeed()) > fabs(0.1 * speed))
    {
        delay(LOOP_DELAY);
    }

    setMotors(0);
}

bool FourWheelDrive::panic(pros::Controller master)
{
    return master.get_digital(E_CONTROLLER_DIGITAL_A) || master.get_digital(E_CONTROLLER_DIGITAL_B);
}
