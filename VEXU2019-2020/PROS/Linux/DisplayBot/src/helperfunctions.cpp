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

//tqke in a vector of motors, and call the move relative function for all of them with a given distance and speed
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
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount)
{
  double currSpeed;
  double speed = 80;
  pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
  setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
  setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

  amount *= 10;
  gyro.reset();

  float lastRemainingTicks = 99999;
  float remainingTicks = amount;
  //white both not close to target and not overshooting
  while( fabs(remainingTicks) >= 5 && fabs(remainingTicks) - fabs(lastRemainingTicks) <= 1)
  {
    double multiplier = fmax(fmin(1, fabs(remainingTicks / 1250.0)), .25);
    currSpeed = speed;
    currSpeed *= multiplier;

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

  	if(master.get_digital(KILL_BUTTON))
    {
      break;
    }
    pros::delay(20);
    lastRemainingTicks = remainingTicks;
    remainingTicks = amount - gyro.get_value();
    pros::lcd::set_text(5, "gyro: " + std::to_string(remainingTicks));
    pros::lcd::set_text(6, "gyro: " + std::to_string(lastRemainingTicks) + " " + std::to_string(fabs(remainingTicks) <= fabs(lastRemainingTicks)));
  }

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(50);

  setBrakes(leftWheelMotorVector, prevBrake );
  setBrakes(rightWheelMotorVector, prevBrake );

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

void depositStack()
{
  //constant slow intake
  setMotors(intakeMotors, -20);

  //forward to align
  setMotors(leftWheelMotorVector, 30);
  setMotors(rightWheelMotorVector, 30);
  pros::delay(200);

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(100);

  //slight back
  setMotors(leftWheelMotorVector, -30);
  setMotors(rightWheelMotorVector, -30);
  pros::delay(200);

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(100);

  setMotors(intakeMotors, 0);

  //tip up tray
  trayLeft.move_absolute(TRAY_MIDDLE_HEIGHT, 60);
  trayRight.move_absolute(TRAY_MIDDLE_HEIGHT, 60);
  while(trayLeft.get_target_position() - trayLeft.get_position() > 0 && trayRight.get_target_position() - trayRight.get_position() > 0)
  {
    if(master.get_digital(KILL_BUTTON))
    {
      break;
    }
    pros::delay(20);
  }
  pros::delay(300);

  //slight constant forward
  setMotors(leftWheelMotorVector, 30);
  setMotors(rightWheelMotorVector, 30);
  pros::delay(250);

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(100);

  //finish tip
  trayLeft.move_absolute(TRAY_MAX_HEIGHT, 40);
  trayRight.move_absolute(TRAY_MAX_HEIGHT, 40);
  while(trayLeft.get_target_position() - trayLeft.get_position() > 0 && trayRight.get_target_position() - trayRight.get_position() > 0)
  {
    if(master.get_digital(KILL_BUTTON))
    {
      break;
    }
    pros::delay(20);
  }

  //slight outtake
  setMotors(intakeMotors, -60);

  //smooth medium speed back
  setMotors(leftWheelMotorVector, -50);
  setMotors(rightWheelMotorVector, -50);
  pros::delay(400);

  setMotors(intakeMotors, 0);

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(100);
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
