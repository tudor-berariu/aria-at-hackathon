#include <iostream>
#include "MPU.h"
#include "MPUData.h"

int main(int argc, const char *argv[])
{
  MPU mpu;
  if (!mpu.setup())
    {
      std::cerr << "MPU Error" <<std::endl;
      return 1;
    }
  while (true)
    {
      MPUData data = mpu.getData();
      std::cout << "(" << data.ax << "," << data.ay << "," << data.az << ")  -- (" <<
	data.gx << "," << data.gy << "," << data.gz << ")" << std::endl;
    }
  return 0;
}
