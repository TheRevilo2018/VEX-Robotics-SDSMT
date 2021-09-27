#include "drive.h"

using namespace std;
using namespace vex;

FourWheelDrive::FourWheelDrive(vector<motor> & right, vector<motor> & left,
    inertial & sensor, controller & masterIn)
{
    vector<motor> *rightPointer = &right;
    vector<motor> *leftPointer = &left;
    inertial *inertialPointer = &sensor;
    controller *controllerPointer = &masterIn;

    rightMotors = rightPointer;
    leftMotors = leftPointer;
    inertialSensor = inertialPointer;
    master = controllerPointer;
    numMotors = rightMotors->size();

    setAllBrakeMode(BRAKE_MODE);

    readCalibration();
}

//take in a vector of motors, and set their speed to a value
void FourWheelDrive::setMotors(vector<motor> *motors, double speed)
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
        //lcd::set_text(0, "speed > maxSpeed: " + to_string(speed) + " bias: " + to_string(LRBiasHigh));
    }
    else if(speed > midSpeed)
    {
        double highPercent = (speed - midSpeed) / (maxSpeed - midSpeed);
        double lowPercent = (maxSpeed - speed) / (maxSpeed - midSpeed);

        rawSetMotors(speed, LRBiasLow * lowPercent + LRBiasHigh * highPercent);
        //lcd::set_text(0, "speed > midSpeed: " + to_string(speed) + " bias: "
        //        + to_string(LRBiasLow * lowPercent + LRBiasHigh * highPercent));
    }
    else if (speed >= 0)
    {
        rawSetMotors(speed, LRBiasLow);
        //lcd::set_text(0, "speed > 0: " + to_string(speed) + " bias: " + to_string(LRBiasLow));
    }
    //backwards biases
    else if (speed < -maxSpeed)
    {
        speed = -maxSpeed;
        rawSetMotors(speed, LRBiasHighBack);
        //lcd::set_text(0, "speed < -maxSpeed: " + to_string(speed) + " bias: " + to_string(LRBiasHighBack));
    }
    else if (speed < -midSpeed)
    {
        double highPercent = (-speed - midSpeed) / (maxSpeed - midSpeed);
        double lowPercent = (maxSpeed + speed) / (maxSpeed - midSpeed);

        rawSetMotors(speed, LRBiasLowBack * lowPercent + LRBiasHighBack * highPercent);
        //lcd::set_text(0, "speed < -midSpeed: " + to_string(speed) + " bias: "
        //        + to_string(LRBiasLow * lowPercent + LRBiasHigh * highPercent));
    }
    else //if (speed < 0)
    {
        rawSetMotors(speed, LRBiasLowBack);
        //lcd::set_text(0, "speed < 0: " + to_string(speed) + " bias: " + to_string(LRBiasLowBack));
    }
}

//take in a vector of motors, and set their brake type to a given type
void FourWheelDrive::setBrakes(vector<motor> *motors,  brakeType mode)
{
  for(auto motor: *motors)
  {
    motor.setBrake(mode);
  }
}

void FourWheelDrive::setBrakes(brakeType mode)
{
  for(auto motor: *leftMotors)
  {
    motor.setBrake(mode);
  }

  for(auto motor: *rightMotors)
  {
    motor.setBrake(mode);
  }
}

//tqke in a vector of motors, and call the move relative function for all of them with a given distance and speed
void FourWheelDrive::setMotorsRelative(vector<motor> * motors, double distance, double speed)
{
  for(auto motor : *motors)
  {
    motor.spinFor(distance, ROT_UNIT, speed, VEL_UNIT);
  }
}

void FourWheelDrive::setMotorsRelative(double distance, double speed)
{
  for(auto motor : *leftMotors)
  {
    motor.spinFor(distance, ROT_UNIT, speed, VEL_UNIT);
  }

  for(auto motor : *rightMotors)
  {
    motor.spinFor(distance, ROT_UNIT, speed, VEL_UNIT);
  }
}

void FourWheelDrive::setZeroPosition(vector<motor> * motors)
{
    for (int i = 0; i < motors->size(); i++) //sets the motors to 0
    {
        (*motors)[i].resetRotation();
    }
}

void FourWheelDrive::setZeroPosition()
{
    for (int i = 0; i < leftMotors->size(); i++) //sets the motors to 0
    {
        (*leftMotors)[i].resetRotation();
    }

    for (int i = 0; i < rightMotors->size(); i++) //sets the motors to 0
    {
        (*rightMotors)[i].resetRotation();
    }
}

double FourWheelDrive::getPosition(vector<motor> * motors)
{
    double averagePosition = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averagePosition += motors->at(i).position(ROT_UNIT);
    }

    return averagePosition / (motors->size());
}

double FourWheelDrive::getAllPosition()
{
    double averagePosition = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averagePosition += leftMotors->at(i).position(ROT_UNIT);
        averagePosition += rightMotors->at(i).position(ROT_UNIT);
    }

    return averagePosition / (numMotors * 2);
}

double FourWheelDrive::rawGetAllSpeed(double bias)
{
    double averageSpeed = 0;
    for(int i = 0; i < numMotors; i++)
    {
        averageSpeed += leftMotors->at(i).velocity(VEL_UNIT);
        averageSpeed += rightMotors->at(i).velocity(VEL_UNIT);
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
			task::sleep(LOOP_DELAY);
		}
	}
	else
	{
		while(currSpeed > targetSpeed + TOLERANCE)
		{
			currSpeed -= maxAccelerationBackward;
			setMotors(currSpeed);
			task::sleep(LOOP_DELAY);
		}
	}
}

