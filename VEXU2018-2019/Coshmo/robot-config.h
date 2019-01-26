#ifndef  _ROBOTCONFIG_H__
#define _ROBOTCONFIG_H__

using namespace vex;
//initialization
vex::brain Brain;

vex::motor leftMotor1 (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor leftMotor2 (vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor leftMotor3 (vex::PORT3, vex::gearSetting::ratio18_1, false);

vex::motor rightMotor1 (vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor rightMotor2 (vex::PORT12, vex::gearSetting::ratio18_1, false);
vex::motor rightMotor3 (vex::PORT13, vex::gearSetting::ratio18_1, true);
vex::controller mainController = vex::controller();

//aliases
vex::directionType forward = vex::directionType::fwd;
vex::directionType reverse = vex::directionType::rev;

vex::velocityUnits percent = vex::velocityUnits::pct;
vex::velocityUnits revolutionsPerMinute = vex::velocityUnits::rpm;
vex::velocityUnits degreesPerSecond = vex::velocityUnits::dps;

vex::brakeType brake = vex::brakeType::brake;
vex::brakeType coast = vex::brakeType::coast;

vex::rotationUnits revolutions = vex::rotationUnits::rev;
vex::rotationUnits degrees = vex::rotationUnits::deg;

#endif
