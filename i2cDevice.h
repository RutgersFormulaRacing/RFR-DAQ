#ifndef _I2C_DEVICE_H_
#define _I2C_DEVICE_H_

#include <string>

class I2CDevice
{
    public:
        I2CDevice(std::string name, int fd)
        {
            this->name = name;
            this->fd = fd;
        }

        void setFD(int fd)
        {
            this->fd = fd;
        }

        int getFD()
        {
            return this->fd;
        }

        virtual void init() = 0;
        virtual int read(std::string arg) = 0;

    protected:
        int fd;
        std::string name;
};

#endif
