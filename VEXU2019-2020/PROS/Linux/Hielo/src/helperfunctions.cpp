#include "helperfunctions.h"
#include <algorithm>

//take in a vecor of motors, and set their speed to a value
void setMotors(std::vector<pros::Motor> & motors, double speed)
{
  for(auto motor : motors)
  {
    motor = speed;
  }
}

//take in a vector of motors, and set their brake type to a given type
void setBrakes(std::vector<pros::Motor> & motors,  pros::motor_brake_mode_e_t brakeType)
{
  for(auto motor: motors)
  {
    motor.set_brake_mode(brakeType);
  }
}

//tqke in a vector of motors, and call the move relative function for all of them with a given distnce and speed
void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed)
{
  for(auto motor : motors)
  {
    motor.move_relative(distance, speed);
  }
}

//function used in autononomous to drive for a given distance at a given speed
void autoDriveDistance(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double distance, double speed)
{
  //TODO add check for stuck motors to prevent damage
  pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
  setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
  setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

  int initialEncoderLeft = leftWheelMotorVector[0].get_raw_position(&now);
  int initialEncoderRight = rightWheelMotorVector[0].get_raw_position(&now);
  int allowedDiff = 0;
  int maxTime = std::max(1000, int(2 * std::fabs(distance)));
  int currTime = 0;
  int gyroVal = 0;
  double diffLeft;
  double diffRight;

  gyro.reset();

  if(distance < 0)
  {
    speed *= -1;
  }
  double leftDriveSpeed = speed;
  double rightDriveSpeed = speed;
  diffLeft = (leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
  diffRight = (rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight);

  setMotors(leftWheelMotorVector, speed);
  setMotors(rightWheelMotorVector, speed);

  while( currTime < maxTime &&
    (abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft) < fabs(distance) ||
    abs(rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight) < fabs(distance)))
  {
    gyroVal = gyro.get_value();

    diffLeft = (leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
    diffRight = (rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight);

    leftDriveSpeed = speed;
    rightDriveSpeed = speed;

    if(abs(gyroVal) > 5)
    {
      if(gyroVal > 0)
      {
        if(distance > 0)
          leftDriveSpeed *= .95;
        else
          rightDriveSpeed *= .95;
      }
      else
      {
        if(distance > 0)
          rightDriveSpeed *= .95;
        else
          leftDriveSpeed *= .95;
      }
    }

    setMotors(leftWheelMotorVector, leftDriveSpeed);
    setMotors(rightWheelMotorVector, rightDriveSpeed);
    currTime += 20;
    pros::delay(20);
  }
  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(50);

  setBrakes(leftWheelMotorVector,  prevBrake );
  setBrakes(rightWheelMotorVector,  prevBrake );
  return;
}

//function used in autonomous to turn a given degree amount at a given speed
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount, double speed)
{
  double currSpeed;
  pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
  setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
  setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

  amount *= 10;
  gyro.reset();

  float remainingTicks = amount - gyro.get_value();
  while( fabs(remainingTicks) >= 10 )
  {
    double multiplier = fmin(1, fabs(remainingTicks / 1000.0));
    currSpeed = speed;
    currSpeed *= multiplier;

    if(remainingTicks < 0)
    {
      setMotors(leftWheelMotorVector, currSpeed);
      setMotors(rightWheelMotorVector, -currSpeed);
    }
    else
    {
      setMotors(leftWheelMotorVector, -currSpeed);
      setMotors(rightWheelMotorVector, currSpeed);
    }
    pros::delay(20);
  }

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(50);

  setBrakes(leftWheelMotorVector,  prevBrake );
  setBrakes(rightWheelMotorVector,  prevBrake );

  remainingTicks = amount - gyro.get_value();
  return;
}

