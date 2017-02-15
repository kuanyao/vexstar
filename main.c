#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  jumper1,        sensorTouch)
#pragma config(Sensor, dgtl2,  jumper2,        sensorTouch)
#pragma config(Sensor, dgtl7,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  ,               sensorQuadEncoder)
#pragma config(Motor,  port1,           ClawLeft,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LeftFrontMotor, tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           RightFrontMotor, tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           LeftBackMotor, tmotorVex393HighSpeed_MC29, openLoop, encoderPort, dgtl7)
#pragma config(Motor,  port5,           RigjtBackMotor, tmotorVex393HighSpeed_MC29, openLoop, encoderPort, dgtl9)
#pragma config(Motor,  port6,           ArmLiftLeftUpper, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           ArmLiftLeftLower, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           ArmLiftRightUpper, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           ArmLiftRightLower, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          ClawRight,     tmotorVex393_HBridge, openLoop, reversed)
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


#include "basic_op.c"
#include "advanced_op.c"

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

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

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
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
  startTask(chassiControl);
  startTask(armClawControl);

  while (true)
  {
    wait1Misc(10);
  }
}
