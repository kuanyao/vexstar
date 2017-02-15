#include "basic_op.h"
#include "advanced_op.h"

/****************************************
1. move forward, lift arm, open claw
2. move back, rotate clockwise 135 degree,
3. move forward

****************************************/
void autonomousProgramOne() {
	driveForward(100);
	moveArmToHighFencePushPosition();
	openClawToPushPosition();
	syncAndWait(500);

	driveBackward(20);
	openClawToWideGrabPosition();
	syncAndWait(500);

	rotateClockwise(135);
	dropArmToFloor();
	syncAndWait(500);

	driveForward(50);
	syncAndWait(100);

	closeClawToGrabObects();
	syncAndWait(100);

	liftArmToCeiling();
	rotateCounterClockwise(90);
	syncAndWait(100);
}
