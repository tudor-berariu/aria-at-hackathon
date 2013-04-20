#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MPU.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69



bool MPU::setup() {
    // initialize device
    printf("Initializing I2C devices...\n");
    this->accelgyro.initialize();

    // verify connection
    printf("Testing device connections...\n");
    return this->accelgyro.testConnection();
}

MPUData MPU::getData() {
    // read raw accel/gyro measurements from device
  MPUData data;
  this->accelgyro.getMotion6(&(data.ax), &(data.ay), &(data.az), 
			     &(data.gx), &(data.gy), &(data.gz));
  return data;
}


