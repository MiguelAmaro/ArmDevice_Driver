#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "MKL25Z4.h" // Device header
#include "stdint.h"

// Pan/Tilt Pulse and Direction Pins
#define PAN_PTB_PIN00_PUL (0x001)
#define PAN_PTB_PIN01_DIR (0x002)

#define TILT_PTB_PIN03_PUL (0x004)
#define TILT_PTB_PIN04_DIR (0x008)

// Motor Movements
#define PAN_LEFT  ('A')
#define PAN_RIGHT ('B')
#define TILT_UP   ('C')
#define TILT_DOWN ('D')

// States
static uint8_t motorState = 0x00;
#define PAN_DIRECTION_REVERSED  0x01
#define TILT_DIRECTION_REVERSED 0x02

// Private

static void startTPM0Counter(uint16_t, uint32_t);
static void stopTPM0Counter (void);

// Public 
void Init_PortB(                                  void);
void Init_TPM0 (                    uint16_t, uint32_t);
void task_pulse(          uint32_t, uint16_t, uint32_t);
void task_changeDirection(uint32_t, uint16_t, uint32_t);
void scanAndProcessMotorCommands(unsigned char recievedChar);
void motorComponentStatusCheck(void);
static uint8_t g_PulseCmd = 0;

#endif

