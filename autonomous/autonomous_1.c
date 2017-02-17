#include "../include/basic_op.h"
#include "../include/advanced_op.h"

/****************************************
1. move forward, lift arm, open claw
2. move back, rotate clockwise 135 degree,
3. move forward

****************************************/
void autonomousProgramOne() {
	rotateClockwise(50);
	syncAndWait(200);

	openClawToWideGrabPosition();
	driveForward(45);
	syncAndWait(200);

	closeClawToGrabObects();

	raiseArmToCeiling();
	//driveForward(40);
	//syncAndWait(200);

	rotateCounterClockwise(50);
	syncAndWait(200);

	liftArm(LIFT_MOTOR_SPEED_THIRD);

	driveForward(70);
	syncAndWait(200);

	openClawToWideGrabPosition();
	liftArm(0);
	syncAndWait(1000);
	//wait1Msec(500);
	driveBackward(15);
	syncAndWait(100);

	//moveArmToLowFenchPushPosition();
	//sync();
	//moveArmToLowFenchPushPosition();
	openClawToPushPosition();
	driveTowardsLeft(25);

	syncAndWait(200);

	driveForward(15);
	syncAndWait(200);
}
