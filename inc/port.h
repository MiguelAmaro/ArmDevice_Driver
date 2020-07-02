#ifndef _PORT_H_
#define _PORT_H_
#include "MKL25Z4.h" // Device header
#include "stdint.h"

#define GPIO (1)
#define TPM_CH_OUTPUT (3)

void Init_PortA(void);
void Init_PortB(void);
void Init_PortC(void);
void Init_PortD(void);
void Init_PortE(void);

void configPin(PORT_Type* port, uint8_t pin, uint8_t mux);
void setHighPin( uint8_t pin, GPIO_Type* port );
void setLowPin ( uint8_t pin, GPIO_Type* port );
void togglePin ( uint8_t pin, GPIO_Type* port );

#endif

