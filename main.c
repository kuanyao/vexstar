#pragma config(Sensor, in1,    Gyro,           sensorGyro)
#pragma config(Sensor, in2,    ArmPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    ClawPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  Jumper1,        sensorTouch)
#pragma config(Sensor, dgtl2,  Jumper2,        sensorTouch)
#pragma config(Sensor, dgtl3,  Jumper3,        sensorTouch)
#pragma config(Sensor, dgtl4,  Jumper4,        sensorTouch)
#pragma config(Sensor, dgtl5,  Jumper5,        sensorTouch)
#pragma config(Sensor, dgtl6,  Jumper6,        sensorTouch)
#pragma config(Sensor, dgtl11, RightWheelEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           ClawLeft,      tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           LeftBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LeftFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           RightFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LiftUpperLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LiftLowerLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LiftUpperRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LiftLowerRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          ClawRight,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("debugStream")
#pragma DebuggerWindows("vexCompetitionControl")

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

#define CLAW_MOTOR_SPEED 85
#define ROTATE_MOTOR_SPEED 40
#define ROTATE_MOTOR_SPEED_HALF 20
#define LIFT_MOTOR_SPEED 120
#define LIFT_MOTOR_SPEED_HALF 40
#define LIFT_MOTOR_SPEED_THIRD 30
#define WHEEL_MOTOR_SPEED 60

#define CLAW_POSITIONING_THRESHOLD 20
#define ARM_POSITIONING_THRESHOLD 20
#define CLAW_STOPPING_THRESHOLD 5
#define ORIENTATION_THRESHOLD 10

#define CLAW_CLOSED_POSITION 1100
#define CLAW_WILD_OPEN_POSITION 1970
#define CLAW_NARROW_OPEN_POSITION 1780
#define CLAW_OPEN_TO_PUSH_POSITION 2500

#define ARM_FLOOR_POSITION 3000
#define ARM_BELOW_FENCE_POSITION 2300
#define ARM_CEILING_POSITION 1090
#define ARM_HIGH_FENCE_POSITION 1215
//#define ARM_LOW_FENCE_POSITION 1688
#define ARM_LOW_FENCE_POSITION 1190

#define DISTANCE_TO_ENCODER_VALUE_BASE_FACTOR 10.5

#define PROGRESS_INCREMENT_DURATION 80

#include "lib/basic_op.c"
#include "lib/advanced_op.c"
#include "lib/sensor_op.c"
#include "lib/chassis_control.c"
#include "lib/armclaw_control.c"
#include "autonomous/autonomous_1.c"
#include "autonomous/autonomous_2.c"
#include "autonomous/autonomous_testing.c"

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
  resetGyroSensor();
  resetRightWheelEncoder();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*---------------------------------------------------------------------------*/

void runAutonomous(bool withSlewControl) {
  writeDebugStreamLine("entering into autonomous now");
  if (withSlewControl) {
    startTask(MotorAccelerateSlewRateTask);
  }

  int jumperSetting = getJumperSetting();
  if (jumperSetting == 1) {
    autonomousProgramOne();
  } else if (jumperSetting == 2) {
    autonomousProgramTwo();
  } else if (jumperSetting == 3) {

  } else if (jumperSetting == 4) {

  } else if (jumperSetting == 5) {

  } else if (jumperSetting == 6) {

  }

  signalAutonCompleted();
}

task triggerAutonomous() {
  int jumperSetting = getJumperSetting();
  if (jumperSetting == 1) {
    autonomousProgramOne();
  } else if (jumperSetting == 2) {
    autonomousProgramTwo();
  } else if (jumperSetting == 3) {
    autonomousProgramTesting();

  } else if (jumperSetting == 4) {

  } else if (jumperSetting == 5) {

  } else if (jumperSetting == 6) {

  }

  signalAutonCompleted();
}

task autonomous()
{
  runAutonomous(true);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  startTask(MotorAccelerateSlewRateTask);
  startTask(chassisControl);
  startTask(armClawControl);

  while (true)
  {
    //checkAutonomous();
  	printSensorValuesToDebugWindow();
    wait(1);
  }
}
