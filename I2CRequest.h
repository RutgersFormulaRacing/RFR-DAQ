#ifndef _I2C_DEVICE_H_
#define _I2C_DEVICE_H_

#include <vector>

class I2CDevice
{
    public:
    I2CDevice(int fd);
    ~I2CDevice();

    void setFD(int fd);
    void setNumBytesToRead(int bytesToRead);

    int read();

    private:
    int fd, bytesToRead;

    std::vector<unsigned char> requestData;

};

#endif
