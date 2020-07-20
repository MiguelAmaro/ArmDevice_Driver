#ifndef SYSTEM_MACROS_H
#define SYSTEM_MACROS_H

//----------------------------
// SERIAL INSTRUCTIONS
//----------------------------
	// OnBoardLeds Module
	#define RED_ONBOARDLED_ON   ('r')
	#define GREEN_ONBOARDLED_ON ('g')
	#define BLUE_ONBOARDLED_ON  ('b')
	#define ALL_ONBOARDLED_OFF  ('o')
	#define LASER_ON  ('M')
	#define LASER_OFF ('N')
	// Motor Module
	#define PAN_CCW  ('A')
	#define PAN_CW   ('B')
	#define TILT_CCW ('C')
	#define TILT_CW  ('D')

//----------------------------
// I/0 PIN DEFENITIONS
//----------------------------
	// Motor Module
	#define PAN_PUL  (0) // port B
	#define PAN_DIR  (1) // port B
	#define TILT_PUL (2) // port B
	#define TILT_DIR (3) // port B
	// OnBoardLeds Module
	#define RED_LED_POS    (18) // port B
	#define GREEN_LED_POS  (19) // port B
	#define BLUE_LED_POS    (1) // port D
	#define LASERCTRL       (1) // port C

#endif

