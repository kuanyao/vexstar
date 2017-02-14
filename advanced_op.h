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

void driveForward(int distance);
void driveBackward(int distance);
void driveTowardsRight(int distance);
void driveTowardsLeft(int distance);
void stopBotMovement();

void rotateClockwise(int degress);
void rotateCounterClockwise(int degress);

void setWheelMotorDefaultSpeed(int speed);
void setArmMotorDefaultSpeed(int speed);
void setClawMotorDefaultSpeed(int speed);
void setRotationDefaultSpeed(int speed);

//wait for wheel, arm, claw command operation to finish
void sync();
//sync() plus a waiting period after sync.
void syncAndWait(int milliseconds);

#endif
