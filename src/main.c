#include <MKL25Z4.h>
#include "scheduler.h"

#include <stdio.h>
#include "serialcomm.h"

int main (void) {
	Init_UART0(115200);
	
 	printf("\n\rPrintF: Starting Program!\n\r");
	Send_String((uint8_t*)"\n\rSendString: Hello, Maseter!\n\r");

	scheduler();
}

