#ifndef _ADC_H_
#define _ADC_H_

#include <stdint.h>

typedef unsigned char byte;

//This library is meant to operate the MCP3204/3208
//SPI ADC

class ADC
{
    public:
        ADC(unsigned char piCE, unsigned char CE);
        ~ADC();

        uint16_t read(unsigned char channel);

    private:
        unsigned char piCE, CE;
};

#endif
