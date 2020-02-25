// Variable Name Changes
//Sensor <-------------------------- Adafruit_Sensor
//fxos8700AccelRange_t <------------ fxos8700AccelRange_t
//sensorsEvent_t <------------------ sensors_event_t
//sensor_t <------------------------ sensor_t

// Defined in ecompass.h
//Adafruit_FXOS8700 <--------------- fxos8700_t
//Adafruit_FXOS8700_Magnetometer  <- fxos8700_Magnetometer_t
//Adafruit_FXOS8700_Accelerometer <- fxos8700_Accelerometer_t

#define INCLUDE (1)


#if INCLUDE == (1)
#ifndef _ECOMPASS_SENSOR_H_
#define _ECOMPASS_SENSOR_H_

//----------------------------
// Includes
//----------------------------
#include <stdint.h>
#include "ecompassSensor.h"
// Implement Arduino.h <-- Convert to KL25Z


//----------------------------
// Definitions
//----------------------------
#define SENSORS_GRAVITY_EARTH (9.80665F) // The Earth's gravity in m/s^2 
#define SENSORS_GRAVITY_MOON  (1.6F)     // The moon's  gravity in m/s^2
#define SENSORS_GRAVITY_SUN   (275.0F)   // The sun's   gravity in m/s^2 
#define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)

#define SENSORS_MAGFIELD_EARTH_MAX   (60.0F)    // Maximum magnetic field on Earth's surface
#define SENSORS_MAGFIELD_EARTH_MIN   (30.0F)    // Minimum magnetic field on Earth's surface

#define SENSORS_PRESSURE_SEALEVELHPA (1013.25F) // Average sea level pressure is 1013.25 hPa

#define SENSORS_DPS_TO_RADS (0.017453293F) // Degrees/s to rad/s multiplier               
#define SENSORS_RADS_TO_DPS (57.29577793F) // Rad/s to degrees/s  multiplier
#define SENSORS_GAUSS_TO_MICROTESLA (100)  // Gauss to micro-Tesla multiplier


//----------------------------
// Enumerators
//----------------------------
typedef enum {
  SENSOR_TYPE_ACCELEROMETER       = ( 1), // Gravity + linear acceleration 
  SENSOR_TYPE_MAGNETIC_FIELD      = ( 2),
  SENSOR_TYPE_ORIENTATION         = ( 3),
  SENSOR_TYPE_GYROSCOPE           = ( 4),
  SENSOR_TYPE_LIGHT               = ( 5),
  SENSOR_TYPE_PRESSURE            = ( 6),
  SENSOR_TYPE_PROXIMITY           = ( 8),
  SENSOR_TYPE_GRAVITY             = ( 9),
  SENSOR_TYPE_LINEAR_ACCELERATION = (10), // Acceleration not including gravity
  SENSOR_TYPE_ROTATION_VECTOR     = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY   = (12),
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
  SENSOR_TYPE_OBJECT_TEMPERATURE  = (14),
  SENSOR_TYPE_VOLTAGE             = (15),
  SENSOR_TYPE_CURRENT             = (16),
  SENSOR_TYPE_COLOR               = (17)
} sensorType_t;


//----------------------------
// Structures
//----------------------------
// Vector Stucture
//
typedef struct {
  union {
    float vector3D[3]; ///< 3D vector elements
		
		// Struct for holding XYZ component
    struct {
      float x; // X component of vector
      float y; // Y component of vector
      float z; // Z component of vector
    };  
		
    // Orientation sensors
    struct {
      float    roll; // Rotation around the longitudinal axis (the plane body, 'X
                     // axis'). Roll is positive and increasing when moving
                     // downward. -90 degrees <= roll <= 90 degrees
			
      float   pitch; // Rotation around the lateral axis (the wing span, 'Y
                     // axis'). Pitch is positive and increasing when moving
                     // upwards. -180 degrees <= pitch <= 180 degrees) 
      
			float heading; // Angle between the longitudinal axis (the plane body)
                     // and magnetic north, measured clockwise when viewing from
                     // the top of the device. 0-359 degrees 
    }; // Struct for holding roll/pitch/heading
  }; // Union that can hold 3D vector array, XYZ components or roll/pitch/heading
                     
  int8_t       status; // Status byte
  uint8_t reserved[3]; // Reserved
	
// Color Structure
//	
} sensorsVector_t;

typedef struct {
  union {
		// RGB color space
    float colorRaw[3]; // Raw 3-element data
    
		// RGB data in floating point notation
    struct {
      float r;   // Red component
      float g;   // Green component
      float b;   // Blue component
    };
  }; // Union of various ways to describe RGB colorspace
  uint32_t rgba; // 24-bit RGBA value 
} sensorsColor_t;

// Event Structure
//
typedef struct {
  int32_t   version; // must be sizeof(struct sensors_event_t)
  int32_t  sensorId; // unique sensor identifier
  int32_t      type; // sensor type 
  int32_t reserved0; // reserved 
  int32_t timestamp; // time is in milliseconds 
  union {
    float data[4]; // Raw data
    sensorsVector_t acceleration; // acceleration values are in meter per second per second (m/s^2)
    sensorsVector_t     magnetic; // magnetic vector values are in micro-Tesla (uT)
    sensorsVector_t  orientation; // orientation values are in degrees
    sensorsVector_t gyro;         // gyroscope values are in rad/s
		
    float       temperature; // temperature is in degrees centigrade (Celsius)
    float          distance; // distance in centimeters
    float             light; // light in SI lux units
    float          pressure; // pressure in hectopascal (hPa)
    float relative_humidity; // relative humidity in percent
    float           current; // current in milliamps (mA)
    float           voltage; // voltage in volts (V)
    sensorsColor_t    color; // color in RGB component values
  }; // Union for the wide ranges of data we can carry
} sensorsEvent_t;

// Sensor Structure
//
typedef struct {
  char name[12];     // sensor name
  int32_t   version; // version of the hardware + driver
  int32_t sensor_id; // unique sensor identifier
  int32_t      type; // this sensor's type (ex. SENSOR_TYPE_LIGHT)
  float   max_value; // maximum value of this sensor's value in SI units
  float   min_value; // minimum value of this sensor's value in SI units 
  float  resolution; // smallest difference between two values reported by this sensor
  int32_t min_delay; // min delay in microseconds between events. zero = not a constant rate
} sensor_t;

#endif
#endif

