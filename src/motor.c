#include "motor.h"

#include "MKL25Z4.h" // Device header

#include "systemMacros.h"
#include "port.h"
#include "timer.h"
#include "stdlib.h"

void Init_MotorController(void) {
	Enable_PortB();
	
	configPin(  PAN_PUL, PORTB, GPIO);
	configPin(  PAN_DIR, PORTB, GPIO);
	configPin( TILT_PUL, PORTB, GPIO);
	configPin( TILT_DIR, PORTB, GPIO);
	
	setToOutputPin( PAN_PUL | PAN_DIR | TILT_PUL | TILT_DIR, PTB);
	setHighPin    ( PAN_PUL | PAN_DIR | TILT_PUL | TILT_DIR, PTB);
	
	return;
}

//----------------------------
// Pan
//----------------------------
void pulseStepperMotorPan(void) {	
	setLowPin(PAN_PUL, GPIOB);
	startTPMCounter(TPM0, 0, 0);
	
	return;
}

void setDirectionCWPan(void){
	setHighPin(PAN_DIR, GPIOB);

	return;
}

void setDirectionCCWPan(void){
	setLowPin(PAN_DIR, GPIOB);

	return;
}

//----------------------------
// Tilt
//----------------------------
void pulseStepperMotorTilt(void) {	
	setLowPin(TILT_PUL, GPIOB);
	startTPMCounter(TPM1, 0, 0);
	
	return;
}

void setDirectionCWTilt(void){
	setHighPin(TILT_DIR, GPIOB);

	return;
}

void setDirectionCCWTilt(void){
	setLowPin(TILT_DIR, GPIOB);

	return;
}

//----------------------------
// General
//----------------------------
void switchDirection(void){
	togglePin(PAN_DIR, GPIOB);

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

