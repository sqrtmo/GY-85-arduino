#include <Wire.h>
#include "GY-85.h"
#include <Arduino.h>

void SetAccelerometer()
{
    //Put the ADXL345 into +/- 4G range by writing the value 0x01 to the DATA_FORMAT register.
    Wire.beginTransmission( ADXL345 );     // start transmission to device
    Wire.write( 0x31 );                 // send register address
    Wire.write( 0x01 );                 // send value to write
    Wire.endTransmission();             // end transmission
    
    //Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
    Wire.beginTransmission( ADXL345 );     // start transmission to device
    Wire.write( 0x2D );                 // send register address  //Power Control Register
    Wire.write( 0x08 );                 // send value to write
    Wire.endTransmission();             // end transmission

}

int* readFromAccelerometer()
{
    int axis[3];
    int buff[6];
    
    Wire.beginTransmission( ADXL345 );      // start transmission to device
    Wire.write( DATAX0 );               // sends address to read from
    Wire.endTransmission();              // end transmission
    
    Wire.beginTransmission( ADXL345 );      // start transmission to device
    Wire.requestFrom( ADXL345, 6 );         // request 6 bytes from device
    
    uint8_t i = 0;
    while(Wire.available())              // device may send less than requested (abnormal)
    {
        buff[i] = Wire.read();          // receive a byte
        i++;
    }
    Wire.endTransmission();              // end transmission
    
    axis[0] = ((buff[1]) << 8) | buff[0];
    axis[1] = ((buff[3]) << 8) | buff[2];
    axis[2] = ((buff[5]) << 8) | buff[4];
    
    return axis;
}

void SetCompass()
{
    //Put the HMC5883 IC into the correct operating mode
    Wire.beginTransmission( HMC5883 );//open communication with HMC5883
    Wire.write( 0x02 );               //select mode register
    Wire.write( 0x00 );               //continuous measurement mode
    Wire.endTransmission();
}

int* readFromCompass()
{
    int axis[3];
    
    //Tell the HMC5883 where to begin reading data
    Wire.beginTransmission( HMC5883 );
    Wire.write( 0x03 );               //select register 3, X MSB register
    Wire.endTransmission();
    
    
    //Read data from each axis, 2 registers per axis
    Wire.requestFrom( HMC5883, 6 );
    if(6<=Wire.available()){
        axis[0] = Wire.read()<<8;   //X msb
        axis[0] |= Wire.read();     //X lsb
        axis[2] = Wire.read()<<8;   //Z msb
        axis[2] |= Wire.read();     //Z lsb
        axis[1] = Wire.read()<<8;   //Y msb
        axis[1] |= Wire.read();     //Y lsb
    }
    return axis;
}

int g_offx = 0;
int g_offy = 0;
int g_offz = 0;

void SetGyro() {
    Wire.beginTransmission( ITG3200 );
    Wire.write( 0x3E );
    Wire.write( 0x00 );
    Wire.endTransmission();
    
    Wire.beginTransmission( ITG3200 );
    Wire.write( 0x15 );
    Wire.write( 0x07 );
    Wire.endTransmission();
    
    Wire.beginTransmission( ITG3200 );
    Wire.write( 0x16 );
    Wire.write( 0x1E );   // +/- 2000 dgrs/sec, 1KHz, 1E, 19
    Wire.endTransmission();
    
    Wire.beginTransmission( ITG3200 );
    Wire.write( 0x17 );
    Wire.write( 0x00 );
    Wire.endTransmission();
    
    delay(10);
    
    GyroCalibrate();
}

void GyroCalibrate(){
    
    int tmpx = 0;
    int tmpy = 0;
    int tmpz = 0;
    
    g_offx = 0;
    g_offy = 0;
    g_offz = 0;
    
    for (uint8_t i = 0; i < 10; i ++) //take the mean from 10 gyro probes and divide it from the current probe
    {
        delay(10);
        float* gp = ReadGyro();
        tmpx += *(  gp);
        tmpy += *(++gp);
        tmpz += *(++gp);
    }
    g_offx = tmpx/10;
    g_offy = tmpy/10;
    g_offz = tmpz/10;
}

float* ReadGyro()
{
    float axis[4];
    
    Wire.beginTransmission( ITG3200 );
    Wire.write( 0x1B );
    Wire.endTransmission();
    
    Wire.beginTransmission( ITG3200 );
    Wire.requestFrom( ITG3200, 8 );    // request 8 bytes from ITG3200
    
    int i = 0;
    uint8_t buff[8];
    while(Wire.available())
    {
        buff[i] = Wire.read();
        i++;
    }
    Wire.endTransmission();
    
    axis[0] = ((buff[4] << 8) | buff[5]) - g_offx;
    axis[1] = ((buff[2] << 8) | buff[3]) - g_offy;
    axis[2] = ((buff[6] << 8) | buff[7]) - g_offz;
    axis[3] = ((buff[0] << 8) | buff[1]); // temperature
    
    return axis;
}

