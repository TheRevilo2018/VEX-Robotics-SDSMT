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
  //red autonomous
  //forward to grab ball under cap
  setMotors(intakeMotors, 100);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2200, 60);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 40);
  pros::delay(200);
  setMotors(intakeMotors, 0);

  //back up and turn around to grab cap
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -750, 60); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1450);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -750, 40); //a
  pros::delay(200);

  //grab cap, turn to platform and drop on platform
  actuatorState = true;
  actuator.set_value(actuatorState);
  pros::delay(200);
  liftMotorLeft.move_absolute(liftPositions[2], 127);
  liftMotorRight.move_absolute(liftPositions[2], 127);
  pros::delay(400);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 510);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -200, 40); //a
  pros::delay(200);
  actuatorState = false;
  actuator.set_value(actuatorState);
  pros::delay(200);

  //back up, turn and align on platform
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 300, 40); //a
  pros::delay(200);
  liftMotorLeft.move_absolute(liftPositions[0], 127);
  liftMotorRight.move_absolute(liftPositions[0], 127);
  pros::delay(400);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 200);
  pros::delay(200);
  //align
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
  pros::delay(200);

  //back away from platform and grab second cap
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 30); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1350);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -850, 40); //a
  pros::delay(200);
  actuatorState = true;
  actuator.set_value(actuatorState);
  pros::delay(200);

  //move into position for highscore from second cap
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 60); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 680);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1200, 60); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 770);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1500, 30); //a
  pros::delay(200);

  //score the pole and align on platform
  highScore(leftWheelMotorVector, rightWheelMotorVector,liftMotors, actuatorState);
  liftMotorLeft.move_absolute(liftPositions[0], 127);
  liftMotorRight.move_absolute(liftPositions[0], 127);
  pros::delay(400);
  autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 100);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1200, 60); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 100);
  pros::delay(200);
  //align
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -800, 40); //a
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 300, 40); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 1350);
  pros::delay(200);
  //realign after spinning
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 800, 30); //a
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -400, 40); //a
  pros::delay(200);
  autoTurnRight(leftWheelMotorVector, rightWheelMotorVector, 230);
  pros::delay(200);
  doubleLaunch(launchMotors, anglerMotor, intakeMotors); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 222);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2200, 100); //a
  pros::delay(200);
}
