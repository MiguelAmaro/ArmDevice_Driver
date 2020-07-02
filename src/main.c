#include <MKL25Z4.h>

#include "cycler.h"
#include "port.h"
#include "timer.h"
#include "serialcomm.h"
#include "motor.h"
#include "onboardLeds.h"
#include "systick.h"
#include "systemMacros.h"
#include "systemHelper.h" 
#include <stdio.h>

int main (void) {
	uint16_t TPM0_TimeModulo = 21000;
	uint16_t TPM1_TimeModulo = 21000;
	
	__disable_irq();
	
	Init_SysTick(1);
	Init_UART0(115200);
	
	Init_PortA();
	Init_PortB();
	Init_PortC();
	Init_PortD();
	Init_PortE();
	
	Init_TPM0(TPM0_TimeModulo, 1); //Param 2 Options: 1 2 4 8 16 32 64 128
	Init_TPM1(TPM1_TimeModulo, 1);
	
	//configChannel(1, TPM1, ( TPM1_TimeModulo * 0.5 ));
	
	__enable_irq();
	
	Send_String((uint8_t*)"\n\rSendString: Driver Initialization Complete!\n\r");
	
	cycler();
	
	END_OF_PROGRAM
}

//----------------------------
// INTERRUPT DERFENTIONS
//----------------------------
void SysTick_Handler(void){
	static volatile uint8_t ledState = 0;
	
	if(!ledState){
		onboardLEDToggle(0,1,0);
		ledState = 1;
	}
	else{
		onboardLEDToggle(0,0,0);
		ledState = 0;
	}	
	
	printf(" %d %d", 20, 2);
	
	return;
}

void TPM0_IRQHandler(void){	
	stopTPMCounter(TPM0);
	setHighPin(PIN00_PUL, GPIOB);

	return;
}

void TPM1_IRQHandler(void){
	stopTPMCounter(TPM1);
	setHighPin(PIN02_PUL, GPIOB);

	return;
}
