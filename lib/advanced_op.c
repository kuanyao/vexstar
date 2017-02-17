#include "../include/basic_op.h"
#include "../include/sensor_op.h"
#include "../include/advanced_op.h"

typedef enum {
	MovementTask = 0,
	ClawPositionTask = 1,
	ClawTighteningTask = 2,
	ArmPositionTask = 3,
	OrientationTask = 4
} TaskNames;

int _rightWheelEncoderTargetValue;
int _clawTargetPosition;
int _armTargetPosition;
int _orientationTarget;
int _lastClawPosition;

bool _activeTaskList[10];

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
	_rightWheelEncoderTargetValue = 0;
	resetRightWheelEncoder();
}

void _completeClawPositionTask() {
	stopClawMovement();
	_activeTaskList[ClawPositionTask] = false;
}

void _completeClawTighteningTask() {
	stopClawMovement();
	_lastClawPosition = 0;
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
		int leftWheelEncoder = getRightWheelEncoderValue();
		if ((_rightWheelEncoderTargetValue > 0 && leftWheelEncoder > _rightWheelEncoderTargetValue) ||
			(_rightWheelEncoderTargetValue < 0 && leftWheelEncoder < _rightWheelEncoderTargetValue)) {
			_completeMovementTask();
		}
	}
}

void _ensureClawPositionTaskDone() {
	if (_activeTaskList[ClawPositionTask]) {
		int clawPosition = getClawPosition();
		int delta = _clawTargetPosition - clawPosition;
		if (abs(delta) > CLAW_POSITIONING_THRESHOLD) {
			int clawSpeed = CLAW_MOTOR_SPEED;
			if (abs(delta) < 50) {
				clawSpeed /= 4;
			} else if (abs(delta) < 100) {
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

bool _isClawMovementStopped() {
	int clawPosition = getClawPosition();
	int oldPosition = _lastClawPosition;
	_lastClawPosition = clawPosition;
	bool isMoving = (abs(oldPosition - clawPosition) <= CLAW_STOPPING_THRESHOLD);
	wait1Msec(200);
	writeDebugStreamLine("clawPosition: %d, last position %d, isMoving %d", clawPosition, oldPosition, isMoving);
	return isMoving;
}

void _ensureClawTighteningTaskDone() {
	if (_activeTaskList[ClawTighteningTask]) {
		int clawPosition = getClawPosition();
		if (_isClawMovementStopped()
			|| abs(clawPosition - CLAW_CLOSED_POSITION) < CLAW_POSITIONING_THRESHOLD) {
			wait1Msec(200);
			_completeClawTighteningTask();
		}
	}
}

void _ensureArmPositionTaskDone() {
	if (_activeTaskList[ArmPositionTask]) {
		int armPosition = getArmPosition();
		int delta = armPosition - _armTargetPosition;
		if (abs(delta) > ARM_POSITIONING_THRESHOLD) {
			//delta > 0 means we need lift, otherwise drop
			int armSpeed = delta > 0 ? LIFT_MOTOR_SPEED : LIFT_MOTOR_SPEED * 0.25;
			// if (abs(delta) < 300) {
			// 	armSpeed *= 0.8;
			// } 
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
		int delta = currentOrientation - _orientationTarget;
		if (abs(delta) > ORIENTATION_THRESHOLD) {
			int rotateSpeed = ROTATE_MOTOR_SPEED;
			if (abs(delta) <= 250) {
				rotateSpeed = ROTATE_MOTOR_SPEED_HALF;
			}
			//writeDebugStreamLine("delta = %d ,set rotation speed to %d", delta, rotateSpeed);
			rotateBot(sgn(delta) * rotateSpeed);
		} else {
			writeDebugStreamLine("complete rotation task, current position = %d, delta = %d", currentOrientation, delta);
			_completeOrientationTask();
		}
	}
}

void sync() {
	while (!_isAllTaskDone()) {
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

void moveArmToHighFencePushPosition() {
	_activeTaskList[ArmPositionTask] = true;
	_armTargetPosition = ARM_HIGH_FENCE_POSITION;
}

void moveArmToLowFenchPushPosition() {
	_activeTaskList[ArmPositionTask] = true;
	_armTargetPosition = ARM_LOW_FENCE_POSITION;
}

void dropArmToFloor() {
	_activeTaskList[ArmPositionTask] = true;
	_armTargetPosition = ARM_FLOOR_POSITION;
}

void raiseArmToCeiling() {
	_activeTaskList[ArmPositionTask] = true;
	_armTargetPosition = ARM_CEILING_POSITION;
}

void raiseArmBelowFence() {
	_activeTaskList[ArmPositionTask] = true;
	_armTargetPosition = ARM_BELOW_FENCE_POSITION;
}

void openClawToPushPosition() {
	_activeTaskList[ClawPositionTask] = true;
	_clawTargetPosition = CLAW_OPEN_TO_PUSH_POSITION;
}

void openClawToWideGrabPosition() {
	_activeTaskList[ClawPositionTask] = true;
	_clawTargetPosition = CLAW_WILD_OPEN_POSITION;
}

void openClawToNarrowGrabPosition() {
	_activeTaskList[ClawPositionTask] = true;
	_clawTargetPosition = CLAW_NARROW_OPEN_POSITION;
}

void closeClawToGrabObects() {
	_activeTaskList[ClawTighteningTask] = true;
	_lastClawPosition = 0;
	closeClaw(CLAW_MOTOR_SPEED);
	writeDebugStreamLine("closing claw at speed %d", CLAW_MOTOR_SPEED);
	// closeClaw(80);
	// wait1Msec(1300);
	// stopClawMovement();
}

int _convertToEncoderValueFromDistance(float distance) {
	return distance * DISTANCE_TO_ENCODER_VALUE_BASE_FACTOR;
}

void driveForward(float distance) {
	resetRightWheelEncoder();
	_activeTaskList[MovementTask] = true;
	sendToWheelMotor(WHEEL_MOTOR_SPEED, 0, 0);

	int encoderValue = _convertToEncoderValueFromDistance(distance);
	_rightWheelEncoderTargetValue = -1 * encoderValue;
}

void driveBackward(float distance) {
	resetRightWheelEncoder();
	_activeTaskList[MovementTask] = true;
	sendToWheelMotor(-1 * WHEEL_MOTOR_SPEED, 0, 0);

	int encoderValue = _convertToEncoderValueFromDistance(distance);
	_rightWheelEncoderTargetValue = encoderValue;
}

void driveTowardsRight(float distance) {
	resetRightWheelEncoder();
	_activeTaskList[MovementTask] = true;
	sendToWheelMotor(0, WHEEL_MOTOR_SPEED, 0);

	int encoderValue = _convertToEncoderValueFromDistance(distance);
	_rightWheelEncoderTargetValue = -1 * encoderValue;
}

void driveTowardsLeft(float distance) {
	resetRightWheelEncoder();
	_activeTaskList[MovementTask] = true;
	sendToWheelMotor(0, -1 * WHEEL_MOTOR_SPEED, 0);

	int encoderValue = _convertToEncoderValueFromDistance(distance);
	_rightWheelEncoderTargetValue = encoderValue;
}

void rotateClockwise(int degree) {
	degree -= 5;
	int currentSetting = SensorValue[Gyro];
	_orientationTarget = currentSetting - 10 * degree;
	_activeTaskList[OrientationTask] = true;
}

void rotateCounterClockwise(int degree) {
	degree -= 5;
	int currentSetting = SensorValue[Gyro];
	_orientationTarget = 10 * degree + currentSetting;
	_activeTaskList[OrientationTask] = true;
}
