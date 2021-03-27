#include "../include/helperFunctions.h"

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

bool pressButton(bool press, bool &debounce)
{
	if(press)
    {
        if(!debounce)
        {
            debounce = true;
            return true;
        }
    }
    else
    {
        debounce = false;
    }

    return false;
}


void unfold()
{
  // We want to run the bottom rollor to detatch its rubber band mounting
  // Our intake is a ratchet, if we run it negative it will lock and move instead of skipping
  bottomDrum = 100;
  setMotors(intakeMotorVector, -100);
  pros::delay(800);
  bottomDrum = 0;
  setMotors(intakeMotorVector, 0);
}

void setOuttakeContain()
{
  // Set everything to an intaking but not inserting speeds
  pooper = 0;
  topDrum = inserterRestingConst;

}

void setOuttakePoop()
{
  // Set everything to an intaking but not inserting speeds
  pooper = pooperConst;
  topDrum = -inserterConst;
}

void setOuttakeInsert()
{
  // Set everything to an intaking but not inserting speeds
  pooper = -pooperConst;
  topDrum = inserterConst;
}

bool isHoldingBall()
{
  int value = opticalSensor.get_proximity();
  pros::lcd::set_text(5, "Proximity: " + std::to_string(value));
  if(value > 25)
  {
    return true;
  }
  return false;
}

Color getBallColor()
{
  if(!isHoldingBall())
  {
    return NA;
  }
  else
  {
      auto colors = opticalSensor.get_rgb();
      if(colors.red > colors.blue)
      {
        return red;
      }
      else
      {
        return blue;
      }
  }
}


void autoCycle(int time)
{
  setMotors(intakeMotorVector, intakeConst);
  bottomDrum = intakeConst;
  setOuttakeContain();
  float MAX_TIME = time;
  float currentTime = 0;

  while(currentTime < MAX_TIME)
  {
    Color lastSeenBall = getBallColor();
    pros::lcd::set_text(3, "Got Color: " + std::to_string(lastSeenBall));
    std::rotate(seenBuffer.begin(), seenBuffer.begin()+1, seenBuffer.end());
    seenBuffer[0] = lastSeenBall;

    int launchCount = 0;
    int poopCount = 0;
    for(int i = 0; i < seenBufferSize; i++)
    {
      if(seenBuffer[i] == colorToPoop)
      {
        poopCount++;
      }
      else if(seenBuffer[i] != colorToPoop && seenBuffer[i] != NA)
      {
        launchCount++;
      }
    }
    if(poopCount > seenBufferSize/2)
    {
      setOuttakePoop();
      seenBuffer.assign(seenBufferSize, NA);
      pros::delay(500);
      setOuttakeContain();
      currentTime += 500;
    }
    else if(launchCount > seenBufferSize/2)
    {
      setOuttakeInsert();
      seenBuffer.assign(seenBufferSize, NA);
      pros::delay(500);
      setOuttakeContain();
      currentTime += 500;
    }
    pros::delay(20);
    currentTime+= 20;
  }
  setMotors(intakeMotorVector, 0);
  setOuttakeInsert();
  pros::delay(800);
  setMotors(intakeMotorVector, intakeConst);
  setOuttakeContain();
}
