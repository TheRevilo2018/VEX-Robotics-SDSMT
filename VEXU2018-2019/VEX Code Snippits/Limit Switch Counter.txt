#include "robot-config.h"
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Limit Switch Counter
This program will instruct your robot to print a variable that keeps track of how many times the Limit Switch has been pressed.

Robot Configuration:
[Three Wire Port]    [Name]        [Type]           [Description]       
Brain Port A         Limit1        Limit Switch     Limit Switch Sensor 
----------------------------------------------------------------------------------------------------*/          

int main() {
    //Print to the screen that the program has started.
    Brain.Screen.print("User Program has Started.");
    
    //Make a variable called pressedCount to record how many times the limit switch has been pressed.
    int pressedCount = 0; 
    
    //Intially print the values of the pressed count. 
    Brain.Screen.printAt(1, 80, "The pressed count is %d", pressedCount);
    
    //Create an infinite loop so we record the data until the user manually ends the program.
    while(1) {        
        //Use an if statement to see if the program needs to wait for the limit switch to be released again.
        if(Limit1.pressing()) { //If the limit switch is pressed
            //...Use a while loop to wait until the limit switch is released.
        	//If the limit switch is pressed, then the program will wait here until it is release.
        	//Once the limit switch is released. We will add 1 to the pressedCount and then display it on the screen.     
        	while(Limit1.pressing()) { //While the limit switch is pressed...
        	//...do nothing but wait in an idle loop.
            	vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
        	} 
            //Once the limit switch is not pressed, the program will continue.
        	//Add 1 to the pressedCount.
        	pressedCount = pressedCount + 1;
            //Update the printed value of the pressed count on the screen.
            Brain.Screen.printAt(1, 80, "The pressed count is %d", pressedCount);
        }
    }
}