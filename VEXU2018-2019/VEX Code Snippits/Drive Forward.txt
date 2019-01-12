#include "robot-config.h"
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Drive Forward
This program instructs your robot to move forward at half power for three seconds.
There is a two second pause at the beginning of the program.

Robot Configuration: 
[Smart Port]    [Name]        [Type]           [Description]       [Reversed]
Motor Port 1    LeftMotor     V5 Smart Motor    Left side motor     false
Motor Port 10   RightMotor    V5 Smart Motor    Right side motor    true

----------------------------------------------------------------------------------------------------*/

int main() {
    
    //Wait 2 seconds or 2000 milliseconds before starting the program.
	vex::task::sleep(2000);
    //Print to the screen that the program has started.
    Brain.Screen.print("User Program has Started.");
    
    //Set the velocity of the left and right motor to 50% power. This command will not make the motor spin.
    LeftMotor.setVelocity(50, vex::velocityUnits::pct);
    RightMotor.setVelocity(50, vex::velocityUnits::pct);
    
	//Spin the right and left motor in the forward direction. The motors will spin at 50% power because of the previous commands.
    LeftMotor.spin(vex::directionType::fwd);
    RightMotor.spin(vex::directionType::fwd);
    
	//Wait 3 second or 3000 milliseconds.
    vex::task::sleep(3000);
    
	//Stop both motors.
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