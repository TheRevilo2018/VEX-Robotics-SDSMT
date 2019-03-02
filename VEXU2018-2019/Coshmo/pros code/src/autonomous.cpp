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
  int autonType = 4;
  switch(autonType)
  {
    //long red auton
    case 0: {
    flipCrown(liftMotor);

    //grab ball underneath cap directly in front of robot
    setMotors(intakeMotors, 100);
    drive(leftWheelMotorVector, rightWheelMotorVector, 2200);
    pros::delay(500);
    setMotors(intakeMotors, -100);
    pros::delay(230);
    setMotors(intakeMotors, 0);

    //grab flat cap
    drive(leftWheelMotorVector, rightWheelMotorVector, -1101);
    pros::delay(200);
    turnRight(leftWheelMotorVector, rightWheelMotorVector, 860);
    pros::delay(200);

    drive(leftWheelMotorVector, rightWheelMotorVector, -1650);
    pros::delay(200);
    liftMotor.move_absolute(liftPositions[0], 127);
    pros::delay(1000);

    //back up and naviagte to pole and score
    drive(leftWheelMotorVector, rightWheelMotorVector, 750);
    pros::delay(200);
    turnRight(leftWheelMotorVector, rightWheelMotorVector, 230);
    pros::delay(200);
    drive(leftWheelMotorVector, rightWheelMotorVector, 750);
    pros::delay(200);
    turnLeft(leftWheelMotorVector, rightWheelMotorVector, 560);
    pros::delay(200);
    drive(leftWheelMotorVector, rightWheelMotorVector, 1000);
    pros::delay(200);
    highScore(leftWheelMotorVector, rightWheelMotorVector, liftMotor);
    pros::delay(200);
    liftMotor.move_absolute(0, 127);
    pros::delay(1000);

    //line up shot on opposite flags next to platform
    drive(leftWheelMotorVector, rightWheelMotorVector, -1500);
    pros::delay(200);
    turnLeft(leftWheelMotorVector, rightWheelMotorVector, 900);
    pros::delay(200);
    doubleLaunch(launchMotors, anglerMotor, intakeMotors);
    pros::delay(200);
    turnLeft(leftWheelMotorVector, rightWheelMotorVector, 185);
    pros::delay(200);
    //autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1500, 60);
    //pros::delay(200);
    return;
    break;
  }
    //long blue auton
    case 1: {
      flipCrown(liftMotor);

      //grab ball underneath cap directly in front of robot
      setMotors(intakeMotors, 100);
      drive(leftWheelMotorVector, rightWheelMotorVector, 2200);
      pros::delay(200);
      int timeOut = 1000;
      while(middleLightSensor.get_value() > 2100 && timeOut >= 0)
      {
        setMotors(intakeMotors, 100);
        pros::delay(20);
        timeOut -= 20;
      }
      setMotors(intakeMotors, 0);
      pros::delay(230);

      //grab flat cap
      drive(leftWheelMotorVector, rightWheelMotorVector, -1101);
      pros::delay(200);
      turnLeft(leftWheelMotorVector, rightWheelMotorVector, 860);
      pros::delay(200);

      drive(leftWheelMotorVector, rightWheelMotorVector, -1650);
      pros::delay(200);
      liftMotor.move_absolute(liftPositions[0], 127);
      pros::delay(1000);

      //back up and naviagte to pole and score
      drive(leftWheelMotorVector, rightWheelMotorVector, 750);
      pros::delay(200);
      turnLeft(leftWheelMotorVector, rightWheelMotorVector, 230);
      pros::delay(200);
      drive(leftWheelMotorVector, rightWheelMotorVector, 750);
      pros::delay(200);
      turnRight(leftWheelMotorVector, rightWheelMotorVector, 560);
      pros::delay(200);
      drive(leftWheelMotorVector, rightWheelMotorVector, 1000);
      pros::delay(200);
      highScore(leftWheelMotorVector, rightWheelMotorVector, liftMotor);
      pros::delay(200);
      liftMotor.move_absolute(0, 127);
      pros::delay(1000);

      //line up shot on opposite flags next to platform
      drive(leftWheelMotorVector, rightWheelMotorVector, -1500);
      pros::delay(200);
      turnRight(leftWheelMotorVector, rightWheelMotorVector, 900);
      pros::delay(200);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);
      turnRight(leftWheelMotorVector, rightWheelMotorVector, 185);
      pros::delay(200);
      autoDriveDistance(leftWheelMotorVector, rightWheelMotorVector, 1500, 60);
      //pros::delay(200);
      return;
      break;
    }
    //short red auton
    case 2:
    {

      //flip the crown with the swing arm
      flipCrown(liftMotor);

      //grab ball underneath cap directly in front of robot
      setMotors(intakeMotors, 100);
      drive(leftWheelMotorVector, rightWheelMotorVector, 2300);
      pros::delay(500);
      setMotors(intakeMotors, -100);
      pros::delay(230);
      setMotors(intakeMotors, 0);

      //position to fire at opposite team's flags
      drive(leftWheelMotorVector, rightWheelMotorVector, -500);
      pros::delay(200);
      turnLeft(leftWheelMotorVector, rightWheelMotorVector, 240);
      pros::delay(200);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);

      //turn toward team platform and park
      turnLeft(leftWheelMotorVector, rightWheelMotorVector, 105);
      pros::delay(200);
      drive(leftWheelMotorVector, rightWheelMotorVector, 2150);
      return;
      break;
    }
  //short blue auton
    case 3:
    {
      //flip the crown with the swing arm
      flipCrown(liftMotor);

      //grab ball underneath cap directly in front of robot
      setMotors(intakeMotors, 100);
      drive(leftWheelMotorVector, rightWheelMotorVector, 2300);
      pros::delay(500);
      setMotors(intakeMotors, -100);
      pros::delay(230);
      setMotors(intakeMotors, 0);

      //position to fire at opposite team's flags
      drive(leftWheelMotorVector, rightWheelMotorVector, -500);
      pros::delay(200);
      turnRight(leftWheelMotorVector, rightWheelMotorVector, 240);
      pros::delay(200);
      doubleLaunch(launchMotors, anglerMotor, intakeMotors);
      pros::delay(200);

      //turn toward team platform and park
      turnRight(leftWheelMotorVector, rightWheelMotorVector, 105);
      pros::delay(200);
      drive(leftWheelMotorVector, rightWheelMotorVector, 2150);
      return;
      break;
    }
    case 4:
    {
      turnRight(leftWheelMotorVector, rightWheelMotorVector, 550);
      pros::delay(200);
    }
  };
}
