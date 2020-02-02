#include <MKL25Z4.h>
#include "scheduler.h"

#include <stdio.h>
#include "serialcomm.h"
#include "onboard_leds.h"
#include "motor.h"

int main (void) {
	Init_UART0(115200);
	Init_OnboardRGB_LEDs();
	Init_Systick();
	Init_PortB();
	Init_TPM0(0xFFFF, 0x07);
	
 	printf("\n\rPrintF: Starting Program!\n\r");
	Send_String((uint8_t*)"\n\rSendString: Hello, Master!\n\r");
	
	scheduler();
}

