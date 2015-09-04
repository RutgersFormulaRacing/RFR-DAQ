#include "I2CRequest.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

I2CDevice::I2CDevice(int fd)
{
    this->fd = fd;
}

I2CDevice::~I2CDevice()
{}

void I2CDevice::setFD(int fd)
{
    this->fd = fd;
}

void I2CDevice::setNumBytesToRead(int bytesToRead)
{
    this->bytesToRead = bytesToRead;
}

int I2CDevice::read()
{
    return 0;
}
