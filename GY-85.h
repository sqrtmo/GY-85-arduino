#ifndef GY-85_h
#define GY-85_h

//----------accelerometer----------//
#define ADXL345 (0x53) // Device address as specified in data sheet //ADXL345 accelerometer
#define DATAX0 (0x32)       //X-Axis Data 0
//#define DATAX1 0x33       //X-Axis Data 1
//#define DATAY0 0x34       //Y-Axis Data 0
//#define DATAY1 0x35       //Y-Axis Data 1
//#define DATAZ0 0x36       //Z-Axis Data 0
//#define DATAZ1 0x37       //Z-Axis Data 1

void SetAccelerometer();
int* readFromAccelerometer();
//----------accelerometer----------//

//-------------compass-------------//
#define HMC5883 0x1E //0011110b, I2C 7bit address of HMC5883
void SetCompass();
int* readFromCompass();
//-------------compass-------------//

//------------gyroscope------------//
#define ITG3200 0x68
void SetGyro();
float* ReadGyro();
void GyroCalibrate();
//------------gyroscope------------//

#endif
