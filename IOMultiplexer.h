#ifndef _IOMULTIPLEXER_H_
#define _IOMULTIPLEXER_H_

#include <stdint.h>

#include "utils.h"

class IOMultiplexer
{
    public:
        IOMultiplexer();
        ~IOMultiplexer();

        void configure(uint8_t channel, bool output);
        void write(uint8_t channel, bool state);
        bool read(uint8_t channel);

        //These methods should be called before the above
        //These handle entire registers
        //Instead of calls to individual pins, saves time
        void readIn();
        void writeOut();

    private:
        uint16_t portDirections;
        uint16_t portStates;

};

#endif // _IOMULTIPLEXER_H_
