#ifndef __sensor_op_h
#define __sensor_op_h

int getLeftWheelEncoderValue();
int getRightWheelEncoderValue();
int getArmPosition();
int getClawPosition();
int getOrientation();

void resetLeftWheelEncoder();
void resetRightWheelEncoder();

#endif
