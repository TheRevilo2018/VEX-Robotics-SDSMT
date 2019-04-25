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
  int mode = 1;
  switch(mode)
  {
    case(0):
    {
      //red long autonomous
      //forward to grab ball under cap
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2050, 60);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
      pros::delay(300);
      setMotors(intakeMotors, 0);

      //back up and turn around to grab cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -600, 60); //a
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
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1380);
      pros::delay(180);
      //TODO
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -500, 40); //a
      pros::delay(180);
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(400);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -350, 40); //aa

      /*
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -850, 40); //a
      pros::delay(180);

      */

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
      doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aaa
      anglerMotor.move_absolute(0, 100);
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 222);
      pros::delay(180);
      /*
      liftMotorLeft.move_absolute(liftPositions[1], 127); //aa
      liftMotorRight.move_absolute(liftPositions[1], 127);
      pros::delay(180);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2700, 90); //a
      pros::delay(180);
      */
      break;
    }
    case(1):
    {
      //red short autonomous
      //forward to grab ball under cap
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2050, 60);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
      pros::delay(300);
      setMotors(intakeMotors, 0);

      //back up and turn around to grab cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -600, 60); //a
      pros::delay(180);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 420);
      pros::delay(180);
      pros::delay(30000);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aa
      pros::delay(200);
      autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 380);
      pros::delay(180);


      //raise arm to get on platform correctly, then lower it after
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127); //aaaaa
      pros::delay(400);
      setMotors(leftWheelMotorVector, 80);
      setMotors(rightWheelMotorVector, 80);
      pros::delay(1500);
      setMotors(leftWheelMotorVector, 0);
      setMotors(rightWheelMotorVector, 0);
      liftMotorLeft.move_absolute(liftPositions[0], 127);
      liftMotorRight.move_absolute(liftPositions[0], 127); //aaaaa
      pros::delay(400);
      anglerMotor.move_absolute(0, 100);
      pros::delay(200);
      anglerMotor = 0;
      pros::delay(200);
      break;

      //back up from platform angle then shoot at opposite flags
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -300, 40); //a
      pros::delay(180);
      autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 300);
      pros::delay(180);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aa
      anglerMotor.move_absolute(0, 100);
      pros::delay(180);

      //back up, and then climb platform
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -300, 40); //a
      pros::delay(180);
      autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 300);
      pros::delay(180);
      /*
      liftMotorLeft.move_absolute(liftPositions[1], 127);
      liftMotorRight.move_absolute(liftPositions[1], 127); //aaaaa
      pros::delay(400);
      setMotors(leftWheelMotorVector, 80);
      setMotors(rightWheelMotorVector, 80);
      pros::delay(1000);
      setMotors(leftWheelMotorVector, 0);
      setMotors(rightWheelMotorVector, 0);
      */
      return;
      break;
      case (2):
      {
        //forward to grab ball under cap
        setMotors(intakeMotors, 100);
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2050, 60);
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 25);
        pros::delay(300);
        setMotors(intakeMotors, 0);

        //back up and turn around to grab cap
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -600, 60); //a
        pros::delay(180);
        autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 1250);
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
        autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 510);
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
        autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 200);
        pros::delay(180);
        //align
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
        pros::delay(180);
        break;

        //back up from platform angle then shoot at opposite flags
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -300, 40); //a
        pros::delay(180);
        autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 300);
        pros::delay(180);
        doubleLaunch(launchMotors, anglerMotor, intakeMotors, farAnglerPositions); //aa
        anglerMotor.move_absolute(0, 100);
        pros::delay(180);

        //back up, and then climb platform
        autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -300, 40); //a
        pros::delay(180);
        autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 300);
        pros::delay(180);
        break;
      }
    }
  }
}
