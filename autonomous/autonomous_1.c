#include "../include/basic_op.h"
#include "../include/advanced_op.h"

/****************************************
1. move forward, lift arm, open claw
2. move back, rotate clockwise 135 degree,
3. move forward

****************************************/
void autonomousProgramOne() {
	rotateClockwise(50);
	sync();

	openClawoToWideGrabPosition();
	driveForward(50);
	syncAndWait(200);

	closeClawToGrabObects();
	sync();

	raiseArmToCeiling();
	driveForward(40);
	syncAndWait(200);

	rotateCounterClockwise(45);
	syncAndWait(200);

	driveForward(20);
	syncAndWait(200);

	openClawToWideGrabPosition();
	syncAndWait(100);
	//wait1Msec(500);
	driveBackward(10);
	syncAndWait(100);

	moveArmToLowFenchPushPosition();
	sync();
	moveArmToLowFenchPushPosition();
	openClawToPushPosition();
	driveForward(15);
	sync();
}
