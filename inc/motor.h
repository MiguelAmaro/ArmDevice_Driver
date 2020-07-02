#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stdint.h"

void switchDirection  (void);
void pulseStepperMotorPan(void);
void setDirectionCWPan   (void);
void setDirectionCCWPan  (void);
void pulseStepperMotorTilt(void);
void setDirectionCWTilt   (void);
void setDirectionCCWTilt  (void);
void executeMotorProcesses(uint8_t cmd);

#endif

