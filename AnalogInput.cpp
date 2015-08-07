#include "AnalogInput.h"

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
