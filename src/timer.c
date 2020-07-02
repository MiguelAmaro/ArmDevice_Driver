#include "MKL25Z4.h" // Device header

#include "timer.h"
#include "motor.h"
#include "systemHelper.h"
#include "math.h"

void Init_TPM0(uint16_t modulo, uint8_t prescaler){
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); //Clock Source set to MCGFLL System Option (set once for all TPMs)
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; //Enable clock access to TPM0
	
	//TPM0 Setup
	TPM0->SC &= ~TPM_SC_CMOD_MASK; //Disable the timer Counter to configure settings
	configAllChannels (TPM0, 0);
	TPM0->CNT = TPM_CNT_COUNT_MASK; 
	TPM0->SC |= TPM_SC_TOIE_MASK; //Enable timer interupt on TOF
	
	NVIC_SetPriority (TPM0_IRQn, 5);
	NVIC_EnableIRQ(TPM0_IRQn);

	startTPMCounter(TPM0, modulo, prescaler);
	
	return;
}

void Init_TPM1(uint16_t modulo, uint8_t prescaler){
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); //Clock Source set to MCGFLL System Option (set once for all TPMs)
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK; //Enable clock access to TPM1
	
	//TPM1 Setup
	TPM1->SC &= ~TPM_SC_CMOD_MASK; //Disable the timer Counter to configure settings
	configAllChannels (TPM1, 0);
	TPM1->CNT = TPM_CNT_COUNT_MASK;
	TPM1->SC |= TPM_SC_TOIE_MASK; //Enable timer interupt on TOF

	NVIC_SetPriority (TPM1_IRQn, 4);
	NVIC_EnableIRQ(TPM1_IRQn);

	startTPMCounter(TPM1, modulo, prescaler);
	
	return;
}


//************************************
//  COUNTER STUFF
//************************************
void startTPMCounter(TPM_Type* timer, uint16_t modulo, uint8_t prescaleFactor){
	if(modulo != 0 && modulo != 0) {
		timer->MOD =  modulo-1; //Modulo set 1500 for a 32 microsecond timer ( 48mHz/1500 = .032MHz)
		timer->SC |= TPM_SC_PS((uint8_t)(log2(prescaleFactor))); //Set the Prescaler
	}
	
		timer->SC |= TPM_SC_TOF_MASK; //Clear Overthrow Flag
		timer->SC |= TPM_SC_CMOD(1);  //Enable the timer Counter
	
	return;
}

void stopTPMCounter(TPM_Type* timer){
	timer->SC |=  TPM_SC_TOF_MASK;  //Clear Overthrow Flag
	timer->SC &= ~TPM_SC_CMOD_MASK; //Disable the timer Counter
	
	return;
}


//************************************
//  GENERAL TIMER STUFF
//************************************
void clearAllTimerFlags(TPM_Type* timer) {
	timer->SC |= TPM_SC_TOF_MASK;
	clearAllChannelFlags(timer);
	
	return;
}

uint8_t isFlaggedTimer(TPM_Type*timer) {
	
	return timer->SC & TPM_SC_TOF_MASK;  //Clear Overthrow Flag
}

//************************************
//  CHANNEL STUFF
//************************************
void configAllChannels(TPM_Type* timer, uint16_t dutyCycleCounterValue) {
	configChannel(0, timer, dutyCycleCounterValue);
	configChannel(1, timer, dutyCycleCounterValue);

	return;
}

void configChannel( uint8_t channel, TPM_Type* timer, uint16_t dutyCycleCounterValue) {
	channelDutyCycleCounterValue   = dutyCycleCounterValue; // useless
	timer->CONTROLS[channel].CnSC  = TPM_CnSC_MSB_MASK |  TPM_CnSC_ELSA_MASK ;
	timer->CONTROLS[channel].CnV   = dutyCycleCounterValue;

	return;
}

void enableChannel( uint8_t channel, TPM_Type* timer) {
	timer->CONTROLS[channel].CnSC  =  TPM_CnSC_MSB_MASK |  TPM_CnSC_ELSA_MASK ;
	timer->CONTROLS[channel].CnV   =  channelDutyCycleCounterValue; // useless
	
	return;
}

void disableChannel( uint8_t channel, TPM_Type* timer) {
	timer->CONTROLS[channel].CnSC  &=  ~(TPM_CnSC_MSA_MASK  | 
	                                     TPM_CnSC_MSB_MASK  |  
	                                     TPM_CnSC_ELSA_MASK |
	                                     TPM_CnSC_ELSB_MASK);                

	return;
}

uint8_t isFlaggedChannel(uint16_t channel, TPM_Type* timer) {
	
	return timer->CONTROLS[channel].CnSC & TPM_CnSC_CHF_MASK;
}

void clearAllChannelFlags(TPM_Type* timer) {
	clearChannelFlag(0, timer);
	clearChannelFlag(1, timer);
	
	return;
}

void clearChannelFlag(uint8_t channel, TPM_Type* timer) {
	timer->CONTROLS[channel].CnSC |= TPM_CnSC_CHF_MASK; // Clear Channel Flag; // Clear Channel Flag
	
	return;
}
