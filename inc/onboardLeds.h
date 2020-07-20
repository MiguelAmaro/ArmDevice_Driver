#ifndef _ONBOARDLED_H_
#define _ONBOARDLED_H_

#include "stdint.h"

void Init_OnboardLed(void);

void executeLightingProccesses(uint8_t cmd);
void onboardLEDToggle    (uint8_t redOn, uint8_t greenOn, uint8_t blueOn);
void onboardLEDAutoToggle(uint8_t redOn, uint8_t greenOn, uint8_t blueOn);
void laserEnable (void);
void laserDisable(void);

#endif