void FourWheelDrive::driveTilesPID(float numTiles, float desiredSpeed)
{
    float INTEGRATOR_MAX_MAGNITUDE = 1000;
    float DELTA_T = LOOP_DELAY / 1000.0;
    const int STOP_LOOPS = 20;
    const float TILE_TOLERANCE = 0.02;
    const float DESIRED_SPEED = 70;
    // 4 Inches wheels, 600RPM motors, measured 222.22 ticks/rotation
    const double TICKS_PER_TILE = 1333.3;
    float currentDistance = 0;

    //float kP = 1;
    //float kI = .47;
    //float kD = 0.004;
    float kP = 3;
    float kI = 0;
    float kD = 0;

    float porportionalAmount = 0;
    float integralAmount = 0;
    float derivativeAmount = 0;

    long iterations = 1;
    float lastDistance = 0;
    float accumulatedDistance = 0;

    float lastEncoderVal = leftMotors->at(0).position(ROT_UNIT);
    float runTime = 0;
    int stopLoopCount = 0;

    int maxRunTime = max(ONE_SEC_IN_MS * 5, ONE_SEC_IN_MS * abs(numTiles) * 2);

    while( stopLoopCount <= STOP_LOOPS && runTime < maxRunTime)
    {
        porportionalAmount = numTiles - currentDistance;

        accumulatedDistance += porportionalAmount;
        accumulatedDistance = bindToMagnitude(accumulatedDistance, INTEGRATOR_MAX_MAGNITUDE);

        integralAmount = accumulatedDistance * DELTA_T;

        derivativeAmount = (lastDistance - currentDistance) / DELTA_T;

        float total = porportionalAmount * kP + integralAmount * kI + derivativeAmount * kD;
        total = bindToMagnitude(total, 1);

        float speed = total * desiredSpeed;

        float currentEncoderVal = leftMotors->at(0).position(ROT_UNIT);

        currentDistance += (currentEncoderVal - lastEncoderVal) / TICKS_PER_TILE;

        /*lcd::set_text(3, "Desired " + to_string(numTiles));
        lcd::set_text(4, "Current: " + to_string(currentDistance));
        lcd::set_text(5, "Raw Vals: " + to_string(porportionalAmount) + " " + to_string(integralAmount) + " " + to_string(derivativeAmount));
        lcd::set_text(6, "New Vals: " + to_string(porportionalAmount * kP) + " " + to_string(integralAmount * kI) + " " + to_string(derivativeAmount * kD));
        lcd::set_text(7, to_string(lastDistance) + " " + to_string(currentDistance));*/

        setMotors(rightMotors, speed);
        setMotors(leftMotors, speed);

        iterations++;
        lastDistance = porportionalAmount;
        lastEncoderVal = currentEncoderVal;

        runTime += LOOP_DELAY;
        task::sleep(LOOP_DELAY);

        if(abs(degreeBoundingHelper(currentDistance) - degreeBoundingHelper(numTiles))
                <= TILE_TOLERANCE)
            { stopLoopCount++;}
        else
            {stopLoopCount = 0;}
    }

    setMotors(rightMotors, 0);
    setMotors(leftMotors, 0);
}

void FourWheelDrive::turnDegreesPID(float numDegrees, float desiredSpeed)
{
    float startDegrees = degreeBoundingHelper(inertialSensor->heading());
    turnDegreesAbsolutePID(degreeBoundingHelper(numDegrees + startDegrees), desiredSpeed);
}

void FourWheelDrive::turnDegreesAbsolutePID(float targetDegrees, float desiredSpeed)
{
  //lcd::set_text(1, "target heading: " + to_string(targetDegrees) + " " + to_string(desiredSpeed));

  float INTEGRATOR_MAX_MAGNITUDE = 1000;
  float DELTA_T = LOOP_DELAY / 1000.0;
  const int STOP_LOOPS = 20;
  const float TURN_TOLERANCE = 2;
  const float DESIRED_SPEED = 70;
  const int MAX_RUN_TIME = ONE_SEC_IN_MS * 5;
  float endingDegrees = degreeBoundingHelper(targetDegrees);
  float currentDegrees = degreeBoundingHelper(inertialSensor->heading());

  //This is here to keep all of the tuning constants in the same place
  if(desiredSpeed == -1)
  {
      desiredSpeed = DESIRED_SPEED;
  }

  //lcd::set_text(2, "turnDegrees: " + to_string(currentDegrees) + " " + to_string(endingDegrees));

  float kP = 1 / 90.0; //speed to goal
  float kI = 1 / 90.0; //adds speed if too slow
  float kD = 0.15 / 90.0; //prevents overshoot

  float porportionalAmount = 0;
  float integralAmount = 0;
  float derivativeAmount = 0;
  float accumulatedDegrees = 0;

  float lastDegrees = 0;
  float runTime = 0;
  int stopLoopCount = 0;  

  while( stopLoopCount <= STOP_LOOPS && runTime < MAX_RUN_TIME)
  {
    currentDegrees = degreeBoundingHelper(inertialSensor->heading());

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

    //lcd::set_text(3, "Desired " + to_string(endingDegrees));
    //lcd::set_text(4, "Current: " + to_string(currentDegrees));
    //lcd::set_text(5, "Raw Vals: " + to_string(porportionalAmount) + " " + to_string(integralAmount) + " " + to_string(derivativeAmount));
    //lcd::set_text(6, "New Vals: " + to_string(porportionalAmount * kP) + " " + to_string(integralAmount * kI) + " " + to_string(derivativeAmount * kD));

    runTime += LOOP_DELAY;
    task::sleep(LOOP_DELAY);

    if(abs(degreeBoundingHelper(currentDegrees) - degreeBoundingHelper(endingDegrees)) <= TURN_TOLERANCE)
    {
        stopLoopCount++;
    }
    else
    {
        stopLoopCount = 0;
    }
  }

  setMotors(0);
}
