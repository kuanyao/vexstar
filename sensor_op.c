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

int getJumperSetting() {
	int jumperSetting = SensorValue[Jumper1] + SensorValue[Jumper2] + SensorValue[Jumper3] + SensorValue[Jumper4] + SensorValue[Jumper5];
	return jumperSetting;
}