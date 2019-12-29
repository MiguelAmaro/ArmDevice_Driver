#include "scheduler.h"
#include <stdio.h>
#include "serialcomm.h"
#include "onboard_leds.h"

//Non premptive schedualer
void scheduler(void){
	while(1){
		// Checks for characters and displays
		task_CheckForAndProcessSerialChars();
		// Start transmitter if it isn't already running
		if(recievedChar == 'r'){
			printf((const*)recievedChar);
			task_ControlRGB_LEDs(1, 0, 0);
		}
		
		task_StartTransmitter();
	}
}

