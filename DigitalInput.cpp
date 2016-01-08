#include "DigitalInput.h"

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "utils.h"

DigitalInput::DigitalInput(){}

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

unsigned char DigitalInput::read()
{
    int ret = 0;

    digitalWrite(DIGITAL_BANK_0 + bank, 0);
    ret = digitalRead(GPIO_BASE + channel);
    digitalWrite(DIGITAL_BANK_0 + bank, 1);

    ret = ret > 0 ? 1 : 0;

    if(polarity < 0)
    {
        ret = (ret*-1) + 1;
    }

    return ret;
}
