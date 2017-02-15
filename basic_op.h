#ifndef __basic_op_h
#define __basic_op_h

void sendToWheelMotor(int speedVeritical, int speedHorizontal, int speedRotation);
void rotateBot(int speed);
void stopBotMovement();

void openClaw(int speed);
void closeClaw(int speed);
void stopClawMovement();

void liftArm(int speed);
void dropArm(int speed);
void stopArmMovement();

void sendToClawMotor(int speed);
void sendToArmMotor(int speed);

#endif
