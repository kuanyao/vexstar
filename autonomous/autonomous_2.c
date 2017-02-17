#include "../include/basic_op.h"
#include "../include/advanced_op.h"

/****************************************
1. move forward, lift arm, open claw
2. move back, rotate clockwise 135 degree,
3. move forward

****************************************/
void autonomousProgramTwo() {
	raiseArmBelowFence();
	openClawToNarrowGrabPosition();
	//syncAndWait(100);
	wait1Msec(1200);
	rotateCounterClockwise(90);
	syncAndWait(100);

	dropArmToFloor();
	driveForward(40);
	syncAndWait(100);

	closeClawToGrabObects();
	syncAndWait(100);

	raiseArmToCeiling();
	rotateClockwise(90);
	syncAndWait(200);

	liftArm(30);

	driveForward(100);
	syncAndWait(100);

	openClawToNarrowGrabPosition();
	wait1Msec(1000);
	driveBackward(20);
	syncAndWait(200);

	rotateClockwise(10);
	syncAndWait(100);

	driveTowardsRight(40);
	openClawToPushPosition();
	//raiseArmToLowFencePosition();
	//moveArmToLowFenchPushPosition();
	syncAndWait(100);
	dropArm(20);

	driveForward(20);
	syncAndWait(200);
}
