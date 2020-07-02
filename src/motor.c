#include "motor.h"

#include "MKL25Z4.h" // Device header

#include "systemMacros.h"
#include "port.h"
#include "timer.h"
#include "stdlib.h"

//----------------------------
// Pan
//----------------------------
void pulseStepperMotorPan(void) {	
	setLowPin(PIN00_PUL, GPIOB);
	startTPMCounter(TPM0, 0, 0);
	
	return;
}

void setDirectionCWPan(void){
	setHighPin(PIN01_DIR, GPIOB);

	return;
}

void setDirectionCCWPan(void){
	setLowPin(PIN01_DIR, GPIOB);

	return;
}

//----------------------------
// Tilt
//----------------------------
void pulseStepperMotorTilt(void) {	
	setLowPin(PIN02_PUL, GPIOB);
	startTPMCounter(TPM1, 0, 0);
	
	return;
}

void setDirectionCWTilt(void){
	setHighPin(PIN03_DIR, GPIOB);

	return;
}

void setDirectionCCWTilt(void){
	setLowPin(PIN03_DIR, GPIOB);

	return;
}

//----------------------------
// General
//----------------------------
void switchDirection(void){
	togglePin(PIN01_DIR, GPIOB);

	return;
}

void executeMotorProcesses(uint8_t cmd) {
	switch(cmd){
		case PAN_CW:
			setDirectionCWPan();
			pulseStepperMotorPan();
			break;
		case PAN_CCW:
			setDirectionCCWPan();
			pulseStepperMotorPan();
			break;
		case TILT_CW:
			setDirectionCWTilt();
			pulseStepperMotorTilt();
			break;
		case TILT_CCW:
			setDirectionCCWTilt();
			pulseStepperMotorTilt();
			break;
		
		default:
			return;
	}
	
	return;
}

