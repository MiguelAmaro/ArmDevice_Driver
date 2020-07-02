#include "port.h"
#include "MKL25Z4.h" // Device header
#include "systemHelper.h"

void Init_PortA(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	configPin(PORTA, 12, TPM_CH_OUTPUT);
	configPin(PORTA, 13, TPM_CH_OUTPUT);
	
	return;
}

void Init_PortB(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	configPin(PORTB,  0, GPIO);
	configPin(PORTB,  1, GPIO);
	configPin(PORTB,  2, GPIO);
	configPin(PORTB,  3, GPIO);
	configPin(PORTB, 18, GPIO);
	configPin(PORTB, 19, GPIO);
	
	
	GPIOB->PDDR |= 0xc000f; //Pins 0 1 2 3 configured to output
	GPIOB->PSOR |= 0xc000f; //Set Pins 0 1 2 3 to HIGH
	
	return;
}

void Init_PortC(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	configPin(PORTC,  1, GPIO);
	
	GPIOC->PDDR |= 0xc0002; //Pins 0 1 2 3 configured to output
	GPIOC->PCOR |= 0xc0002; //Set Pins 0 1 2 3 to HIGH
	
	return;
}

void Init_PortD(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	configPin(PORTD, 1, GPIO);
	
	GPIOD->PDDR |= 0x00002; //Pins 0 1 2 3 configured to output
	GPIOD->PSOR |= 0x00002; //Set Pins 0 1 2 3 to HIGH
	
	return;
}

void Init_PortE(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	configPin(PORTE, 20, TPM_CH_OUTPUT);
	configPin(PORTE, 21, TPM_CH_OUTPUT);
	
	return;
}

void configPin(PORT_Type* port, uint8_t pin, uint8_t mux) {
	port->PCR[pin] &= ~PORT_PCR_MUX_MASK; //Clear Bit Fields
	port->PCR[pin] |=  PORT_PCR_MUX(mux); //Configure PortB Pin00 as PWM not GPIO - Pulse     Pan
	
	return;
}

void setHighPin( uint8_t pin, GPIO_Type* port){
	port->PSOR |= MASK( pin );
	
	return;
}

void setLowPin(uint8_t pin, GPIO_Type* port){
	port->PCOR |= MASK( pin );
	
	return;
}

void togglePin(uint8_t pin, GPIO_Type* port){
	port->PTOR |= MASK( pin );
	
	return;
}

