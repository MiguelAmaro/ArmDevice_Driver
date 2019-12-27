#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)

void Init_UART0 (uint32_t baud_rate);
void Send_String(uint8_t*       str);

uint32_t Rx_Chars_Available(void);
uint8_t	 Get_Rx_Char       (void);

extern Q_T TxQ, RxQ;


#endif