//turn right while adjusting speed based on distance from goal
void autoTurnRight(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount)
{
    //translation factor
    pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
    setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
    setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

    int initialEncoderLeft = leftWheelMotorVector[0].get_raw_position(&now);
    int initialEncoderRight = rightWheelMotorVector[3].get_raw_position(&now);

    double leftDriveSpeed;
    double rightDriveSpeed;

    amount = fabs(amount);

    double diffLeft, diffRight;

    diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
    diffRight = abs(rightWheelMotorVector[3].get_raw_position(&now) - initialEncoderRight);

    while( diffLeft < amount)
    {
        if(amount - diffLeft < (amount * 2 )/ 32 || amount - diffLeft > (amount * 30 )/ 32)
        {
            leftDriveSpeed = 30;
            rightDriveSpeed = 30;
        }
        else if(amount - diffLeft < (amount * 4 )/ 32 || amount - diffLeft > (amount * 28 )/ 32)
        {
            leftDriveSpeed = 30;
            rightDriveSpeed = 30;
        }
        else if(amount - diffLeft < (amount * 6 )/ 32 || amount - diffLeft > (amount * 26 )/ 32)
        {
            leftDriveSpeed = 40;
            rightDriveSpeed = 40;
        }
        else
        {
            leftDriveSpeed = 50;
            rightDriveSpeed = 50;
        }
        leftDriveSpeed /= 1.25;
        rightDriveSpeed /= 1.25;
        setMotors(leftWheelMotorVector, leftDriveSpeed);
        setMotors(rightWheelMotorVector, -rightDriveSpeed);
        diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
        diffRight = abs(rightWheelMotorVector[3].get_raw_position(&now) - initialEncoderRight);
        pros::delay(20);

    }
    setBrakes(leftWheelMotorVector, pros::E_MOTOR_BRAKE_BRAKE);
    setBrakes(rightWheelMotorVector, pros::E_MOTOR_BRAKE_BRAKE);
    setMotors(leftWheelMotorVector, 0);
    setMotors(rightWheelMotorVector, 0);
    pros::delay(200);
    setBrakes(leftWheelMotorVector, prevBrake);
    setBrakes(rightWheelMotorVector, prevBrake);
}


void autoTurnLeft(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount)
{
    pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
    setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
    setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

    int initialEncoderLeft = leftWheelMotorVector[0].get_raw_position(&now);
    int initialEncoderRight = rightWheelMotorVector[3].get_raw_position(&now);

    double leftDriveSpeed;
    double rightDriveSpeed;

    amount = fabs(amount);

    double diffLeft, diffRight;

    diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
    diffRight = abs(rightWheelMotorVector[3].get_raw_position(&now) - initialEncoderRight);

    while( diffRight < amount)
    {
        if(amount - diffRight < (amount * 2 )/ 32 || amount - diffRight > (amount * 30 )/ 32)
        {
            leftDriveSpeed = 30;
            rightDriveSpeed = 30;
        }
        else if(amount - diffRight < (amount * 4 )/ 32 || amount - diffRight > (amount * 28 )/ 32)
        {
            leftDriveSpeed = 30;
            rightDriveSpeed = 30;
        }
        else if(amount - diffRight < (amount * 6 )/ 32 || amount - diffRight > (amount * 26 )/ 32)
        {
            leftDriveSpeed = 40;
            rightDriveSpeed = 40;
        }
        else
        {
            leftDriveSpeed = 50;
            rightDriveSpeed = 50;
        }

        leftDriveSpeed /= 1.25;
        rightDriveSpeed /= 1.25;
        setMotors(leftWheelMotorVector, -leftDriveSpeed);
        setMotors(rightWheelMotorVector, rightDriveSpeed);
        diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
        diffRight = abs(rightWheelMotorVector[3].get_raw_position(&now) - initialEncoderRight);
        pros::delay(20);

    }
    setBrakes(leftWheelMotorVector, pros::E_MOTOR_BRAKE_BRAKE);
    setBrakes(rightWheelMotorVector, pros::E_MOTOR_BRAKE_BRAKE);
    setMotors(leftWheelMotorVector, 0);
    setMotors(rightWheelMotorVector, 0);
    pros::delay(200);
    setBrakes(leftWheelMotorVector, prevBrake);
    setBrakes(rightWheelMotorVector, prevBrake);
}

bool pressButton(std::uint32_t  & debounceTime)
{
	std::uint32_t pressTime = pros::millis();
	if(pressTime - debounceTime >= DEBOUNCE_DELAY)
	{
		debounceTime = pressTime;
		return true;
	}
	return false;
}
