#include "GPIOExpander.h"

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "utils.h"

GPIOExpander::GPIOExpander(int cs)
{
    this->cs = cs;
    CSExpander = NULL;

    stateA = 0x00;
    stateB = 0x00;

    dirA = 0x00;
    dirB = 0x00;

    pullupA = 0x00;
    pullupB = 0x00;

    unsigned char aDir[] = {0x40 | 0x00, 0x00, dirA};
    unsigned char bDir[] = {0x40 | 0x00, 0x01, dirB};

    unsigned char aState[] = {0x40 | 0x00, 0x12, stateA};
    unsigned char bState[] = {0x40 | 0x00, 0x13, stateB};

    wiringPiSPIDataRW(cs, aDir, 3);
    wiringPiSPIDataRW(cs, bDir, 3);

    wiringPiSPIDataRW(cs, aState, 3);
    wiringPiSPIDataRW(cs, bState, 3);
}

GPIOExpander::GPIOExpander(GPIOExpander *CSExpander, int cs)
{
    this->CSExpander = CSExpander;
    this->cs = 1;

    stateA = 0x00;
    stateB = 0x00;

    dirA = 0x00;
    dirB = 0x00;

    pullupA = 0x00;
    pullupB = 0x00;

    unsigned char aDir[] = {0x40 | 0x00, 0x00, dirA};
    unsigned char bDir[] = {0x40 | 0x00, 0x01, dirB};

    unsigned char aState[] = {0x40 | 0x00, 0x12, stateA};
    unsigned char bState[] = {0x40 | 0x00, 0x13, stateB};

    CSExpander->write(0, cs, false);
    wiringPiSPIDataRW(cs, aDir, 3);
    CSExpander->write(0, cs, true);

    CSExpander->write(0, cs, false);
    wiringPiSPIDataRW(cs, bDir, 3);
    CSExpander->write(0, cs, true);

    CSExpander->write(0, cs, false);
    wiringPiSPIDataRW(cs, aState, 3);
    CSExpander->write(0, cs, true);

    CSExpander->write(0, cs, false);
    wiringPiSPIDataRW(cs, bState, 3);
    CSExpander->write(0, cs, true);
}

void GPIOExpander::setup(char bank, char pin, bool input)
{
    if(bank == 0)
    {
        if(input)
            sbi(dirA, pin);
        else
            cbi(dirA, pin);

        unsigned char message[] = {0x40 | 0x00, 0x00, dirA};

        wiringPiSPIDataRW(cs, message, 3);
    }
    else if(bank == 1)
    {
        if(input)
            sbi(dirB, pin);
        else
            cbi(dirB, pin);

        unsigned char message[] = {0x40 | 0x00, 0x01, dirB};

        wiringPiSPIDataRW(cs, message, 3);
    }
}

void GPIOExpander::pullup(char bank, char pin, bool en)
{
    if(bank == 0)
    {
        if(en)
            sbi(pullupA, pin);
        else
            cbi(pullupA, pin);

        unsigned char message[] = {0x40 | 0x00, 0x0C, pullupA};

        wiringPiSPIDataRW(cs, message, 3);
    }
    else if(bank == 1)
    {
        if(en)
            sbi(pullupB, pin);
        else
            cbi(pullupB, pin);

        unsigned char message[] = {0x40 | 0x00, 0x0D, pullupB};

        wiringPiSPIDataRW(cs, message, 3);
    }
}

void GPIOExpander::write(char bank, char pin, bool state)
{
    if(bank == 0)
    {
        if(state)
            sbi(stateA, pin);
        else
            cbi(stateA, pin);

        unsigned char message[] = {0x40 | 0x00, 0x12, stateA};

        wiringPiSPIDataRW(cs, message, 3);
    }
    else if(bank == 1)
    {
        if(state)
            sbi(stateB, pin);
        else
            cbi(stateB, pin);

        unsigned char message[] = {0x40 | 0x00, 0x13, stateB};

        wiringPiSPIDataRW(cs, message, 3);
    }
}

bool GPIOExpander::read(char bank, char pin)
{
    char ret;

    if(bank == 0)
    {
        unsigned char message[] = {0x40 | 0x00, 0x12, 0x00};

        wiringPiSPIDataRW(cs, message, 3);

        ret = message[2];
    }
    else if(bank == 1)
    {
        unsigned char message[] = {0x40 | 0x00, 0x13, 0x00};

        wiringPiSPIDataRW(cs, message, 3);

        ret = message[2];
    }

    return ((ret & (1 << pin)) != 0);
}
