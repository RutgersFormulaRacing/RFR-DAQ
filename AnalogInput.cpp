#include "AnalogInput.h"

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "utils.h"

AnalogInput::AnalogInput()
{}

AnalogInput::~AnalogInput()
{}

void AnalogInput::setName(std::string name)
{
    this->name = name;
}

void AnalogInput::setBank(unsigned char bank)
{
    this->bank = bank;
}

void AnalogInput::setChannel(unsigned char channel)
{
    this->channel = channel;
}

void AnalogInput::setMapFrom(std::pair<float, float> mapFrom)
{
    this->mapFrom = mapFrom;
}

void AnalogInput::setMapTo(std::pair<float, float> mapTo)
{
    this->mapTo = mapTo;
}

std::string AnalogInput::getName()
{
    return this->name;
}

unsigned char AnalogInput::getBank()
{
    return this->bank;
}

unsigned char AnalogInput::getChannel()
{
    return this->channel;
}

std::pair<float, float> AnalogInput::getMapFrom()
{
    return this->mapFrom;
}

std::pair<float, float> AnalogInput::getMapTo()
{
    return this->mapTo;
}

float AnalogInput::read()
{
    unsigned char buf[3] = {0};
    int result;
    float fResult;

    buf[0] = (1 << 1) | (1 << 2) | ((channel & 0x07) >> 2);
    buf[1] = (channel & 0x03) << 7;

    //Enable new chip select
    digitalWrite(ADC_BANK_0 + bank, 0);

    //Change to chip select 1 so that accidental commands aren't sent to the expander
    wiringPiSPIDataRW(1, buf, 3);

    //Disable chip select
    digitalWrite(ADC_BANK_0 + bank, 1);

    result = buf[1] & 0x0F;
    result = (result << 8) | buf[2];

    fResult = (result - mapFrom.first)*(mapTo.second - mapTo.first)/(mapFrom.second - mapFrom.first) + mapTo.first;

    return fResult;
}
