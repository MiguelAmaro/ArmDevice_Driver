#include "scheduler.h"
#include <stdio.h>
#include "serialcomm.h"
#include "onboard_leds.h"
#include "motor.h"

//Non premptive scheduler
void scheduler(void){
	while(1){
		// Checks for characters and displays
		task_CheckForAndProcessSerialChars();
		// Start transmitter if it isn't already running

		task_scanForAndProcessIfMotorCommands(*(task_readRecievedChar()));
		
		
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
		
		task_StartTransmitter();
	} // End of Scheduler Loop
}
//----------------------------
// Scheduling Components
//----------------------------
void SysTick_Handler(void){
	printf((task_readRecievedChar()));
}
void Init_SysTick(void){
	SysTick->LOAD = 48000000L/16;
	NVIC_SetPriority (SysTick_IRQn, 3); // Set the interrupt priority
	SysTick->CTRL |=            2;       // Enable the SysTick interrupt
	SysTick->CTRL |=            5;       // Set the Clock and Enable the down counter
}

