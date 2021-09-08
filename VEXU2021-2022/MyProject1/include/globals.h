#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "../src/straightDriveBase/drive.h"
#include "vex.h"

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON E_CONTROLLER_DIGITAL_DOWN

//motor grouping declarations
extern std::vector<motor> wheelMotorVector;
extern std::vector<motor> leftWheelMotorVector;
extern std::vector<motor> rightWheelMotorVector;

//drive base class
extern FourWheelDrive* driveBase;

//pros declarations
extern  std::uint32_t now;

//globals
extern const int loopDelay;

#endif
