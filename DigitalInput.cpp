#include "DigitalInput.h"

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "utils.h"

DigitalInput::DigitalInput(GPIOExpander *csExpander, std::vector<GPIOExpander*>* GPIOBanks)
{
    this->csExpander = csExpander;
    this->GPIOBanks = GPIOBanks;
}

DigitalInput::~DigitalInput(){}

void DigitalInput::setName(std::string name)
{
    this->name = name;
}

void DigitalInput::setBank(unsigned char bank)
{
    this->bank = bank;
}

void DigitalInput::setChannel(unsigned char channel)
{
    this->channel = channel;
}

void DigitalInput::setPolarity(int polarity)
{
    this->polarity = polarity;
}

std::string DigitalInput::getName()
{
    return name;
}

unsigned char DigitalInput::getBank()
{
    return bank;
}

unsigned char DigitalInput::getChannel()
{
    return channel;
}

int DigitalInput::getPolarity()
{
    return polarity;
}

void DigitalInput::setup()
{
    csExpander->write(0, GPIO_CS + (unsigned char)(bank/2), false);
    GPIOBanks->at((unsigned char)(bank/2))->setup(bank%2, channel, true);
    csExpander->write(0, GPIO_CS + (unsigned char)(bank/2), true);

    csExpander->write(0, GPIO_CS + (unsigned char)(bank/2), false);
    GPIOBanks->at((unsigned char)(bank/2))->pullup(bank%2, channel, true);
    csExpander->write(0, GPIO_CS + (unsigned char)(bank/2), true);
}

bool DigitalInput::read()
{
    unsigned char message[] = {0x40 | 0x01, 0x12 + (unsigned char)(bank/2), 0x00};

    csExpander->write(0, GPIO_CS + (unsigned char)(bank/2), false);
    wiringPiSPIDataRW(1, message, 3);
    csExpander->write(0, GPIO_CS + (unsigned char)(bank/2), true);

    return ((message[2] & (1 << channel)) > 0);
}
