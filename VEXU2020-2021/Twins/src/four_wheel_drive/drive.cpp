#include "drive.h"

using namespace pros;
using namespace std;

FourWheelDrive::FourWheelDrive(vector<Motor> & right, vector<Motor> & left,
                               Imu & sensor, Controller & masterIn)
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

    readCalibration();
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

void FourWheelDrive::driveTilesPID(float numTiles, float desiredSpeed)
{
    float INTEGRATOR_MAX_MAGNITUDE = 100;
    float DELTA_T = LOOP_DELAY / 1000.0;
    float currentDistance = 0;

    float kP = 1;
    float kI = .4;
    float kD = .01;

    float porportionalAmount = 0;
    float integralAmount = 0;
    float derivativeAmount = 0;

    long iterations = 1;
    float lastDistance = 0;
    float accumulatedDistance = 0;

    float lastEncoderVal = (leftMotors->at(0).get_position() + rightMotors->at(0).get_position())/2.0;
    float runTime = 0;

    int maxRunTime = max(ONE_SEC_IN_MS, ONE_SEC_IN_MS * abs(numTiles));
    porportionalAmount = numTiles - currentDistance;

    float initialHeading = degreeBoundingHelper(inertialSensor->get_heading());
    float initialEncoderLeft = leftMotors->at(0).get_position();
    float initialEncoderRight = rightMotors->at(0).get_position();

    // While not at destination and not out of time
    while ((abs(porportionalAmount) > 0.1 ||
            derivativeAmount > 0.2 * kD) &&
            runTime < maxRunTime)
    {
        porportionalAmount = numTiles - currentDistance;

        accumulatedDistance += porportionalAmount;
        accumulatedDistance = bindToMagnitude(accumulatedDistance, INTEGRATOR_MAX_MAGNITUDE);

        integralAmount = accumulatedDistance * DELTA_T;

        derivativeAmount = (lastDistance - currentDistance) / DELTA_T;

        float total = porportionalAmount * kP + integralAmount * kI + derivativeAmount * kD;
        total = bindToMagnitude(total, 1);

        float speed = total * desiredSpeed;
        if(abs(speed) <= minSpeed)
        {
          speed = speed / abs(speed) * minSpeed;
        }
        float currentEncoderVal = (leftMotors->at(0).get_position() + rightMotors->at(0).get_position())/2.0;

        // 4 Inches wheels, 600RPM motors, measured 222.22 ticks/rotation
        double encoderTicksPerTile = 1333.33;
        currentDistance += (currentEncoderVal - lastEncoderVal) / encoderTicksPerTile;

        lcd::set_text(3, "Desired " + to_string(numTiles));
        lcd::set_text(4, "Current: " + to_string(currentDistance));
        lcd::set_text(5, "Raw Vals: " + to_string(porportionalAmount) + " " + to_string(integralAmount) + " " + to_string(derivativeAmount));
        lcd::set_text(6, "New Vals: " + to_string(porportionalAmount * kP) + " " + to_string(integralAmount * kI) + " " + to_string(derivativeAmount * kD));
        lcd::set_text(7, to_string(lastDistance) + " " + to_string(currentDistance));

        float currentHeading = degreeBoundingHelper(inertialSensor->get_heading());

        float speedLeft = speed;
        float speedRight = speed;

        bool correctedLeft = false;
        bool correctedRight = false;
        // If we've turned too far, adjust
        float degreeDeviation = degreeBoundingHelper(initialHeading - currentHeading);
        if(abs(degreeDeviation) > 3)
        {
          // We're facing more right than we want
          if(degreeDeviation > 0 && degreeDeviation < 180)
          {
            if(speed > 0)
            {
              correctedRight = true;
            }
            else
            {
              correctedLeft = true;
            }
          }
          // We're facing more left than we want
          else
          {
            if(speed > 0)
            {
              correctedLeft = true;
            }
            else
            {
              correctedRight = true;
            }
          }
        }

        float leftEncoderDiff = leftMotors->at(0).get_position() - initialEncoderLeft;
        float rightEncoderDiff = rightMotors->at(0).get_position() - initialEncoderRight;
        if(abs(leftEncoderDiff - rightEncoderDiff) > 50)
        {
          if(leftEncoderDiff > rightEncoderDiff)
          {
            if(speed > 0)
            {
                correctedLeft = true;
            }
            else
            {
              correctedRight = true;
            }
          }
          else
          {
            if(speed > 0)
            {
              correctedRight = true;
            }
            else
            {
              correctedLeft = true;
            }
          }
        }

        if(correctedLeft && !correctedRight)
        {
          speedLeft *= 0.90;
        }
        else if(!correctedLeft && correctedRight)
        {
          speedRight *= 0.90;
        }

        setMotors(rightMotors, speedRight);
        setMotors(leftMotors, speedLeft);

        iterations++;
        lastDistance = porportionalAmount;
        lastEncoderVal = currentEncoderVal;
        runTime += LOOP_DELAY;
        pros::delay(LOOP_DELAY);
    }
    setMotors(0);
}

void FourWheelDrive::turnDegreesPID(float numDegrees, float desiredSpeed)
{
    float startDegrees = degreeBoundingHelper(inertialSensor->get_heading());
    turnDegreesAbsolutePID(degreeBoundingHelper(numDegrees + startDegrees), desiredSpeed);
}

void FourWheelDrive::turnDegreesAbsolutePID(float targetDegrees, float desiredSpeed)
{
    lcd::set_text(1, "target heading: " + to_string(targetDegrees) + " " + to_string(desiredSpeed));

    float INTEGRATOR_MAX_MAGNITUDE = 100;
    float DELTA_T = LOOP_DELAY / 1000.0;
    float MINSPEED_MOD = 2;
    float endingDegrees = degreeBoundingHelper(targetDegrees);
    float currentDegrees = degreeBoundingHelper(inertialSensor->get_heading());

    lcd::set_text(2, "turnDegrees: " + to_string(currentDegrees) + " " + to_string(endingDegrees));
    lcd::set_text(3, "turnDegrees: " + to_string(inertialSensor->get_heading()));

    float kP = 1.5 / 90.0;
    float kI = .20 / 90.0;
    float kD = .05 / 90.0;

    float porportionalAmount = 0;
    float integralAmount = 0;
    float derivativeAmount = 0;
    float accumulatedDegrees = 0;

    float lastDegrees = 0;
    float runTime = 0;

    porportionalAmount = degreeBoundingHelper(endingDegrees - currentDegrees);

    // While not at destination and not out of time
    while( (abs(porportionalAmount) >= 2 ||
     abs(derivativeAmount) >= (6 / DELTA_T)) &&
     runTime < ONE_SEC_IN_MS * 10)
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

        if (fabs(speed) < minSpeed * MINSPEED_MOD)
        {
            speed = speed * minSpeed * MINSPEED_MOD / fabs(speed);
        }

        setMotors(rightMotors, -speed);
        setMotors(leftMotors, speed);

        lcd::set_text(3, "Desired " + to_string(endingDegrees));
        lcd::set_text(4, "Current: " + to_string(currentDegrees));
        lcd::set_text(5, "Raw Vals: " + to_string(porportionalAmount) + " " + to_string(integralAmount) + " " + to_string(derivativeAmount));
        lcd::set_text(6, "New Vals: " + to_string(porportionalAmount * kP) + " " + to_string(integralAmount * kI) + " " + to_string(derivativeAmount * kD));

        runTime += LOOP_DELAY;
        pros::delay(LOOP_DELAY);
    }

    setMotors(0);
}
