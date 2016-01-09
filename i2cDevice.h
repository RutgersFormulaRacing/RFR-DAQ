#ifndef _I2C_DEVICE_H_
#define _I2C_DEVICE_H_

#include <string>

#include <wiringPi.h>
#include <wiringPiI2C.h>

class I2CDevice
{
    public:
        I2CDevice(std::string name, int address)
        {
            this->name = name;
            this->address = address;

            this->fd = wiringPiI2CSetup(address);
        }

        virtual void init() = 0;
        virtual int read(std::string arg) = 0;

    protected:
        int address, fd;
        std::string name;
};

typedef struct I2CRequest
{
    I2CDevice* device;
    std::string arg;
};

#endif
