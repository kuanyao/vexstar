#ifndef __preset_op_h
#define __preset_op_h

void moveArmToHighFencePushPosition();
void moveArmToLowFenchPushPosition();
void dropArmToFloor();
void raiseArmToCeiling();

void openClawToPushPosition();
void openClawToWideGrabPosition();
void openClawToNarrowGrabPosition();
void closeClawToGrabObects();

void driveForward(float distance);
void driveBackward(float distance);
void driveTowardsRight(float distance);
void driveTowardsLeft(float distance);

void rotateClockwise(int degree);
void rotateCounterClockwise(int degree);

//wait for wheel, arm, claw command operation to finish
void sync();
//sync() plus a waiting period after sync.
void syncAndWait(int milliseconds);

#endif
