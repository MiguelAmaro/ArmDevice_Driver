#ifndef ONBOARDLEDS_H
#define ONBOARDLEDS_H

#include <MKL25Z4.h>

// Freedom KL25Z LEDs
#define RED_LED_POS   (18)  // on port B
#define GREEN_LED_POS (19)  // on port B
#define BLUE_LED_POS  (1)   // on port D

#define MASK(x) (1UL << (x))

// function prototypes
void Init_OnboardRGB_LEDs(void);
void task_ControlRGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);

#endif

