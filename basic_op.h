#ifndef __basic_op_h
#define __basic_op_h

void driveBot(int vericalSpeed, int horizontalSpeed, int rotateSpeed);
void stopBotMovement();

void openClaw(int speed);
void closeClaw(int speed);
void stopClawMovement();

void liftArm(int speed);
void dropArm(int speed);
void stopArm();

void sendToClawMotor(int speed);
void sendToArmMotor(int speed);

#endif
