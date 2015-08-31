#include "GY85.h"
#include <Wire.h>

GY_85 GY85;     //create the object

void setup()
{
    Wire.begin();
    delay(10);
    Serial.begin(9600);
    delay(10);
    set_GY85();
    delay(10);
}

void loop()
{
    Serial.print  ( "accelerometer" );
    Serial.print  ( " x:" );
    Serial.print  ( GY85.accelerometer_x );
    Serial.print  ( " y:" );
    Serial.print  ( GY85.accelerometer_y );
    Serial.print  ( " z:" );
    Serial.println( GY85.accelerometer_z );

    Serial.print  ( "  compass" );
    Serial.print  ( " x:" );
    Serial.print  ( GY85.compass_x );
    Serial.print  ( " y:" );
    Serial.print  ( GY85.compass_y );
    Serial.print  (" z:");
    Serial.println( GY85.compass_z );
    
    Serial.print  ( "  gyro" );
    Serial.print  ( " x:" );
    Serial.print  ( GY85.gyro_x );
    Serial.print  ( " y:" );
    Serial.print  ( GY85.gyro_y );
    Serial.print  ( " z:" );
    Serial.print  ( GY85.gyro_z );
    Serial.print  ( " gyro temp:" );
    Serial.println( GY85.temperature );
    
    delay(500);             // only read every 0,5 seconds, 10ms for 100Hz, 20ms for 50Hz
}