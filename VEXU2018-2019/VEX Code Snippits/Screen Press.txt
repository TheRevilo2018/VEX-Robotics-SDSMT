#include "robot-config.h"
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Screen Press
This program instructs the robot to draw a circle on the brain where ever a user presses the screen.

----------------------------------------------------------------------------------------------------*/

int main() {   
    //Create an infinite loop to record data until the user manually ends the program.
    while(1) {         
        //Check to see if the brain has been pressed.
        if(Brain.Screen.pressing()) { //If the Brain is pressed...
            //...Clear the screen of any circles that were on the screen from a previous touch.
            Brain.Screen.clearScreen();            
            //Draw a circle with the origin being the user's touch locations.
            Brain.Screen.drawCircle(Brain.Screen.xPosition(), Brain.Screen.yPosition(), 50);
        }
    }
}