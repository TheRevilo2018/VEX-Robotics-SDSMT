#ifndef  _ROBOT-CONFIG_H__
#define _ROBOT-CONFIG_H__

using namespace vex;
vex::brain Brain;
vex::motor LeftMotor (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor RightMotor (vex::PORT10, vex::gearSetting::ratio18_1, true);

#endif
