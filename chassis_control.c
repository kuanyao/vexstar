#include "basic_op.h"

void subtle_movement_control() {
	if (vexRT[Btn8U] == 1 || vexRT[Btn8D] == 1 || vexRT[Btn8L] == 1 || vexRT[Btn8R] == 1) {
		if (vexRT[Btn8U] == 1) {
			sendToWheelMotor(WHEEL_MOTOR_SPEED / 2, 0, 0);
		} else if (vexRT[Btn8D] == 1) {
			sendToWheelMotor(-1 * WHEEL_MOTOR_SPEED / 2, 0, 0);
		} else if (vexRT[Btn8L] == 1) {
			sendToWheelMotor(0, -1 * WHEEL_MOTOR_SPEED / 2, 0);
		} else if (vexRT[Btn8R] == 1) {
			sendToWheelMotor(0, WHEEL_MOTOR_SPEED / 2, 0);
		}
		wait1Msec(PROGRESS_INCREMENT_DURATION);
	}
}

void subtle_rotation_control() {
	if (vexRT[Btn7L] == 1 || vexRT[Btn7R] == 1) {
		if (vexRT[Btn7L] == 1) {
			rotate_bot(-1 * ROTATE_MOTOR_SPEED / 2);
		} else {
			rotate_bot(ROTATE_MOTOR_SPEED / 2);
		}
		wait1Msec(PROGRESS_INCREMENT_DURATION);
	}
}

void subtle_claw_control() {
	if (vexRT[Btn7LXmtr2] == 1 || vexRT[Btn7RXmtr2] == 1) {
		if (vexRT[Btn7LXmtr2] == 1) {
			sendToClawMotor(-1 * CLAW_MOTOR_SPEED / 2);
		} else {
			sendToClawMotor(CLAW_MOTOR_SPEED / 2);
		}
		wait1Msec(PROGRESS_INCREMENT_DURATION);
	}
}

void subtle_arm_control() {
	if (vexRT[Btn8UXmtr2] == 1 || vexRT[Btn8DXmtr2] == 1) {
		if (vexRT[Btn8UXmtr2] == 1) {
			sendToLiftMotor(LIFT_MOTOR_SPEED / 2);
		} else {
			sendToLiftMotor(-1 * LIFT_MOTOR_SPEED / 3);
		}
		wait1Msec(PROGRESS_INCREMENT_DURATION);
	}
}

void subtle_controls() {
	subtle_arm_control();
	subtle_claw_control();
	subtle_rotation_control();
	subtle_movement_control();
}

task chassisControl() {
	int liftArmControlThreshold = 15;
	int clawControlThreshold = 10;
	int wheelControlThreshold = 15;

	while(true){
		if (trigger_autonomous_mode()) {
			doAutonumousMovement();
		}

		subtle_controls();

		int rotateDirection = 0;
		if (vexRT[Btn5D] == 1) {
			rotateDirection = -1;
		}
		else if (vexRT[Btn5U] == 1) {
			rotateDirection = 1;
		}

		int wheelStraightMovementInput = vexRT[Ch2];
		int wheelSideMovementInput = vexRT[Ch1];

		if (max(abs(wheelStraightMovementInput), abs(wheelSideMovementInput)) > wheelControlThreshold
			|| rotateDirection != 0) {
			sendToWheelMotor(wheelStraightMovementInput, wheelSideMovementInput, rotateDirection * ROTATE_MOTOR_SPEED);
		} else {
			stop_bot_movement();
		}

		int liftControlInput = vexRT[Ch2Xmtr2];
		int clawControlInput = vexRT[Ch4Xmtr2];
		if (abs(liftControlInput) > liftArmControlThreshold) {
			if (liftControlInput < 0) {
				liftControlInput /= 2;
			}
			sendToLiftMotor(liftControlInput);
		} else {
			sendToLiftMotor(0);
		}

		if (abs(clawControlInput) > clawControlThreshold) {
			sendToClawMotor(sgn(clawControlInput) * CLAW_MOTOR_SPEED);
		} else {
			sendToClawMotor(0);
		}
	}
}