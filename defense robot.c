#pragma config(Sensor, in6,    LiftPot,        sensorPotentiometer)
#pragma config(Sensor, in7,    SwingPot,       sensorPotentiometer)
#pragma config(Sensor, in8,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LeftEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  RightEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  Claw,           sensorDigitalOut)
#pragma config(Motor,  port2,           LeftFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightFrontDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LeftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           RightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Swing,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           Mogo,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftRearDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RightRearDrive, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

void LeftAutoStack();
int position = 0;
int height = 2100;
int distanceBackward = 0;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

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
task DrivePIDBackwards()
{
	int error = 0;
	int prevError = 0;
	int integral = 0;
	int derivative = 0;
	int speed;
	int kP = 1;
	int kI = 1;
	int kD = 1;
	
	error = distanceBackward - SensorValue[LeftEnc];
	prevError = distanceBackward - SensorValue[LeftEnc];
	
	while ( abs(error) > 10 )
	{
		error = distanceBackward - SensorValue[LeftEnc];
		integral = integral + error;
		if (error == 0)
		{
			integral = 0;
		}
		derivative = error - prevError;
		prevError = error;
		speed = error*kP + integral*kI + derivative*kD;
		motor[LeftFrontDrive] = speed;
		motor[RightFrontDrive] = speed;
		motor[LeftRearDrive] = speed;
		motor[RightRearDrive] = speed;
		wait1Msec(15);
	}
}

task autonomous()
{
	distanceBackward = 1000;
	startTask(DrivePIDBackwards);
}

void LeftAutoStack()
{
	int armHeight[6] = {2100, 2400, 2700, 3000, 3300, 3600};
	int grabHeight = 2100;

	for(int i = 0; i < 6; i++)
	{
		// line up arm with platform
		position = 0;
		wait1Msec(300);
		
		// lower arm
		height = grabHeight;
		wait1Msec(300);
		
		// close claw
		//SensorValue[Claw] = 1;

		// lift arm
		height = armHeight[i];
		wait1Msec(300);
		
		// swing arm to middle
		position = 1050;
		wait1Msec(300);
		
		// open claw
		//SensorValue[Claw] = 0;
	}

	return;
}

task liftPoint()
{
	int difference;

	while(true)
	{
		difference = abs(SensorValue[LiftPot] - height);
		if(SensorValue[LiftPot] > height)
		{
			motor[LeftLift] = -1 * (difference * 0.2);
			motor[RightLift] = -1 * (difference * 0.2);
			wait1Msec(20);
		}
		else
		{
			motor[LeftLift] = difference * 0.2;
			motor[RightLift] = difference * 0.2;
			wait1Msec(20);
		}
	}
	return;
}

task swingPoint()
{
	int difference;

	while(true)
	{
		difference = abs(SensorValue[SwingPot] - position);
		if(SensorValue[SwingPot] > position + 100)
		{
			motor[Swing] = -1 * (difference * .2);
			wait1Msec(20);
		}
		else if(SensorValue[SwingPot] < position - 100)
		{
			motor[Swing] = (difference *.2);
			wait1Msec(20);
		}
		else
		{
			motor[Swing] = 0;
			wait1Msec(20);
		}
	}
	return;
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	startTask(liftPoint);
	startTask(swingPoint);
	startTask(DrivePIDBackwards);

	// User control code here, inside the loop
	int y;
	int x;
	int threshhigh = 100;
	int threshlow = 20;
	while (true)
	{
		// make joystick move far enough before using values
		if(abs(vexRT[Ch3]) >= threshhigh)
		{
			y = vexRT[Ch3] * .8;
		}
		else if(abs(vexRT[Ch3]) <= threshlow)
		{
			y = 0;
		}
		else
		{
			y = vexRT[Ch3];
		}
		// make joystick move far enough before using values
		if(abs(vexRT[Ch1]) >= threshhigh)
		{
			x = vexRT[Ch1] * .8;
		}
		else if(abs(vexRT[Ch1]) <= threshlow)
		{
			x = 0;
		}

		else
		{
			x = vexRT[Ch1];
		}

		motor[LeftFrontDrive] = -x - y;
		motor[RightFrontDrive] = x - y;
		motor[LeftRearDrive] = -x - y;
		motor[RightRearDrive] = x - y;

		/*
		if(vexRT[Btn6U] == 1)
		{
		motor[LeftLift] = 127;
		motor[RightLift] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
		motor[LeftLift] = -127;
		motor[RightLift] = -127;
		}
		else
		{
		motor[LeftLift] = 0;
		motor[RightLift] = 0;
		}

		if(vexRT[Btn5U] == 1)
		{
		motor[Swing] = 127;
		}
		else if(vexRT[Btn5D] == 1)
		{
		motor[Swing] = -127;
		}
		else
		{
		motor[Swing] = 0;
		}
		*/

		if(vexRT[Btn8U] == 1)
		{
			motor[Mogo] = 127;
		}
		else if(vexRT[Btn8D] == 1)
		{
			motor[Mogo] = -127;
		}
		else
		{
			motor[Mogo] = 0;
		}

		if(vexRT[Btn7U] == 1)
		{
			SensorValue[Claw] = 1;
		}
		else if(vexRT[Btn7D] == 1)
		{
			SensorValue[Claw] = 0;
		}

		if(vexRT[Btn8L] == 1)
		{
			LeftAutoStack();
		}
	}
}