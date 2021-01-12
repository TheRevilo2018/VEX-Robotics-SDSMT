#include "drive.h"

using namespace pros;
using namespace std;

FourWheelDrive::FourWheelDrive(vector<Motor> & right, vector<Motor> & left,
    Imu & sensor) : logger("Drivebase")
{
    vector<Motor> *rightPointer = &right;
    vector<Motor> *leftPointer = &left;
    Imu *inertialPointer = &sensor;

    rightMotors = rightPointer;
    leftMotors = leftPointer;
    inertialSensor = inertialPointer;
    numMotors = rightMotors->size();
}

FourWheelDrive::~FourWheelDrive() {}

//take in a vector of motors, and set their speed to a value
void FourWheelDrive::setMotors(vector<Motor> *motors, double speed)
{
  for(auto motor : *motors)
  {
    motor = speed;
  }
}

void FourWheelDrive::setMotors(double speed)
{
    for(auto motor : *leftMotors)
    {
      motor = speed;
    }

    for(auto motor : *rightMotors)
    {
      motor = speed;
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

void FourWheelDrive::setDirection(DIRECTION inputDirection)
{
    if (inputDirection != direction)
    {
        for(int i = 0; i < leftMotors->size(); i++)
        {
            (*leftMotors)[i].set_reversed(true);
        }

        for(int i = 0; i < rightMotors->size(); i++)
        {
            (*rightMotors)[i].set_reversed(true);
        }
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

//function used in autononomous to drive for a given distance at a given speed
void FourWheelDrive::driveDist(double target, DIRECTION direction, double maxSpeed)
{
    double speed = maxSpeed;
    double endDistance = 0;
    double startDistance = 2 * ROTATION_MUL;
    double currDist = 0;
    double deccelDist = 2 * ROTATION_MUL;
    double averagePos = 0;
    double distPercent = 0;
    int stopCount = 0;

    auto previous_brake = (*leftMotors)[0].get_brake_mode();
    setBrakes(pros::E_MOTOR_BRAKE_HOLD);
    inertialSensor->reset();


    setDirection(direction);
    target *= ROTATION_MUL;
    deccelDist = distReq(maxSpeed, direction);
    startDistance = distReq(maxSpeed, direction);
    endDistance = target - deccelDist;

    if ( startDistance + deccelDist > target)
    {
        distPercent = target / (startDistance + deccelDist);
        maxSpeed *= distPercent;
        startDistance *= distPercent;
        endDistance *= distPercent;
    }

    setZeroPosition();

    if (maxSpeed > 10)
    {
        while (averagePos < startDistance && stopCount < STOP_AMOUNT)
        {
            averagePos = (rightMotors->front().get_position() + rightMotors->front().get_position() +
                    leftMotors->back().get_position() + leftMotors->back().get_position()) / 4;
                    speed = maxSpeed * (averagePos / startDistance) + 14;

            if(speed < 20)
                speed = 20;
            if (speed > maxSpeed)
            {
                speed = maxSpeed;
            }

            correctDist(leftMotors, rightMotors, averagePos, speed, direction);
            pros::delay(LOOP_DELAY);
            if (leftMotors->front().get_actual_velocity() <= 5)
                stopCount++;
        }

        while (averagePos < endDistance && stopCount < STOP_AMOUNT)
        {
            averagePos = (leftMotors->front().get_position() + rightMotors->front().get_position() +
            leftMotors->back().get_position() + leftMotors->back().get_position()) / 4;

            correctDist(leftMotors, rightMotors, averagePos, speed, direction);

            pros::delay(LOOP_DELAY);
            if (leftMotors->front().get_actual_velocity() <= 5)
                stopCount++;
        }

        endDistance = target - averagePos;
        while (averagePos < target && stopCount < STOP_AMOUNT)
        {
            averagePos = (leftMotors->front().get_position() + rightMotors->front().get_position() +
            leftMotors->back().get_position() + leftMotors->back().get_position()) / 4;
            currDist = target - averagePos;
            speed = maxSpeed * (currDist / endDistance) + 14;
            if(speed < 20)
                speed = 20;
            if (speed > maxSpeed)
            {
               speed = maxSpeed;
            }

            correctDist(leftMotors, rightMotors, averagePos, speed, direction);
            pros::delay(LOOP_DELAY);
            if (leftMotors->front().get_actual_velocity() <= 5)
                stopCount++;
        }
    }
    else
    {
        speed = 10;

        while (averagePos < endDistance && stopCount < STOP_AMOUNT)
        {
            averagePos = (leftMotors->front().get_position() + rightMotors->front().get_position() +
            leftMotors->back().get_position() + leftMotors->back().get_position()) / 4;

            correctDist(leftMotors, rightMotors, averagePos, speed, direction);

            pros::delay(LOOP_DELAY);
            if (leftMotors->front().get_actual_velocity() <= 5)
                stopCount++;
        }
    }
    //displayPosition();

    setMotors(0);
    setDirection(FORWARD);
    pros::delay(150);
    setBrakes(previous_brake);
}

//a function that finds the best speed based on the distance of the wheels
void FourWheelDrive::correctDist (std::vector<pros::Motor> *leftMotors, std::vector<pros::Motor> *rightMotors,
    double target, double speed, DIRECTION direction)
{
    double leftValue = 0;
    double rightValue = 0;
    for(int i = 0; i < leftMotors->size(); i++)
    {
      leftValue += (*leftMotors)[i].get_position();
      rightValue += (*rightMotors)[i].get_position();
    }
    leftValue /= leftMotors->size();
    leftValue -= target;

    rightValue /= rightMotors->size();
    rightValue -= target;

    double leftSpeed = speed;
    double rightSpeed = speed;

    if ( rightValue > 2)
    {
        leftSpeed *= 0.96;
    }
    else if (rightValue < -2)
    {
        leftSpeed *= 1.04;
    }


    if ( rightValue > 2)
    {
        rightSpeed *= 0.96;
    }
    else if (rightValue < -2)
    {
        rightSpeed *= 1.04;
    }

    /*if(direction == FORWARD)
    {
        if(gyroVal < -10)
        {
            rightSpeed *= 0.92;
        }
        else if(gyroVal > 10)
        {
            leftSpeed *= 0.92;
        }
    }
    else
    {
        if(gyroVal < -10)
        {
            leftSpeed *= 1.15;
        }
        else if(gyroVal > 10)
        {
            rightSpeed *= 1.15;
        }
    }*/

    setMotors(leftMotors, leftSpeed);
    setMotors(rightMotors, rightSpeed);

}

double FourWheelDrive::distReq(double speed, DIRECTION direction)
{
    double result = 1.0 * ROTATION_MUL;

    if (direction == BACKWARD)
    {
        result = 1.8 * ROTATION_MUL;
    }

    return result;
}

//function used in autonomous to turn a given degree amount at a given speed
void FourWheelDrive::autoTurnRelative(std::vector<pros::Motor> *leftWheelMotorVector,
    std::vector<pros::Motor> *rightWheelMotorVector, double amount)
{
  double currSpeed;
  double speed = 80;

  pros::motor_brake_mode_e_t prevBrake = (*leftWheelMotorVector)[0].get_brake_mode();
  setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
  setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

  amount *= 10;
  //gyro.reset();
  pros::delay(100);

  float lastRemainingTicks = 99999;
  float remainingTicks = amount;
  //white both not close to target and not overshooting
  while( fabs(remainingTicks) >= 5 && fabs(remainingTicks) - fabs(lastRemainingTicks) <= 1)
  {
    double multiplier = fmax(fmin(1, fabs(remainingTicks / 1250.0)), .25);
    currSpeed = speed;
    currSpeed *= multiplier;

    if (currSpeed < 30)
        currSpeed = 30;

    if(remainingTicks < 0)
    {
      setMotors(leftWheelMotorVector, -currSpeed);
      setMotors(rightWheelMotorVector, currSpeed);
    }
    else
    {
      setMotors(leftWheelMotorVector, currSpeed);
      setMotors(rightWheelMotorVector, -currSpeed);
    }

  	//if(master.get_digital(KILL_BUTTON))
    //{
    //  break;
    //}
    pros::delay(LOOP_DELAY);
    //lastRemainingTicks = remainingTicks;
    //remainingTicks = amount - gyro.get_value();
    lcd::set_text(5, "gyro: " + to_string(remainingTicks));
    pros::lcd::set_text(6, "gyro: " + to_string(lastRemainingTicks) + " " + to_string(fabs(remainingTicks) <= fabs(lastRemainingTicks)));
  }

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(50);

  setBrakes(leftWheelMotorVector, prevBrake );
  setBrakes(rightWheelMotorVector, prevBrake );

  return;
}

double FourWheelDrive::getAllSpeed()
{
    double averageSpeed = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averageSpeed += leftMotors->at(i).get_actual_velocity();
        averageSpeed += rightMotors->at(i).get_actual_velocity();
    }

    return averageSpeed / (numMotors * 2);
}
