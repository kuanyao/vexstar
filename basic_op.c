#include "basic_op.h"

void sendToWheelMotor(int speedVeritical, int speedHorizontal, int speedRotation) {
	motor[LeftFrontMotor]  = speedVeritical + speedHorizontal + speedRotation;
	motor[RightBackMotor]  = -1 * (speedVeritical + speedHorizontal) + speedRotation;
	motor[RightFrontMotor] = speedHorizontal - speedVeritical + speedRotation;
	motor[LeftBackMotor]   = speedVeritical - speedHorizontal + speedRotation;
}

void sendToClawMotor(int speed) {
	motor[ClawLeft] = -1 * speed;
	motor[ClawRight] = speed;
}

void sendToArmMotor(int speed) {
	motor[LiftUpperRight] = speed;
	motor[LiftUpperLeft] = speed;
	motor[LiftLowerLeft] = speed;
	motor[LiftLowerRight] = speed;
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
