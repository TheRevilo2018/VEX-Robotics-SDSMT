#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <ctype.h>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>
#include "robot-config.h"
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
  bool holdMode = false;
  vex::directionType leftMotorDirection;
  vex::directionType rightMotorDirection;
  int loopDelay = 20;
  int debounceButtonY = 0;
  int turnThreshold = 10;
  int driveThreshold = 10;
  int leftMotorPercent = 0;
  int rightMotorPercent = 0;
  
  std::vector<vex::motor> motorVector = { leftMotor1, leftMotor2, leftMotor3, 
                                         rightMotor1, rightMotor2, rightMotor3 };
  std::vector<vex::motor> leftMotorVector = { leftMotor1, leftMotor2, leftMotor3 };
  std::vector<vex::motor> rightMotorVector = { rightMotor1,rightMotor2, rightMotor3 };
    
   /*
  rightMotor1.stop(vex::brakeType::brake);
  rightMotor2.stop(vex::brakeType::brake);
  rightMotor3.stop(vex::brakeType::brake);
  leftMotor1.stop(vex::brakeType::brake); 
  leftMotor2.stop(vex::brakeType::brake);
  leftMotor3.stop(vex::brakeType::brake);
    */
      rightMotor1.stop(vex::brakeType::coast);
  rightMotor2.stop(vex::brakeType::coast);
  rightMotor3.stop(vex::brakeType::coast);
  leftMotor1.stop(vex::brakeType::coast); 
  leftMotor2.stop(vex::brakeType::coast);
  leftMotor3.stop(vex::brakeType::coast);  

  while (1){
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    
    //settings checks
    if(mainController.ButtonY.pressing())
    {
        if(debounceButtonY > 0)
        {
            debounceButtonY -= loopDelay;
        }
        else
        {
            //call hold mode
            holdMode = !holdMode;
            debounceButtonY = 200;
        }
    }
      
      
    //set settings
    if(!holdMode)
    {
        
        setBrakeType(motorVector, vex::brakeType::brake);
        /*
        rightMotor1.setStopping(vex::brakeType::brake);
        rightMotor2.setStopping(vex::brakeType::brake);
        rightMotor3.setStopping(vex::brakeType::brake);
        leftMotor1.setStopping(vex::brakeType::brake);
        leftMotor2.setStopping(vex::brakeType::brake);
        leftMotor3.setStopping(vex::brakeType::brake);
        */
    }
    else
    {
        setBrakeType(motorVector, vex::brakeType::hold);
        /*
        rightMotor1.setStopping(vex::brakeType::hold);
        rightMotor2.setStopping(vex::brakeType::hold);
        rightMotor3.setStopping(vex::brakeType::hold);
        leftMotor1.setStopping(vex::brakeType::hold);
        leftMotor2.setStopping(vex::brakeType::hold);
        leftMotor3.setStopping(vex::brakeType::hold);
        */
    }
    
    // up/down is axis 3, left/right control is axis1;
   
    //if high enough values to move
    if(abs(mainController.Axis1.value()) > turnThreshold || abs(mainController.Axis3.value()) > driveThreshold)
    {
         Brain.Screen.print("Hello");
        leftMotorPercent = mainController.Axis3.value();
        rightMotorPercent = mainController.Axis3.value();
        
        
        if(mainController.Axis1.value()> 0)
        {
             leftMotorPercent += fabs(mainController.Axis1.value() / 4.0);
             rightMotorPercent -= fabs(mainController.Axis1.value() / 4.0);
        }
        else
        {
            leftMotorPercent -= fabs(mainController.Axis1.value() / 4.0);
            rightMotorPercent += fabs(mainController.Axis1.value() / 4.0);
        }
       
        
        if(leftMotorPercent > 0)
        {
            leftMotorDirection = forward;
        }
        else
        {
            leftMotorDirection = reverse;
        }
        if(rightMotorPercent > 0)
        {
            rightMotorDirection = forward;
        }
        else
        {
            rightMotorDirection = reverse;
        }
        
        //set percents to abs value of driection, capped at 100
        rightMotorPercent = std::min(100, abs(rightMotorPercent));
        leftMotorPercent = std::min(100, abs(leftMotorPercent));
        
        rightMotor1.spin(rightMotorDirection, rightMotorPercent, percent);
        rightMotor2.spin(rightMotorDirection, rightMotorPercent, percent);
        rightMotor3.spin(rightMotorDirection, rightMotorPercent, percent);
        leftMotor1.spin(leftMotorDirection, leftMotorPercent, percent); 
        leftMotor2.spin(leftMotorDirection, leftMotorPercent, percent);
        leftMotor3.spin(leftMotorDirection, leftMotorPercent, percent); 
        
    }
    else
    {
        rightMotor1.spin(rightMotorDirection, 0, percent);
        rightMotor2.spin(rightMotorDirection, 0, percent);
        rightMotor3.spin(rightMotorDirection, 0, percent);
        leftMotor1.spin(leftMotorDirection, 0, percent); 
        leftMotor2.spin(leftMotorDirection, 0, percent);
        leftMotor3.spin(leftMotorDirection, 0, percent);   
    }
    
    vex::task::sleep(loopDelay); //Sleep the task for a short amount of time to prevent wasted resources. 
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









//code declared in header file
void setBrakeType(std::vector<vex::motor>motorVector, vex::brakeType type)
{
	for(auto motor: motorVector)
	{
		motor.setStopping(type);
	}
}

void test()
{
	return;
}