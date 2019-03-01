#include "helperfunctions.h"

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

//call launch twice with appropriate waits and heights in order to hit the two high flags
void doubleLaunch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors)
{
  launch(launchMotors, anglerMotor, anglerPositions[1]);
  setMotors(intakeMotors, 127);
  pros::delay(600);
  setMotors(intakeMotors, 0);
  pros::delay(200);
  launch(launchMotors, anglerMotor, anglerPositions[2]);
  return;
}

//set the puncher hight to a value and rotate the slip ear 360 degrees
void launch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, int height)
{
  if(lightSensor.get_value() < 2100)
  {
    anglerMotor.move_absolute(height, 50);
    pros::delay(200);
    setMotorsRelative(launchMotors, 720, 127);
    pros::delay(500); //TODO
    return;
  }
  else
  {
    pros::delay(200);
    return;
  }
}

void setMotorsRelative(std::vector<pros::Motor> & motors, double distance, double speed)
{
  for(auto motor : motors)
  {
    motor.move_relative(distance, speed);
  }
}

void autoDriveDistance(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double distance, double speed)
{
  //TODO add check for stuck motors to prevent damage
  pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
  setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
  setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

  int initialEncoderLeft = leftWheelMotorVector[0].get_raw_position(&now);
  int initialEncoderRight = rightWheelMotorVector[0].get_raw_position(&now);
  int allowedDiff = 0;
  double diffLeft;
  double diffRight;

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

  while( abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft) < fabs(distance) || abs(rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight) < fabs(distance))
  {
    if(fabs(diffLeft - diffRight) > allowedDiff)
    {
      if(diffLeft < diffRight)
      {
        leftDriveSpeed *= .8;
      }
      else
      {
        rightDriveSpeed *= .8;
      }
    }

    diffLeft = (leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
    diffRight = (rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight);

    leftDriveSpeed = speed;
    rightDriveSpeed = speed;
    setMotors(leftWheelMotorVector, leftDriveSpeed);
    setMotors(rightWheelMotorVector, rightDriveSpeed);
    pros::delay(20);
  }
  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(50);

  setBrakes(leftWheelMotorVector,  prevBrake );
  setBrakes(rightWheelMotorVector,  prevBrake );
  return;
}
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount, double speed)
{
  double currSpeed;
  pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
  setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
  setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

  amount *= ((double)2087/360);
  int initialEncoderLeft = leftWheelMotorVector[0].get_raw_position(&now);
  int initialEncoderRight = rightWheelMotorVector[0].get_raw_position(&now);
  int diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
  int diffRight = abs(rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight);
  while(  diffLeft < fabs(amount) ||  diffRight < fabs(amount))
  {
    /*
    if(diffLeft < fabs(.25 * amount) || diffLeft > fabs(.75 * amount))
    {
      currSpeed = speed * .5;
    }

    else
    {
      */
      currSpeed = speed;
    //}
    if(amount < 0)
    {
      setMotors(leftWheelMotorVector, currSpeed);
      setMotors(rightWheelMotorVector, -currSpeed);
    }
    else
    {
      setMotors(leftWheelMotorVector, -currSpeed);
      setMotors(rightWheelMotorVector, currSpeed);
    }
    diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
    diffRight = abs(rightWheelMotorVector[0].get_raw_position(&now) - initialEncoderRight);
    pros::delay(20);
  }

  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  pros::delay(50);

  setBrakes(leftWheelMotorVector,  prevBrake );
  setBrakes(rightWheelMotorVector,  prevBrake );
  return;
}

void highScore(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, pros::Motor & liftMotor)
{
  liftMotor.move_absolute(liftPositions[1], 127);
  pros::delay(1000);
  setMotors(leftWheelMotorVector, -20);
  setMotors(rightWheelMotorVector, -20);
  pros::delay(550);
  liftMotor.move_absolute(liftPositions[2], 127);
  pros::delay(100);
  return;
}

void longDoubleLaunch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, std::vector<pros::Motor> & intakeMotors)
{
  launch(launchMotors, anglerMotor, longAnglerPositions[1]);
  setMotors(intakeMotors, 127);
  pros::delay(400);
  setMotors(intakeMotors, 0);
  pros::delay(200);
  launch(launchMotors, anglerMotor, longAnglerPositions[2]);
  return;
}
