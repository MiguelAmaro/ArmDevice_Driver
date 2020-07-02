#include "systick.h"

void Init_SysTick(uint16_t divisor){
	SysTick->LOAD = 48000000L/divisor;
	
	NVIC_SetPriority (SysTick_IRQn, 3); // Set the interrupt priority
	NVIC_EnableIRQ(SysTick_IRQn);

	SysTick->CTRL |= 2;       // Enable the SysTick interrupt
	SysTick->CTRL |= 5;       // Set the Clock and Enable the down counter
	
	return;
}
