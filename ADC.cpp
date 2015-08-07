#include <string.h>
#include <cstdlib>

#include <wiringPiSPI.h>

#include "ADC.h"
#include "utils.h"

ADC::ADC(unsigned char piCE, unsigned char CE)
{
    this->piCE = piCE;
    this->CE = CE;
}

ADC::~ADC()
{

}

uint16_t ADC::read(byte channel)
{
    byte length = 3;

    unsigned char buf[length];

    memset(buf, 0, length);

    buf[0] = (byte)(1 << 5) | (byte)(1 << 6) | (byte)((channel >> 2) << 7);
    buf[1] = (byte)(channel & 0x03);

    wiringPiSPIDataRW(piCE, buf, length);

    buf[1] &= 0x0F; //Clear uncessary bits

    return *((uint16_t*)(buf + 1));
}
