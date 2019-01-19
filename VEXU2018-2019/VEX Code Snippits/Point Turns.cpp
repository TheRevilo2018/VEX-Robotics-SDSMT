#include "robot-config.h"
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Point Turns
This program instructs your robot to make a point turn right for 0.75 seconds, wait for 1 second and then
make a point turn left for 0.75 seconds.  There is a two second pause at the beginning of the program.

Robot Configuration:
[Smart Port]    [Name]        [Type]           [Description]       [Reversed]
Motor Port 1    LeftMotor     V5 Smart Motor    Left side motor     false
Motor Port 10   RightMotor    V5 Smart Motor    Right side motor    true

----------------------------------------------------------------------------------------------------*/

int main() {
    
    vex::task::sleep(2000); //Wait 2 seconds or 2000 milliseconds before starting the program.
    //Print to the screen that the program has started.
    Brain.Screen.print("User Program has Started.");
    
    //Set the velocity of the left and right motor to 50% power. This command will not make the motor spin.
    LeftMotor.setVelocity(50, vex::velocityUnits::pct);
    RightMotor.setVelocity(50,vex::velocityUnits::pct);
    
    //Turn right at half power for 0.75 seconds or 750 milliseconds.
	LeftMotor.spin(vex::directionType::fwd); //Spin the left motor in the forward direction.
    RightMotor.spin(vex::directionType::rev); //Spin the right motor in the reverse direction.
    vex::task::sleep(750); //Wait .750 seconds or 750 milliseconds.
    
    //Stop the motors and wait 1 second or 1000 milliseconds.
    LeftMotor.stop(); //Stop the left motor.
    RightMotor.stop(); //Stop the right motor.
    vex::task::sleep(1000); //Wait 1 second or 1000 milliseconds.
    
    //Turn left at half power for 0.75 seconds or 750 milliseconds.
    LeftMotor.spin(vex::directionType::rev); //Spin the left motor in the reverse direction.
    RightMotor.spin(vex::directionType::fwd); //Spin the right motor in the forward direction.
    vex::task::sleep(750); //Wait .750 seconds or 750 milliseconds.
    
    //Stop the motors
    LeftMotor.stop();
    RightMotor.stop();
    
    //Print to the brain's screen that the program has ended.
    Brain.Screen.newLine();//Move the cursor to a new line on the screen.
    Brain.Screen.print("User Program has Ended.");
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
    
}