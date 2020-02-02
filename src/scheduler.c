#include "scheduler.h"
#include <stdio.h>
#include "serialcomm.h"
#include "onboard_leds.h"
#include "motor.h"

//Non premptive schedualer
void scheduler(void){
	while(1){
		// Checks for characters and displays
		task_CheckForAndProcessSerialChars();
		// Start transmitter if it isn't already running

		scanAndProcessMotorCommands(*(task_readRecievedChar()));
		
		
		//Check for rgb LED commands
		if     (*(task_readRecievedChar()) == 'r'){
			task_ControlRGB_LEDs(1, 0, 0);
		}
		if     (*(task_readRecievedChar()) == 'g'){
			task_ControlRGB_LEDs(0, 1, 0);
		}
		else if(*(task_readRecievedChar()) == 'b'){
			task_ControlRGB_LEDs(0, 0, 1);
		} 
		else if(*(task_readRecievedChar()) == 'o'){
			task_ControlRGB_LEDs(0, 0, 0);
		}
		
		if(SysTick->CTRL & 0x10000){
			printf(task_readRecievedChar());
		}
		
		task_StartTransmitter();
	} // End of Scheduler Loop
}
//----------------------------
// Schedualing Components
//----------------------------
void Systic_Handler(void){

}
void Init_Systick(void){
	SysTick->LOAD = 48000000 - 1;
	SysTick->CTRL =        5    ;
}

