#include "motor.h"
#include "MKL25Z4.h"                    // Device header


void Init_TPM0(uint16_t modulo, uint32_t prescaler){
	__disable_irq();
	SIM->SOPT2 |= 0x1000000; //Clock Source set to MCGFLL System Option (set once for all TPMs)
	SIM->SCGC6 |= 0x1000000; //Enable clock access to TPM0
	
	//TPM0 Setup
	TPM0->SC &=      ~0x08; //Disable the timer Counter to configure settings
	TPM0->MOD =   modulo-1; //Modulo set 1500 for a 32 microsecond timer ( 48mHz/1500 = .032MHz)
	TPM0->SC |=  prescaler; //Set the Prescaler
	TPM0->SC |=       0x80; //Clear Overthrow Flag          Status & Control
	TPM0->SC |=       0x40; //Enable timer interupt on TOF
	
	NVIC->ISER[0] |= 0x0020000; //What the fuck is thissss How is this value determined
	__enable_irq();
	
	return;
}

void startTPM0Counter(uint16_t modulo, uint32_t prescaler){
	TPM0->MOD =  modulo-1; //Modulo set 1500 for a 32 microsecond timer ( 48mHz/1500 = .032MHz)
	TPM0->SC |= prescaler; //Set the Prescaler
	
	TPM0->SC |= 0x80; //Clear Overthrow Flag
	TPM0->SC |= 0x08; //Enable the timer Counter
	
	return;
}

void stopTPM0Counter(void){
	TPM0->SC |=  0x80; //Clear Overthrow Flag
	TPM0->SC &= ~0x08; //Disable the timer Counter
	
	return;
}

void Init_PortB(void){
	//Clock Gate Access
	SIM->SCGC5 |= 0x400; //Enable Port B clock access
	
	PORTB->PCR[0] |= 0x100; //Configure PortB Pin00 as GPIO - Pulse     Pan
	PORTB->PCR[1] |= 0x100; //Configure Portb Pin01 as GPIO - Direction Pan
	PORTB->PCR[2] |= 0x100; //Configure Portb Pin02 as GPIO - Pulse     Tilt
	PORTB->PCR[3] |= 0x000; //Configure Portb Pin03 as GPIO - Direction Tilt
	
	GPIOB->PDDR |= 0x0000F; //Pins 0 1 2 3 configured to output
	GPIOB->PCOR |= 0x0000F; //Set Pins 0 1 2 3 to HIGH
	
	return;
}

void task_pulseStepperMotor(uint32_t motorPin, uint16_t modulo, uint32_t prescaler) {
	GPIOB->PSOR |= motorPin;
	startTPM0Counter(modulo, prescaler);
	
	return;
}

void task_changeDirection(uint32_t motorPin, uint16_t modulo, uint32_t prescaler){
	GPIOB->PSOR |= motorPin;
	startTPM0Counter(modulo, prescaler);
	
	return;
}

void TPM0_IRQHandler(void){
	
	// Look for Low Pin and set it to High
	if (GPIOB->PDOR &  PAN_PTB_PIN00_PUL){
			GPIOB->PCOR |= PAN_PTB_PIN00_PUL;
	}
	if (GPIOB->PDOR &  TILT_PTB_PIN03_PUL){
			GPIOB->PCOR |= TILT_PTB_PIN03_PUL;
	}
	if (GPIOB->PDOR &  PAN_PTB_PIN01_DIR){
			GPIOB->PCOR |= PAN_PTB_PIN01_DIR;
	}
	if (GPIOB->PDOR &  TILT_PTB_PIN04_DIR){
			GPIOB->PCOR |= TILT_PTB_PIN04_DIR;
	}
	
	//Disable the timer
	TPM0->SC |= 0x80; //Clear the Timer Overflow Flag
	stopTPM0Counter();
	
	return;
}

void task_motorComponentStatusCheck(void){
	//Check Pin Volage
	GPIOB->PSOR |= PAN_PTB_PIN00_PUL;
	GPIOB->PSOR |= PAN_PTB_PIN01_DIR;

	//Check Timer overflow

	startTPM0Counter(0xFFFF, 0x07);
	
	
	if(TPM0->SC & 0x80){
			GPIOB->PTOR |= PAN_PTB_PIN00_PUL;
			TPM0->SC |= 0x80;
	}
	
	return;
}

void task_scanForAndProcessIfMotorCommands(unsigned char recievedChar){
		//Check for motor commands
	
		// Pan Processing
		if     (recievedChar == PAN_RIGHT ){
			if(panDirectionReversed == 1)
			{
				task_changeDirection(PAN_PTB_PIN01_DIR, 0x002F, 0x00 );
				panDirectionReversed = 0;
			}
			
			task_pulseStepperMotor(PAN_PTB_PIN00_PUL, 0x002F, 0x00 );
		}
		
		else if(recievedChar == PAN_LEFT)
		{
			if( panDirectionReversed == 0)
			{
				task_changeDirection(PAN_PTB_PIN01_DIR, 0x002F, 0x00 );
				panDirectionReversed = 1;
			}
			
			task_pulseStepperMotor(PAN_PTB_PIN00_PUL, 0x002F, 0x00 );
		}
		
		// Tilt Processing
	 if(recievedChar == TILT_UP  ){
			task_pulseStepperMotor(TILT_PTB_PIN03_PUL, 0x002F, 0x00);
		} 
		else if(recievedChar == TILT_DOWN){
			task_pulseStepperMotor(TILT_PTB_PIN03_PUL, 0x002F, 0x00);
		}
		
		return;
}
