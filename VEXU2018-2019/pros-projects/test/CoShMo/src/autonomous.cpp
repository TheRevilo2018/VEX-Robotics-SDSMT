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
  setMotors(intakeMotors, 100);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2500, 60);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 200, 40);

  pros::delay(200);
  setMotors(intakeMotors, 0);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -2150, 60); //a
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 700);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1275, 60);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -500, 40);
  pros::delay(300);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 375, 60);
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 670);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1500, 60);
  pros::delay(200);
  actuatorState = true;
  actuator.set_value(actuatorState);
  pros::delay(200);
  liftMotorLeft.move_absolute(liftPositions[1], 127);
  liftMotorRight.move_absolute(liftPositions[1], 127);
  pros::delay(500);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 900, 60);
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 725);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 450, 30);
  pros::delay(200);
  highScore(leftWheelMotorVector, rightWheelMotorVector, liftMotors, actuatorState);
}
