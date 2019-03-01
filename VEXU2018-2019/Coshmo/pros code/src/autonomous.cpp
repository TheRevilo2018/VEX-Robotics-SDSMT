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
void autonomous()
{
  int autonType = 3;
  switch(autonType)
  {
    //blue long auton
    case 0:
      //grab ball under first cap
      flipCrown(liftMotor);

      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2200, 50);
      pros::delay(500);
      setMotors(intakeMotors, -100);
      pros::delay(250);
      setMotors(intakeMotors, 0);

      //back up and grab second cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1175, 50);
      pros::delay(400);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 132, 50);
      pros::delay(300);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1750, 40);
      pros::delay(300);
      liftMotor.move_absolute(liftPositions[0], 127);
      pros::delay(1000);

      //move cap to post and score it
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 700, 50);
      pros::delay(300);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 32, 50);
      pros::delay(300);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2600, 50);
      pros::delay(300);
      highScore(leftWheelMotorVector, rightWheelMotorVector, liftMotor);
      pros::delay(200);
      liftMotor.move_absolute(0, 127);

      //drive closer to flags and launch at opponent's flags
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1100, 50);
      pros::delay(300);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -130, 50);
      pros::delay(500);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);

      //move to team platform
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -65, 50);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 500, 50);
      pros::delay(200);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 90, 50);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 700, 75);
      pros::delay(200);
      return;
      break;
    //red long auton
    case 1:
      flipCrown(liftMotor);
      liftMotor.move_absolute(liftPositions[3], 127);
      pros::delay(2500);
      liftMotor.move_absolute(0, 127);
      pros::delay(2500);
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2300, 40);
      pros::delay(500);
      setMotors(intakeMotors, -100);
      pros::delay(260);
      setMotors(intakeMotors, 0);

      //back up and grab second cap
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1275, 40);
      pros::delay(400);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -137, 40);
      pros::delay(300);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1750, 40);
      pros::delay(300);
      liftMotor.move_absolute(liftPositions[0], 127);
      pros::delay(1000);

      //move cap to post and score it
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 700, 40);
      pros::delay(400);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -33, 40);
      pros::delay(400);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2500, 40);
      pros::delay(400);
      highScore(leftWheelMotorVector, rightWheelMotorVector, liftMotor);
      pros::delay(100);
      liftMotor.move_absolute(0, 127);

      pros::delay(400);
      //drive closer to flags and launch at opponent's flags
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -1100, 40);
      pros::delay(300);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 148, 40);
      pros::delay(500);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);

      //move to team platform
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 34, 40);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1450, 40);
      pros::delay(200);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -95, 40);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 3000, 75);
      pros::delay(200);
      return;

      break;
    //short blue auton
    case 2:
      //flip up the crown using the swing arm
      flipCrown(liftMotor);

      //grab the ball underneath the cap directly in front of the bot
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2300, 40);
      pros::delay(500);
      setMotors(intakeMotors, -100);
      pros::delay(150);
      setMotors(intakeMotors, 0);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -500, 40);
      pros::delay(200);

      //turn to opposite team's flags and score tem
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -56, 40);
      pros::delay(200);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);

      //turn to team platform and park
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, -19, 40);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2150, 60);
      return;
      break;
  //short red auton
    case 3:
      //flip the crown with the swing arm
      flipCrown(liftMotor);

      //grab ball underneath cap directly in front of robot
      setMotors(intakeMotors, 100);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2300, 40);
      pros::delay(500);
      setMotors(intakeMotors, -100);
      pros::delay(230);
      setMotors(intakeMotors, 0);

      //position to fire at opposite team's flags
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, -500, 40);
      pros::delay(200);
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 44, 40);
      pros::delay(200);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);

      //turn toward team platform and park
      autoTurnRelative(leftWheelMotorVector, rightWheelMotorVector, 19, 40);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 2150, 60);
      return;
      break;
  };
}
