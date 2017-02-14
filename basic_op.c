#include "basic_op.h"

void driveBot(int vericalSpeed, int horizontalSpeed, int rotateSpeed) {
	motor[leftFront]  = speedVeritical + speedHorizontal + speedRotation;
	motor[rightBack]  = -1 * (speedVeritical + speedHorizontal) + speedRotation;
	motor[rightFront] = speedHorizontal - speedVeritical + speedRotation;
	motor[leftBack]   = speedVeritical - speedHorizontal + speedRotation;
}

void stopBotMovement() {
	driveBot(0, 0, 0);
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

void stopArm() {
	sendToArmMotor(0);
}

void sendToClawMotor(int speed) {
	motor[clawLeft] = -1 * speed;
	motor[clawRight] = speed;
}

void sendToArmMotor(int speed) {
	motor[liftMotor1] = speed;
	motor[liftMotor2] = speed;
	motor[liftMotor3] = speed;
	motor[liftMotor4] = speed;
}