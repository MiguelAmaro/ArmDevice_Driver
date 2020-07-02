#include <MKL25Z4.h>

#include "systemMacros.h"
#include "port.h"
#include "onboardLeds.h"
#include <stdio.h>

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
	setLowPin(PIN01_LASERCTRL, PTC);
	
	return;
}

void laserDisable(void) {
	setHighPin(PIN01_LASERCTRL, PTC);
	
	return;
}

