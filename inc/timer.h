#ifndef _TIMER_H_
#define _TIMER_H_

#include "MKL25Z4.h" // Device header

#define CLOCKSRCFEQUENCY (48000000)

extern uint16_t TPM1_Modulo;
static uint16_t channelDutyCycleCounterValue;

struct {
	uint8_t process;
	int remainingTime;
} typedef timerState_t;

// Timer
void Init_TPM0         (uint16_t modulo, uint8_t prescaler);
void Init_TPM1         (uint16_t modulo, uint8_t prescaler);
void clearAllTimerFlags(TPM_Type* timer);
void startTPMCounter   (TPM_Type* timer, uint16_t modulo, uint8_t prescaler);
void stopTPMCounter    (TPM_Type* timer                                    );


// Channel
void configChannel    (uint8_t channel, TPM_Type* timer, uint16_t dutyCycleCounterValue);
void configAllChannels(                 TPM_Type* timer, uint16_t dutyCycleCounterValue);
void enableChannel    (uint8_t channel, TPM_Type* timer);
void disableChannel   (uint8_t channel, TPM_Type* timer);

uint8_t isFlagThrownChannel(uint16_t channel, TPM_Type* timer);

void clearChannelFlag    (uint8_t channel, TPM_Type* timer);
void clearAllChannelFlags(                 TPM_Type* timer);
#endif

