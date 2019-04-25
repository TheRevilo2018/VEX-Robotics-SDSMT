#include "main.h"
#include "helperfunctions.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() //aaa
{
  int mode = 0;
  switch(mode)
  {
    case(0):
    {
      //red autonomous
      //forward to grab ball under cap
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2100, 60);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
      pros::delay(300);
      setMotors(intakeMotors, 0);

      //back up and turn around to grab cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -650, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1450);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -750, 60); //a
      pros::delay(180);

      //grab cap, turn to platform and drop on platform
      actuatorState = true;
      actuator.set_value(actuatorState);
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[2], 127);
      liftMotorRight.move_absolute(liftPositions[2], 127);
      pros::delay(400);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 510);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -200, 70); //a
      pros::delay(180);
      actuatorState = false;
      actuator.set_value(actuatorState);
      pros::delay(180);

      //back up, turn and align on platform
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 300, 40); //a
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127);
      pros::delay(400);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 200);
      pros::delay(180);
      //align
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
      pros::delay(180);

      //back away from platform and grab second cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 30); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1350);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -850, 40); //a
      pros::delay(180);
      actuatorState = true;
      actuator.set_value(actuatorState);
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(400);
      //move into position for highscore from second cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 680);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1200, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 725);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1500, 40); //a
      pros::delay(180);

      //score the pole and align on platform
      highScore(leftWheelMotorVector, rightWheelMotorVector,liftMotors, actuatorState);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127);
      pros::delay(400);
      autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 130);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1200, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 140);
      pros::delay(180);
      //align
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
      pros::delay(180);

      //back up and realign
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 300, 40); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1350);
      pros::delay(180);
      //realign after spinning
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 800, 30); //a
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -400, 40); //a
      pros::delay(180);
      autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 230);
      pros::delay(180);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 222);
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2700, 90); //a
      pros::delay(180);
      break;
    }
  }
}
