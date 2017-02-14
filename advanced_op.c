#include "basic_op.h"

typedef enum {
	MovementTask = 0,
	ClawPositionTask = 1,
	ClawTighteningTask = 2,
	ArmPositionTask = 3,
	OrientationTask = 4
} TaskNames;

int _leftWheelEncoderTargetValue;
int _rightWheelEncoderTargetValue;
int _clawTargetPosition;
int _armTargetPosition;
int _orientationTarget;

bool _activeTaskList[10];

int __defaultWheelSpeed = 80;
int __defaultArmSpeed = 80;
int __defaultClawSpeed = 80;
int __defaultRotateSpeed = 60;

// maximum delta considered to be in position, this depends on potentiometer value 
// from 0 ~ 4096
int _CLAW_POSITION_THRESHOLD = 50;
int _ARM_POSITION_THRESHOLD = 50;
int _ORIENTATION_THRESHOLD = 20;
int _CLAW_SPEED_THRESHOLD = 0;
int _CLAW_CLOSED_POSITION = 500;

bool _isAllTaskDone() {
	for (int i=0;i<10;++i) {
		if (_activeTaskList[i]) {
			return false;
		}
	}
	return true;
}

void _completeMovementTask() {
	stopBotMovement();
	_activeTaskList[MovementTask] = false;
	_leftWheelEncoderTargetValue = 0;
	resetLeftWheelEncoder();
}

void _completeClawPositionTask() {
	stopClawMovement();
	_activeTaskList[ClawPositionTask] = false;
}

void _completeClawTighteningTask() {
	stopClawMovement();
	_activeTaskList[ClawTighteningTask] = false;
}

void _completeArmPositionTask() {
	stopArmMovement();
	_activeTaskList[ArmPositionTask] = false;
}

void _completeOrientationTask() {
	stopBotMovement();
	_activeTaskList[OrientationTask] = false;
}

void _ensureMovementTaskDone() {
	if (_activeTaskList[MovementTask]) {
		int leftWheelEncoder = getLeftWheelEncoderValue();
		if ((_leftWheelEncoderTargetValue > 0 && leftWheelEncoder > _leftWheelEncoderTargetValue) ||
			(_leftWheelEncoderTargetValue < 0 && leftWheelEncoder < _leftWheelEncoderTargetValue)) {
			_completeMovementTask();			
		}
	}
}

void _ensureClawPositionTaskDone() {
	if (_activeTaskList[ClawPositionTask]) {
		int clawPosition = getClawPosition();
		int delta = _clawTargetPosition - clawPosition;
		if (abs(delta) > _CLAW_POSITION_THRESHOLD) {
			int clawSpeed = __defaultClawSpeed;
			if (abs(delta) < 250) {
				clawSpeed /= 8;
			} else if (abs(delta) < 500) {
				clawSpeed /= 4;
			} else if (abs(delta) < 1000) {
				clawSpeed /= 2;
			}
			if (delta > 0) {
				openClaw(clawSpeed);
			} else {
				closeClaw(clawSpeed);
			}
		} else {
			_completeClawPositionTask();
		}	
	}
}

void _ensureClawTighteningTaskDone() {
	if (_activeTaskList[ClawTighteningTask]) {
		int clawSpeed = getClawSpeed();
		int clawPosition = getClawPosition();
		if (abs(clawSpeed) <= _CLAW_SPEED_THRESHOLD 
			|| abs(clawPosition - _CLAW_CLOSED_POSITION) < _CLAW_POSITION_THRESHOLD) {
			_completeClawTighteningTask();
		}
	}
}

void _ensureArmPositionTaskDone() {
	if (_activeTaskList[ArmPositionTask]) {
		int armPosition = getArmPosition();
		int delta = _armTargetPosition - armPosition;
		if (abs(delta) > _ARM_POSITION_THRESHOLD) {
			int armSpeed = delta > 0 ? __defaultArmSpeed : __defaultArmSpeed / 3;
			if (abs(delta < 500)) {
				armSpeed /= 3;
			} else if (abs(delta) < 1000) {
				armSpeed /= 2;
			}
			if (delta > 0) {
				liftArm(armSpeed);
			} else {
				dropArm(armSpeed);
			}
		} else {
			_completeArmPositionTask();
		}
	}
}

void _ensureOrientationTaskDone() {
	if (_activeTaskList[OrientationTask]) {
		int currentOrientation = getOrientation();
		int delta = _orientationTarget - currentOrientation;
		if (abs(delta) > _ORIENTATION_THRESHOLD) {
			int rotateSpeed = __defaultRotateSpeed;
			if (abs(delta) < 300) {
				rotateSpeed /= 4;
			} else if (abs(delta) < 600) {
				rotateSpeed /= 2;
			}
			if (delta > 0) {
				rotateClockwise(rotateSpeed);
			} else {
				rotateCounterClockwise(rotateSpeed);
			}
		} else {
			_completeOrientationTask();
		}
	}
}

void sync() {
	while (!isAllTaskDone()) {
		_ensureMovementTaskDone();
		_ensureClawPositionTaskDone();
		_ensureClawTighteningTaskDone();
		_ensureArmPositionTaskDone();
		_ensureOrientationTaskDone();

		wait1Msec(10);
	}	
}

void syncAndWait(int milliseconds) {
	sync();
	wait1Msec(milliseconds);
}