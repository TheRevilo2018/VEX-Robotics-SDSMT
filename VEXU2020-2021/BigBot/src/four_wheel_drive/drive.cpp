#include "drive.h"

using namespace pros;
using namespace std;

FourWheelDrive::FourWheelDrive(vector<Motor> & right, vector<Motor> & left,
    Imu & sensor, Controller & masterIn) : logger("Drivebase")
{
    vector<Motor> *rightPointer = &right;
    vector<Motor> *leftPointer = &left;
    Imu *inertialPointer = &sensor;
    Controller *controllerPointer = &masterIn;

    rightMotors = rightPointer;
    leftMotors = leftPointer;
    inertialSensor = inertialPointer;
    master = controllerPointer;
    numMotors = rightMotors->size();
}

//take in a vector of motors, and set their speed to a value
void FourWheelDrive::setMotors(vector<Motor> *motors, double speed)
{
  for(auto motor : *motors)
  {
    motor = speed;
  }
}

void FourWheelDrive::rawSetMotors(double speed, double bias)
{
    if (bias > 1)
    {
        speed *= (1 / bias);
    }


    for(auto motor : *leftMotors)
    {
      motor = speed;
    }
    for(auto motor : *rightMotors)
    {
      motor = speed * bias;
    }
}

void FourWheelDrive::setMotors(double speed)
{
    //speed capping
    if (speed > maxSpeed)
    {
        speed = maxSpeed;
        rawSetMotors(speed, LRBiasHigh);
        lcd::set_text(0, "speed > maxSpeed: " + to_string(speed) + " bias: " + to_string(LRBiasHigh));
    }
    else if(speed > midSpeed)
    {
        double highPercent = (speed - midSpeed) / (maxSpeed - midSpeed);
        double lowPercent = (maxSpeed - speed) / (maxSpeed - midSpeed);

        rawSetMotors(speed, LRBiasLow * lowPercent + LRBiasHigh * highPercent);
        lcd::set_text(0, "speed > midSpeed: " + to_string(speed) + " bias: "
                + to_string(LRBiasLow * lowPercent + LRBiasHigh * highPercent));
    }
    else if (speed >= 0)
    {
        rawSetMotors(speed, LRBiasLow);
        lcd::set_text(0, "speed > 0: " + to_string(speed) + " bias: " + to_string(LRBiasLow));
    }
    //backwards biases
    else if (speed < -maxSpeed)
    {
        speed = -maxSpeed;
        rawSetMotors(speed, LRBiasHighBack);
        lcd::set_text(0, "speed < -maxSpeed: " + to_string(speed) + " bias: " + to_string(LRBiasHighBack));
    }
    else if (speed < -midSpeed)
    {
        double highPercent = (-speed - midSpeed) / (maxSpeed - midSpeed);
        double lowPercent = (maxSpeed + speed) / (maxSpeed - midSpeed);

        rawSetMotors(speed, LRBiasLowBack * lowPercent + LRBiasHighBack * highPercent);
        lcd::set_text(0, "speed < -midSpeed: " + to_string(speed) + " bias: "
                + to_string(LRBiasLow * lowPercent + LRBiasHigh * highPercent));
    }
    else //if (speed < 0)
    {
        rawSetMotors(speed, LRBiasLowBack);
        lcd::set_text(0, "speed < 0: " + to_string(speed) + " bias: " + to_string(LRBiasLowBack));
    }
}

//take in a vector of motors, and set their brake type to a given type
void FourWheelDrive::setBrakes(vector<Motor> *motors,  motor_brake_mode_e_t brakeType)
{
  for(auto motor: *motors)
  {
    motor.set_brake_mode(brakeType);
  }
}

void FourWheelDrive::setBrakes(motor_brake_mode_e_t brakeType)
{
  for(auto motor: *leftMotors)
  {
    motor.set_brake_mode(brakeType);
  }

  for(auto motor: *rightMotors)
  {
    motor.set_brake_mode(brakeType);
  }
}

//tqke in a vector of motors, and call the move relative function for all of them with a given distance and speed
void FourWheelDrive::setMotorsRelative(vector<Motor> * motors, double distance, double speed)
{
  for(auto motor : *motors)
  {
    motor.move_relative(distance, speed);
  }
}

void FourWheelDrive::setMotorsRelative(double distance, double speed)
{
  for(auto motor : *leftMotors)
  {
    motor.move_relative(distance, speed);
  }

  for(auto motor : *rightMotors)
  {
    motor.move_relative(distance, speed);
  }
}

void FourWheelDrive::setZeroPosition(vector<Motor> * motors)
{
    for (int i = 0; i < motors->size(); i++) //sets the motors to 0
    {
        (*motors)[i].set_zero_position(0);
    }
}

void FourWheelDrive::setZeroPosition()
{
    for (int i = 0; i < leftMotors->size(); i++) //sets the motors to 0
    {
        (*leftMotors)[i].set_zero_position(0);
    }

    for (int i = 0; i < rightMotors->size(); i++) //sets the motors to 0
    {
        (*rightMotors)[i].set_zero_position(0);
    }
}

double FourWheelDrive::getPosition(vector<Motor> * motors)
{
    double averagePosition = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averagePosition += motors->at(i).get_position();
    }

    return averagePosition / (motors->size());
}

double FourWheelDrive::getAllPosition()
{
    double averagePosition = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averagePosition += leftMotors->at(i).get_position();
        averagePosition += rightMotors->at(i).get_position();
    }

    return averagePosition / (numMotors * 2);
}

double FourWheelDrive::rawGetAllSpeed(double bias)
{
    double averageSpeed = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averageSpeed += leftMotors->at(i).get_actual_velocity();
        averageSpeed += rightMotors->at(i).get_actual_velocity();
    }

    return (averageSpeed / (numMotors * 2)) * bias;
}

double FourWheelDrive::getAllSpeed()
{
    return rawGetAllSpeed(speedBias);
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
