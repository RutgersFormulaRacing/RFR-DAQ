#include "i2cDevice.h"

/*
    Depending on who reads this...
    These devices are weird and require a bit of tweaking

    1. There IS a way to configure the I2C address of these devices, location 0x00E in EEPROM
    2. The I2C code provided by wiringpi may not work with this without kernel adjustments
*/

class mlx90616 : public I2CDevice
{

    public:
        mlx90616(std::string name, int fd) : I2CDevice(name, fd) {}

        void init();
        int read(std::string arg);

};
