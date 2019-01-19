#include "robot-config.h"
#include "aliases.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  vex::directionType robotDirection;
  ll turnThreshold = 10;
  while (1){
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    
    
    
    //left/right control is axis1, up/down is axis 3;
    
    //if turning
    if(abs(mainController.axis3.value()) > turnThreshold && abs(mainController.axis1.value()) > driveThreshold)
    {
        if(mainController.axis3.value() < 0)
        {
            rightMotors.spin(forward, abs(mainController.axis1.value()), percent);
            leftMotors.spin(reverse, abs(mainController.axis1.value()), percent);
        }
        else
        {
            rightMotors.spin(reverse, abs(mainController.axis1.value()), percent);
            leftMotors.spin(forward, abs(mainController.axis1.value()), percent);
            
        }
    }
    //if driving in a line
    else if(abs(mainController.axis1.value()) > driveThreshold)
    {
        if(mainController.axis1.value() < 0)
        {
            robotDirection = backward; 
        }
        else
        {
            robotDiretion = forward;
        }
        rightMotors.spin(robotDirection, abs(mainController.axis1.value()), percent);
        leftMotors.spin(robotDirection, abs(mainController.axis1.value()), percent);   
    }
    
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
