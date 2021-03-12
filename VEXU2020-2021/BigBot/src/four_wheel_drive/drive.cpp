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

void FourWheelDrive::driveTilesPID(float numTiles, float desiredSpeed)
{
  float INTEGRATOR_MAX_MAGNITUDE = 100;
  float DELTA_T = LOOP_DELAY / 1000.0;
  float currentDistance = 0;

  float kP = 1;
  float kI = .5;
  float kD = .005;

  float porportionalAmount = 0;
  float integralAmount = 0;
  float derivativeAmount = 0;

  long iterations = 1;
  float lastDistance = 0;
  float accumulatedDistance = 0;

  float lastEncoderVal = leftMotors->at(0).get_position();
  float runTime = 0;
  while (abs(numTiles - currentDistance) > 0.1 &&
     runTime < ONE_SEC_IN_MS * numTiles)
  {
    porportionalAmount = numTiles - currentDistance;

    accumulatedDistance += porportionalAmount;
    accumulatedDistance = bindToMagnitude(accumulatedDistance, INTEGRATOR_MAX_MAGNITUDE); 

    integralAmount = accumulatedDistance * DELTA_T;

    derivativeAmount = (lastDistance - currentDistance) / DELTA_T;

    float total = porportionalAmount * kP + integralAmount * kI + derivativeAmount * kD;
    total = bindToMagnitude(total, 1);

    float speed = total * desiredSpeed;

    float currentEncoderVal = leftMotors->at(0).get_position();

    currentDistance += (currentEncoderVal - lastEncoderVal) / 1000.0;


    lcd::set_text(3, "Desired " + to_string(numTiles));
    lcd::set_text(4, "Current: " + to_string(currentDistance));
    lcd::set_text(5, "Raw Vals: " + to_string(porportionalAmount) + " " + to_string(integralAmount) + " " + to_string(derivativeAmount));
    lcd::set_text(6, "New Vals: " + to_string(porportionalAmount * kP) + " " + to_string(integralAmount * kI) + " " + to_string(derivativeAmount * kD));
    lcd::set_text(7, to_string(lastDistance) + " " + to_string(currentDistance));

    setMotors(rightMotors, speed);
    setMotors(leftMotors, speed);

    iterations++;
    lastDistance = porportionalAmount;
    lastEncoderVal = currentEncoderVal;
    runTime += LOOP_DELAY;
    pros::delay(LOOP_DELAY);
  }
}

void FourWheelDrive::turnDegreesPID(float numDegrees, float desiredSpeed)
{
  lcd::set_text(1, "turnDegrees: " + to_string(numDegrees) + " " + to_string(desiredSpeed));

  float INTEGRATOR_MAX_MAGNITUDE = 100;
  float DELTA_T = LOOP_DELAY / 1000.0;
  float startingDegrees = degreeBoundingHelper(inertialSensor->get_heading());
  float endingDegrees = degreeBoundingHelper(startingDegrees + numDegrees);
  float currentDegrees = degreeBoundingHelper(inertialSensor->get_heading());

  lcd::set_text(2, "turnDegrees: " + to_string(currentDegrees) + " " + to_string(endingDegrees));

  float kP = 1 / 90.0;
  float kI = .1 / 90.0;
  float kD = .02 / 90.0;

  float porportionalAmount = 0;
  float integralAmount = 0;
  float derivativeAmount = 0;
  float accumulatedDegrees = 0;

  float lastDegrees = 0;
  float runTime = 0;
  while( abs(degreeBoundingHelper(currentDegrees) - degreeBoundingHelper(endingDegrees)) >= 2 
    && runTime < ONE_SEC_IN_MS)
  {
    currentDegrees = degreeBoundingHelper(inertialSensor->get_heading());
    
    porportionalAmount = degreeBoundingHelper(endingDegrees - currentDegrees);

    accumulatedDegrees += porportionalAmount;
    accumulatedDegrees = bindToMagnitude(accumulatedDegrees, INTEGRATOR_MAX_MAGNITUDE);

    derivativeAmount = (porportionalAmount - lastDegrees) / DELTA_T;
    lastDegrees = porportionalAmount;

    integralAmount = accumulatedDegrees * DELTA_T;

    float total = porportionalAmount * kP + integralAmount * kI + derivativeAmount * kD;
    total = bindToMagnitude(total, 1);
    float speed = total * desiredSpeed;

    setMotors(rightMotors, -speed);
    setMotors(leftMotors, speed);

    lcd::set_text(3, "Desired " + to_string(endingDegrees));
    lcd::set_text(4, "Current: " + to_string(currentDegrees));
    lcd::set_text(5, "Raw Vals: " + to_string(porportionalAmount) + " " + to_string(integralAmount) + " " + to_string(derivativeAmount));
    lcd::set_text(6, "New Vals: " + to_string(porportionalAmount * kP) + " " + to_string(integralAmount * kI) + " " + to_string(derivativeAmount * kD));

    runTime += LOOP_DELAY;
    pros::delay(LOOP_DELAY);
  }
}
