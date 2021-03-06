#include "../include/basic_op.h"
#include "slew_control.c"

task triggerAutonomous();
void runAutonomous(bool withSlewControl);

bool _autonStarted = false;

void signalAutonCompleted() {
	writeDebugStreamLine("signal auton off");
	_autonStarted = false;
}

void checkAutonomous() {
	if (vexRT[Btn6D] == 1 && vexRT[Btn6U] == 1) {
		writeDebugStreamLine("try to trigger auton");
		if (!_autonStarted) {
			writeDebugStreamLine("starting auton");
			startTask(triggerAutonomous);
			//runAutonomous(false);
			_autonStarted = true;
		}
	} else if (vexRT[Btn6D] == 1 && vexRT[Btn6U] == 0) {
		writeDebugStreamLine("auton off");
		stopTask(triggerAutonomous);
		_autonStarted = false;
	}
}

void sendToWheelMotor(int speedVeritical, int speedHorizontal, int speedRotation) {
	// motor[LeftFrontMotor]  = speedVeritical + speedHorizontal + speedRotation;
	// motor[RightBackMotor]  = -1 * (speedVeritical + speedHorizontal) + speedRotation;
	// motor[RightFrontMotor] = speedHorizontal - speedVeritical + speedRotation;
	// motor[LeftBackMotor]   = speedVeritical - speedHorizontal + speedRotation;
	motorReq[LeftFrontMotor]  = speedVeritical + speedHorizontal + speedRotation;
	motorReq[RightBackMotor]  = -1 * (speedVeritical + speedHorizontal) + speedRotation;
	//motorReq[RightFrontMotor] = round((speedHorizontal - speedVeritical + speedRotation) * 0.9);
	motorReq[RightFrontMotor] = speedHorizontal - speedVeritical + speedRotation;
	motorReq[LeftBackMotor]   = speedVeritical - speedHorizontal + speedRotation;
}

void sendToClawMotor(int speed) {
	// motor[ClawLeft] = speed;
	// motor[ClawRight] = speed;
	motorReq[ClawLeft] = speed;
	motorReq[ClawRight] = speed;
}

void sendToArmMotor(int speed) {
	// motor[LiftUpperRight] = speed;
	// motor[LiftUpperLeft] = speed;
	// motor[LiftLowerLeft] = speed;
	// motor[LiftLowerRight] = speed;
	motorReq[LiftUpperRight] = speed;
	motorReq[LiftUpperLeft] = speed;
	motorReq[LiftLowerLeft] = speed;
	motorReq[LiftLowerRight] = speed;
}

void stopBotMovement() {
	sendToWheelMotor(0, 0, 0);
}

void rotateBot(int speed) {
	sendToWheelMotor(0, 0, speed);
}

void openClaw(int speed) {
	sendToClawMotor(-1 * speed);
}

void closeClaw(int speed) {
	sendToClawMotor(speed);
}

void stopClawMovement() {
	sendToClawMotor(0);
}

void liftArm(int speed) {
	sendToArmMotor(speed);
}

void dropArm(int speed) {
	sendToArmMotor(-1 * speed);
}

void stopArmMovement() {
	sendToArmMotor(0);
}

int max(int a, int b) {
	return a > b ? a : b;
}
