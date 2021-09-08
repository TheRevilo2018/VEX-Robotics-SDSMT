#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor rightFront = motor(PORT1, ratio18_1, true);
motor rightMid = motor(PORT2, ratio18_1, false);
motor rightBack = motor(PORT3, ratio18_1, true);
motor leftFront = motor(PORT11, ratio18_1, false);
motor leftMid = motor(PORT16, ratio18_1, true);
motor leftBack = motor(PORT20, ratio18_1, true);
inertial Inertial = inertial(PORT6);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}