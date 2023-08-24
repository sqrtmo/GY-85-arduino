#include "GY_85.h"

// Create module object
GY_85 GY85;

void setup() {
    // Initialize the serial communication:
    Serial.begin(9600);

    // Initialize module
    GY85.init();
}

void loop() {   
    // Read data from sensors
    int* accelerometerReadings = GY85.readFromAccelerometer();
    int ax = GY85.accelerometer_x(accelerometerReadings);
    int ay = GY85.accelerometer_y(accelerometerReadings);
    int az = GY85.accelerometer_z(accelerometerReadings);
    
    int* compassReadings = GY85.readFromCompass();
    int cx = GY85.compass_x(compassReadings);
    int cy = GY85.compass_y(compassReadings);
    int cz = GY85.compass_z(compassReadings);

    float* gyroReadings = GY85.readGyro();
    float gx = GY85.gyro_x(gyroReadings);
    float gy = GY85.gyro_y(gyroReadings);
    float gz = GY85.gyro_z(gyroReadings);
    float gt = GY85.temp(gyroReadings);
    
    // Log it to serial port
    Serial.print("accelerometer");
    Serial.print(" x:");
    Serial.print(ax);
    Serial.print(" y:");
    Serial.print(ay);
    Serial.print(" z:");
    Serial.print(az);
    
    Serial.print("\t compass");
    Serial.print(" x:");
    Serial.print(cx);
    Serial.print(" y:");
    Serial.print(cy);
    Serial.print(" z:");
    Serial.print(cz);
    
    Serial.print("\t  gyro");
    Serial.print(" x:");
    Serial.print(gx);
    Serial.print(" y:");
    Serial.print(gy);
    Serial.print(" z:");
    Serial.print(gz);
    Serial.print("\t gyro temp:");
    Serial.println(gt);
    
    // Make delay between readings
    delay(100);
}