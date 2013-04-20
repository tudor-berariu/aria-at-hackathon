#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MPUData.h"

class MPU
{
 public:
  bool setup();
  MPUData getData();
 private:
  MPU6050 accelgyro;
};
