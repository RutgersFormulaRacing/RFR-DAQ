#include "i2cDevice.h"

class accelgyro : public I2CDevice
{
    public:
        accelgyro(std::string name, int fd) : I2CDevice(name, fd){}

        int read(std::string arg);
};
