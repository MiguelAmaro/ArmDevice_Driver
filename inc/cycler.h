#ifndef CYCLER_H
#define CYCLER_H
#include "cycler.h"

#include "serialcomm.h"
#include "motor.h"
#include "onboardLeds.h"

//Non premptive scheduler
void cycler(void){
	
	while(1){
		// Checks for characters and displays
		serialcomm_CheckForAndProcessSerialChars();

		executeMotorProcesses    (*serialcomm_readReceivedChar());
		
		executeLightingProccesses(*serialcomm_readReceivedChar());
		
		serialcomm_clearReceivedChar();
		
		// Start transmitter if it isn't already running
		serialcomm_StartTransmitter();
	} // End of Scheduler Loop
}

#endif
