#include "robot-config.h"
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Drive for Revolutions
This program will instruct your robot to move forward at half power for one revolution.
There is a two second pause at the beginning of the program.

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
    RightMotor.setVelocity(50, vex::velocityUnits::pct);
    
    //Rotate both motors for one revolution. Make sure the first motor is not blocking by setting waitForCompletion to false.
    LeftMotor.rotateFor(1, vex::rotationUnits::rev, false); //Rotates the left motor 1 revolution, and is not blocking.
    RightMotor.rotateFor(1, vex::rotationUnits::rev); //Rotates the right motor 1 revolution and is blocking. This will cause the program to wait here until the right motor completes its one revolution.
    
    //The motors automatically brake after they reach their destination. 
    
    //Print to the brain's screen that the program has ended.
    Brain.Screen.newLine();//Move the cursor to a new line on the screen.
    Brain.Screen.print("User Program has Ended.");
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}