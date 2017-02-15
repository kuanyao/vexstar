int getLeftWheelEncoderValue(){
	return SensorValue[LeftWheelEncoder];
}

int getRightWheelEncoderValue() {
	return SensorValue[RightWheelEncoder];
}

int getArmPosition() {
	return SensorValue[ArmPotentiometer];
}

int getClawPosition() {
	return SensorValue[ClawPotentiometer];
}

int getOrientation() {
	return SensorValue[Gyro];
}

void resetLeftWheelEncoder(){
	SensorValue[LeftWheelEncoder] = 0;
}

void resetRightWheelEncoder() {
	SensorValue[RightWheelEncoder] = 0;
}
