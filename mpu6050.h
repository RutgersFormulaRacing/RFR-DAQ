#include "i2cDevice.h"
#include <iostream>

#define ACC_X   "AX"
#define ACC_Y   "AY"
#define ACC_Z   "AZ"

#define GYO_P   "GP"
#define GYO_R   "GR"
#define GYO_Y   "GY"

class mpu6050 : public I2CDevice
{
    public:
        mpu6050(std::string name, int address) : I2CDevice(name, address){}

        void init();
        int read(std::string arg);
};
