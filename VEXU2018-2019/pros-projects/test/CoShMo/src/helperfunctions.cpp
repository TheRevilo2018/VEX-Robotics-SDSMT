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
  launch(launchMotors, anglerMotor, anglerPositions[1], true);
  pros::delay(300);
  launch(launchMotors, anglerMotor, anglerPositions[2], true);
  pros::delay(200);
  return;
}

//set the puncher hight to a value and rotate the slip ear 360 degrees
void launch(std::vector<pros::Motor> & launchMotors, pros::Motor & anglerMotor, int height, bool fast)
{
  //2900
  if(fast || lightSensor.get_value() < NO_BALL_LIGHT_VALUE)
  {
    anglerMotor.move_absolute(height, 50);
    pros::delay(200);
    setMotorsRelative(launchMotors, 727, 127);
    pros::delay(500);
    return;
  }
  else
  {
    pros::delay(200);
    return;
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

//function used in autonomous to turn a given degree amount at a given speed
void autoTurnRelative(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, double amount, double speed)
{
  //TODO add checks for getting stuck to prevent damage
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
    currSpeed = speed;
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

//adds a cap to a post when aligned properly
void highScore(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector,  std::vector<pros::Motor> & liftMotors, bool & actuatorState)
{
  drive(leftWheelMotorVector, rightWheelMotorVector, -100);
  pros::delay(200);
  liftMotors[0].move_absolute(liftPositions[3], 127);
  liftMotors[1].move_absolute(liftPositions[3], 127);
  pros::delay(980);
  actuator.set_value(false);
  pros::delay(220);
  setMotors(leftWheelMotorVector, -40);
  setMotors(rightWheelMotorVector, -40);
  pros::delay(700);
  setMotors(leftWheelMotorVector, 0);
  setMotors(rightWheelMotorVector, 0);
  actuatorState = false;
  return;
}

//drive for autonomous
void drive(std::vector<pros::Motor> & leftWheelMotorVector, std::vector<pros::Motor> & rightWheelMotorVector, int distance)
{
    pros::motor_brake_mode_e_t prevBrake = leftWheelMotorVector[0].get_brake_mode();
    setBrakes(leftWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );
    setBrakes(rightWheelMotorVector,  pros::E_MOTOR_BRAKE_BRAKE );

    int initialEncoderLeft = leftWheelMotorVector[0].get_raw_position(&now);
    int initialEncoderRight = rightWheelMotorVector[3].get_raw_position(&now);
    int currTime = 0;
    int maxTime = std::min(1000, 2 * distance);
    double leftDriveSpeed;
    double rightDriveSpeed;

    bool forward = distance > 0;
    distance = abs(distance);

    double diffLeft, diffRight;

    diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
    diffRight = abs(rightWheelMotorVector[3].get_raw_position(&now) - initialEncoderRight);

    while(diffLeft < distance && currTime < maxTime)
    {
        if(distance - diffLeft < (distance * 2 )/ 32 || distance - diffLeft > (distance * 30 )/ 32)
        {
            leftDriveSpeed = 40;
            rightDriveSpeed = 40;
        }
        else if(distance - diffLeft < (distance * 4 )/ 32 || distance - diffLeft > (distance * 28 )/ 32)
        {
            leftDriveSpeed = 60;
            rightDriveSpeed = 60;
        }
        else if(distance - diffLeft < (distance * 6 )/ 32 || distance - diffLeft > (distance * 26 )/ 32)
        {
          leftDriveSpeed = 60;
          rightDriveSpeed = 60;
        }
        else if(distance - diffLeft < (distance * 8 )/ 32 || distance - diffLeft > (distance * 24 )/ 32)
        {
          leftDriveSpeed = 80;
          rightDriveSpeed = 80;
        }
        else
        {
          leftDriveSpeed = 100;
          rightDriveSpeed = 100;
        }

        if(distance <= 1000)
        {
            leftDriveSpeed /= 2;
            rightDriveSpeed /= 2;
        }
        else if(distance <= 500)
        {
            leftDriveSpeed /= 4;
            rightDriveSpeed /= 4;
        }

        leftDriveSpeed /= 2;
        rightDriveSpeed /= 2;
        if(!forward)
        {
          leftDriveSpeed *= -1;
          rightDriveSpeed *= -1;
        }
        setMotors(leftWheelMotorVector, leftDriveSpeed);
        setMotors(rightWheelMotorVector, rightDriveSpeed);
        diffLeft = abs(leftWheelMotorVector[0].get_raw_position(&now) - initialEncoderLeft);
        diffRight = abs(rightWheelMotorVector[3].get_raw_position(&now) - initialEncoderRight);
        currTime += 20;
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
            leftDriveSpeed = 20;
            rightDriveSpeed = 20;
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
            leftDriveSpeed = 20;
            rightDriveSpeed = 20;
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
