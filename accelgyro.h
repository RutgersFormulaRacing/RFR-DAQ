#include "i2cDevice.h"
#include <iostream>

#define ACC_X   "AX"
#define ACC_Y   "AY"
#define ACC_Z   "AZ"

#define GYO_P   "GP"
#define GYO_R   "GR"
#define GYO_Y   "GY"

class accelgyro : public I2CDevice
{
    public:
        accelgyro(std::string name, int fd) : I2CDevice(name, fd){}

        void init();
        int read(std::string arg);
};
