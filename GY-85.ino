#include <Wire.h>
#include "Arduino.h"
#include "GY-85.h"

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    SetAccelerometer();
    SetCompass();
    SetGyro();
}

void loop()
{
    int* accelp;
    int* compassp;
    float* gyrop;
    
    accelp = readFromAccelerometer();
    compassp = readFromCompass();
    gyrop = ReadGyro();
    
//    Serial.print("accelerometer");
//    Serial.print(" x:");
//    Serial.print(*(  accelp));
//    Serial.print(" y:");
//    Serial.print(*(++accelp));
//    Serial.print(" z:");
//    Serial.print(*(++accelp));
//    
//    Serial.print("  compass");
//    Serial.print(" x:");
//    Serial.print(*(  compassp));
//    Serial.print(" y:");
//    Serial.print(*(++compassp));
//    Serial.print(" z:");
//    Serial.print(*(++compassp));
    
    Serial.print("  gyro");
    Serial.print(" x:");
    Serial.print(*(  gyrop)/ 14.375);
    Serial.print(" y:");
    Serial.print(*(++gyrop)/ 14.375);
    Serial.print(" z:");
    Serial.print(*(++gyrop)/ 14.375);
    Serial.print(" gyro temp:");
    Serial.println(35+(*(++gyrop)+13200)/280);
    
    delay(500);             // only read every 0,5 seconds, 10ms for 100Hz, 20ms for 50Hz
}