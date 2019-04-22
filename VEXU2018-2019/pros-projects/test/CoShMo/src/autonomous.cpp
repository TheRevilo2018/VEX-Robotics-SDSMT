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
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2700, 60);
  pros::delay(200);
  setMotors(intakeMotors, 0);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1900, 60);
  pros::delay(200);
  autoTurnLeft(leftWheelMotorVector, rightWheelMotorVector, 650);
  pros::delay(200);
  autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1300, 60);
  pros::delay(200);
}
