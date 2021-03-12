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

void setIntakeContain()
{
  // Set everything to an intaking but not inserting speeds
  pooper = 0;
  setMotors(intakeMotorVector, intakeConst);
  bottomDrum = intakeConst;
  topDrum = inserterRestingConst;
}

void setIntakePoop()
{
  // Set everything to an intaking but not inserting speeds
  pooper = -inserterConst;
  setMotors(intakeMotorVector, intakeConst);
  bottomDrum = intakeConst;
  topDrum = -inserterConst;
}

void setIntakeInsert()
{
  // Set everything to an intaking but not inserting speeds
  pooper = inserterConst;
  setMotors(intakeMotorVector, intakeConst);
  bottomDrum = intakeConst;
  topDrum = inserterConst;
}

bool isHoldingBall()
{
  return false;
}
Color getBallColor()
{
  return blue;
}
void autoIntake()
{
  setIntakeContain();
  float MAX_TIME = 1000;
  float currentTime = 0;
  bool holdingBall = false;

  while(!holdingBall && currentTime < MAX_TIME)
  {
    holdingBall = isHoldingBall();
    currentTime += loopDelay;
    pros::delay(loopDelay);
  }

  Color ballColor = getBallColor();
  if(ballColor != NA)
  {
    // Either shoot or poop
    if(ballColor == colorToPoop)
    {
      setIntakePoop();
      pros::delay(500);
    }
    else
    {
      setIntakeInsert();
      pros::delay(500);
    }
  }
  setIntakeContain();
}
