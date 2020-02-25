#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)

//----------------------------
// Tasks
//----------------------------
void task_CheckForAndProcessSerialChars(void);
void task_StartTransmitter(void);
unsigned char* task_readRecievedChar(void);

//----------------------------
// Supporting Functions
//----------------------------
void Init_UART0 (uint32_t baud_rate);
void Send_String(uint8_t*       str);

uint32_t Rx_Chars_Available(void);
uint8_t	 Get_Rx_Char       (void);

// For Serial: Tx = transmit & Rx = recieve
extern queue_t transmitQ, recieveQ;
static uint8_t buffer[80], recievedChar, * bufferPtr;
#endif

