#include "globals.h"


//motor grouping declarations
std::vector<motor> wheelMotorVector = {leftFront, leftMid, leftBack, 
                                      rightFront, rightMid, rightBack};
std::vector<motor> leftWheelMotorVector = {leftFront, leftMid, leftBack };
std::vector<motor> rightWheelMotorVector = {rightFront, rightMid, rightBack};


//drive base class
FourWheelDrive* driveBase;

//globals
const int loopDelay = 20;
