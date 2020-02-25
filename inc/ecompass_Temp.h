

#define INCLUDE (0)


#if INCLUDE == (1)

#ifndef __FXOS8700_H__
#define __FXOS8700_H__

#include "Arduino.h" // What is this???

#include <Adafruit_Sensor.h> // Get this source code
#include <Wire.h>            // Is this a dependency???

/*=========================================================================
	 I2C ADDRESS/BITS AND SETTINGS
	 -----------------------------------------------------------------------*/
#define FXOS8700_ADDRESS (0x1F) // 0011111

#define FXOS8700_ID (0xC7) // 1100 0111
/*=========================================================================*/

/*=========================================================================
	 REGISTERS
	 -----------------------------------------------------------------------*/
typedef enum {
 FXOS8700_REGISTER_STATUS = 0x00,    
 FXOS8700_REGISTER_OUT_X_MSB = 0x01, 
 FXOS8700_REGISTER_OUT_X_LSB = 0x02, 
 FXOS8700_REGISTER_OUT_Y_MSB = 0x03, 
 FXOS8700_REGISTER_OUT_Y_LSB = 0x04, 
 FXOS8700_REGISTER_OUT_Z_MSB = 0x05, 
 FXOS8700_REGISTER_OUT_Z_LSB = 0x06, 
 FXOS8700_REGISTER_WHO_AM_I =
		 0x0D, 
 FXOS8700_REGISTER_XYZ_DATA_CFG = 0x0E, 
 FXOS8700_REGISTER_CTRL_REG1 =
		 0x2A, 
 FXOS8700_REGISTER_CTRL_REG2 =
		 0x2B, 
 FXOS8700_REGISTER_CTRL_REG3 =
		 0x2C, 
 FXOS8700_REGISTER_CTRL_REG4 =
		 0x2D, 
 FXOS8700_REGISTER_CTRL_REG5 =
		 0x2E, 
 FXOS8700_REGISTER_MSTATUS = 0x32,    
 FXOS8700_REGISTER_MOUT_X_MSB = 0x33, 
 FXOS8700_REGISTER_MOUT_X_LSB = 0x34, 
 FXOS8700_REGISTER_MOUT_Y_MSB = 0x35, 
 FXOS8700_REGISTER_MOUT_Y_LSB = 0x36, 
 FXOS8700_REGISTER_MOUT_Z_MSB = 0x37, 
 FXOS8700_REGISTER_MOUT_Z_LSB = 0x38, 
 FXOS8700_REGISTER_MCTRL_REG1 =
		 0x5B, 
 FXOS8700_REGISTER_MCTRL_REG2 =
		 0x5C, 
 FXOS8700_REGISTER_MCTRL_REG3 =
		 0x5D, 
} fxos8700Registers_t;
/*=========================================================================*/

/*=========================================================================
	 OPTIONAL SPEED SETTINGS
	 -----------------------------------------------------------------------*/
typedef enum {
 ACCEL_RANGE_2G = 0x00, 
 ACCEL_RANGE_4G = 0x01, 
 ACCEL_RANGE_8G = 0x02  
} fxos8700AccelRange_t;
/*=========================================================================*/

/*=========================================================================
	 RAW GYROSCOPE DATA TYPE
	 -----------------------------------------------------------------------*/
typedef struct {
 int16_t x; 
 int16_t y; 
 int16_t z; 
} fxos8700RawData_t;
/*=========================================================================*/

class Adafruit_FXOS8700;

class Adafruit_FXOS8700_Accelerometer : public Adafruit_Sensor {
public:
 Adafruit_FXOS8700_Accelerometer(Adafruit_FXOS8700 *parent) {
	 _theFXOS8700 = parent;
 }
 bool getEvent(sensors_event_t *);
 void getSensor(sensor_t *);

private:
 int _sensorID = 8701;
 Adafruit_FXOS8700 *_theFXOS8700 = NULL;
};

class Adafruit_FXOS8700_Magnetometer : public Adafruit_Sensor {
public:
 Adafruit_FXOS8700_Magnetometer(Adafruit_FXOS8700 *parent) {
	 _theFXOS8700 = parent;
 }
 bool getEvent(sensors_event_t *);
 void getSensor(sensor_t *);

private:
 int _sensorID = 8702;
 Adafruit_FXOS8700 *_theFXOS8700 = NULL;
};

/**************************************************************************/
/**************************************************************************/
class Adafruit_FXOS8700 : public Adafruit_Sensor {
public:
 Adafruit_FXOS8700(int32_t accelSensorID = -1, int32_t magSensorID = -1);

 bool begin(fxos8700AccelRange_t rng = ACCEL_RANGE_2G);
 bool getEvent(sensors_event_t *accel);
 void getSensor(sensor_t *accel);
 bool getEvent(sensors_event_t *accel, sensors_event_t *mag);
 void getSensor(sensor_t *accel, sensor_t *mag);
 void standby(boolean standby);

 fxos8700RawData_t accel_raw;
 fxos8700RawData_t mag_raw;

 Adafruit_Sensor *getMagnetometerSensor(void);
 Adafruit_Sensor *getAccelerometerSensor(void);

 Adafruit_FXOS8700_Accelerometer *accel_sensor =
		 NULL; 
 Adafruit_FXOS8700_Magnetometer *mag_sensor = NULL; 

private:
 void write8(byte reg, byte value);
 byte read8(byte reg);

 fxos8700AccelRange_t _range;
 int32_t _accelSensorID;
 int32_t _magSensorID;
};

#endif
#endif