#include "port.h"
#include "MKL25Z4.h" // Device header
#include "systemHelper.h"

void Enable_PortA(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	return;
}

void Enable_PortB(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	return;
}

void Enable_PortC(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	return;
}

void Enable_PortD(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;	
	
	return;
}

void Enable_PortE(void){
	//Clock Gate Access
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	return;
}

void configPin(uint8_t pin, PORT_Type* port, uint8_t mux) {
	port->PCR[pin] &= ~PORT_PCR_MUX_MASK; //Clear Bit Fields
	port->PCR[pin] |=  PORT_PCR_MUX(mux); //Configure PortB Pin00 as PWM not GPIO - Pulse     Pan
	
	return;
}

void setToOutputPin(uint32_t pin, GPIO_Type* port){
	port->PDDR |= MASK( pin );
	
	return;
}

void setToInputPin(uint32_t pin, GPIO_Type* port){
	port->PDDR &= ~MASK( pin );
	
	return;
}

void setHighPin(uint8_t pin, GPIO_Type* port){
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

