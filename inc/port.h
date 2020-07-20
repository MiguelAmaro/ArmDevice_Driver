#ifndef _PORT_H_
#define _PORT_H_
#include "MKL25Z4.h" // Device header
#include "stdint.h"

#define GPIO (1)
#define TPM_CH_OUTPUT (3)

void Enable_PortA(void);
void Enable_PortB(void);
void Enable_PortC(void);
void Enable_PortD(void);
void Enable_PortE(void);

void configPin(uint8_t pin, PORT_Type* port, uint8_t mux);
void setToOutputPin( uint32_t pin, GPIO_Type* port);
void setToInputPin ( uint32_t pin, GPIO_Type* port);
void setHighPin( uint8_t pin, GPIO_Type* port );
void setLowPin ( uint8_t pin, GPIO_Type* port );
void togglePin ( uint8_t pin, GPIO_Type* port );

#endif

