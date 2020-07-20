#include <MKL25Z4.h>

#include "systemMacros.h"
#include "port.h"
#include "onboardLeds.h"
#include <stdio.h>

void Init_OnboardLed(){
	Enable_PortB();
	configPin(  RED_LED_POS, PORTB, GPIO);
	configPin(GREEN_LED_POS, PORTB, GPIO);
	
	setToOutputPin( RED_LED_POS | GREEN_LED_POS, PTB);
	setHighPin    ( RED_LED_POS | GREEN_LED_POS, PTB);
	
	Enable_PortC();
	configPin(LASERCTRL ,PORTC, GPIO);
	setToOutputPin( LASERCTRL, PTB);
	setHighPin    ( LASERCTRL, PTB);
	
	Enable_PortD();
	configPin(BLUE_LED_POS, PORTD, GPIO);
	setToOutputPin(BLUE_LED_POS, PTD);
	setHighPin    (BLUE_LED_POS, PTD);
	                                                                      
	return;
}

void executeLightingProccesses(uint8_t cmd){
		//Check for rgb LED commands
		if     (cmd == RED_ONBOARDLED_ON){
			onboardLEDToggle(1, 0, 0);
		}
		else if(cmd == ALL_ONBOARDLED_OFF){
			onboardLEDToggle(0, 0, 0);
		}
		
		//Check for rgb LED commands
		if     (cmd == LASER_ON){
			laserEnable();
		}
		else if(cmd == LASER_OFF){
			laserDisable();
		}
	return;
}

void onboardLEDToggle(uint8_t redOn, uint8_t greenOn, uint8_t blueOn) {
	if (  redOn) { setLowPin (  RED_LED_POS, PTB ); } 
	else         { setHighPin(  RED_LED_POS, PTB ); }
	
	if (greenOn) { setLowPin (GREEN_LED_POS, PTB ); }	
	else         { setHighPin(GREEN_LED_POS, PTB ); } 
	
	if ( blueOn) { setLowPin ( BLUE_LED_POS, PTD ); }	
	else         { setHighPin( BLUE_LED_POS, PTD ); }
	
	return;
}	

void onboardLEDAutoToggle(uint8_t redOn, uint8_t greenOn, uint8_t blueOn) {
	if (  redOn) { togglePin (  RED_LED_POS, PTB ); } 	
	if (greenOn) { togglePin (GREEN_LED_POS, PTB ); }	
	if ( blueOn) { togglePin ( BLUE_LED_POS, PTD ); }	
	
	return;
}

void laserEnable (void) {
	setLowPin( LASERCTRL, PTC);
	
	return;
}

void laserDisable(void) {
	setHighPin( LASERCTRL, PTC);
	
	return;
}

