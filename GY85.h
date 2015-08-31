#include "Arduino.h"
#include <Wire.h>

#ifndef GY85_h
#define GY85_h

//----------addresses----------//
#define ADXL345 (0x53)       // Device address as specified in data sheet //ADXL345 accelerometer
#define DATAX0  (0x32)       //X-Axis Data 0
//#define DATAX1 0x33        //X-Axis Data 1
//#define DATAY0 0x34        //Y-Axis Data 0
//#define DATAY1 0x35        //Y-Axis Data 1
//#define DATAZ0 0x36        //Z-Axis Data 0
//#define DATAZ1 0x37        //Z-Axis Data 1
#define HMC5883 (0x1E)       //gyro
#define ITG3200 (0x68)       //compass

void set_GY85();

int*   readFromAccelerometer();
int*   readFromCompass();
float* ReadGyro();

typedef struct GY85
{
    int* accelp = readFromAccelerometer();
    
    int accelerometer_x = *(  accelp);
    int accelerometer_y = *(++accelp);
    int accelerometer_z = *(++accelp);
    
    
    int* compass = readFromCompass();
    
    int compass_x = *(  compass);
    int compass_y = *(++compass);
    int compass_z = *(++compass);
    

    float* gyro = ReadGyro();
    
    float gyro_x = *(  gyro) / 14.375;
    float gyro_y = *(++gyro) / 14.375;
    float gyro_z = *(++gyro) / 14.375;
    
    float temperature = 35 + ( *(++gyro)+13200 ) / 280;

} GY_85;

#endif
