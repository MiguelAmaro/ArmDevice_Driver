
#ifndef __FXOS8700_H__
#define __FXOS8700_H__

//----------------------------
// Includes
//----------------------------
#include <stdint.h>
#include "ecompassSensor.h"
// Implement Wire.h <-- Not finished
// Implement Adafruit_Sensor.h <-- Not finished
// Implement Arduino.h

//----------------------------
// Definitions
//----------------------------

// I2C Address/Bits and Settings
#define FXOS8700_ADDRESS (0x1F)
#define FXOS8700_ID      (0xC7)

// FXOS8700 Register Definitions
#define FXOS8700_REGISTER_STATUS       (0x00)
#define FXOS8700_REGISTER_OUT_X_MSB    (0x01)
#define FXOS8700_REGISTER_OUT_X_LSB    (0x02)
#define FXOS8700_REGISTER_OUT_Y_MSB    (0x03)
#define FXOS8700_REGISTER_OUT_Y_LSB    (0x04)
#define FXOS8700_REGISTER_OUT_Z_MSB    (0x05)
#define FXOS8700_REGISTER_OUT_Z_LSB    (0x06)

#define FXOS8700_REGISTER_WHO_AM_I     (0x0D)
#define FXOS8700_REGISTER_XYZ_DATA_CFG (0x0E)

#define FXOS8700_REGISTER_CTRL_REG1    (0x2A)
#define FXOS8700_REGISTER_CTRL_REG2    (0x2B)
#define FXOS8700_REGISTER_CTRL_REG3    (0x2C)
#define FXOS8700_REGISTER_CTRL_REG4    (0x2D)
#define FXOS8700_REGISTER_CTRL_REG5    (0x2E)

#define FXOS8700_REGISTER_MSTATUS      (0x32)

#define FXOS8700_REGISTER_MOUT_X_MSB   (0x33)
#define FXOS8700_REGISTER_MOUT_X_LSB   (0x34)
#define FXOS8700_REGISTER_MOUT_Y_MSB   (0x35)
#define FXOS8700_REGISTER_MOUT_Y_LSB   (0x36)
#define FXOS8700_REGISTER_MOUT_Z_MSB   (0x37)
#define FXOS8700_REGISTER_MOUT_Z_LSB   (0x38)

#define FXOS8700_REGISTER_MCTRL_REG1   (0x5B)
#define FXOS8700_REGISTER_MCTRL_REG2   (0x5C)
#define FXOS8700_REGISTER_MCTRL_REG3   (0x5D)

// Speed Setting Definitions
#define ACCEL_RANGE_2G (0x00)
#define ACCEL_RANGE_4G (0x01)
#define ACCEL_RANGE_8G (0x02)


//----------------------------
// Stuctures
//----------------------------

// Stucutures Foward Declerations Section
typedef struct fxos8700 fxos8700_t;

// Raw Gyroscope Data Structure
typedef struct {
 int16_t x; 
 int16_t y; 
 int16_t z; 
} fxos8700RawData_t;

/**************************************************************************/
// Variable Name Changes
//Sensor <-------------------------- Adafruit_Sensor
//fxos8700AccelRange_t <------------ fxos8700AccelRange_t
//sensorsEvent_t <------------------ sensors_event_t
//sensor_t <------------------------ sensor_t
//Adafruit_FXOS8700 <--------------- fxos8700_t
//Adafruit_FXOS8700_Magnetometer  <- fxos8700_Magnetometer_t
//Adafruit_FXOS8700_Accelerometer <- fxos8700_Accelerometer_t
/**************************************************************************/
// Accelerometer Structure
// Add anything that is inherited Adafruit_Sensor
// Implement Methods
typedef struct {
	// Was Private
	uint16_t sensorId;          // Value: 8701
	fxos8700_t* fxos8700Sensor; // Value: NULL
	
} fxos8700_Accelerometer_t;

// Accelerometer Functions
void    Init_fxos_Accelerometer(fxos8700_t* parent);
uint8_t getEvent (sensorsEvent_t*);
void    getSensor(sensor_t*      );

/**************************************************************************/
/**************************************************************************/
// Magnetometer Structure
// Add anything that is inherited Adafruit_Sensor
// Implement Methods
typedef struct {
	// Was Private
	uint16_t sensorId;          // Value: 8702
	fxos8700_t* fxos8700Sensor; // Value: NULL
	
} fxos8700_Magnetometer_t;

// Magnetometer Functions
void    Init_fxos_Magnetometer(fxos8700_t* parent);
uint8_t getEvent (sensorsEvent_t*);
void    getSensor(sensor_t*      );

/**************************************************************************/
/**************************************************************************/
// FXOS8700 Structure
// Add anything that is inherited Adafruit_Sensor
// Implement Methods
typedef struct {
	// Public
	fxos8700RawData_t accelRaw;
	fxos8700RawData_t   magRaw;
	
	fxos8700_Accelerometer_t* accelSensor = NULL;
	fxos8700_Magnetometer_t*    magSensor = NULL;
	
	// Was Private
	fxos8700AccelRange_t range;
	int32_t accelSensorId;
	int32_t   magSensorId;
	
} fxos8700;

// fxos8700 Functions
void    Init_fxos8700(int32_t accelSensorId = - 1, int32_t magSensorId = - 1);
uint8_t begin    (fxos8700AccelRange_t range = ACCEL_RANGE_2G);
uint8_t getEvent (sensorsEvent_t* accel);
void    getSensor(sensor_t* accel);
uint8_t getEvent (sensorsEvent_t* accel, sensor_t* mag);
void    getSensor(sensor_t* accel, sensor_t* mag);
void    standby  (uint8_t standby);

Sensor* getMagnetometerSensor (void);
Sensor* getAccelerometerSensor(void);

// fxos8700 Fuctions Private
void  writeByte(int8_t reg, int8_t value);
int8_t readByte(int8_t reg              );

#endif

