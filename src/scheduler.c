#include "scheduler.h"
#include <stdio.h>
#include "serialcomm.h"
#include "onboard_leds.h"

void scheduler(void){
	uint8_t buffer[80], c, * bp;
	
	while(1){
		// non Blocking receive
		if(Q_Size(&RxQ)){ // check if characters have arrived
			c = Q_Dequeue(&RxQ);
			// Blocking transmit
			sprintf((char *) buffer, "You pressed %c\n\r", c);
			// Enqueue string
			bp = buffer;
		
			while (*bp != '\0') { 
				// copy characters up to null terminator
				while (Q_Full(&TxQ)); // wait for space to open up
			
				Q_Enqueue(&TxQ, *bp);
				bp++;
			}
		}
		// start transmitter if it isn't already running
		if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
			UART0->C2 |= UART0_C2_TIE(1);
		}
	}
}

