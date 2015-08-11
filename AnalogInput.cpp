#include "AnalogInput.h"

AnalogInput::AnalogInput()
{}

AnalogInput::~AnalogInput()
{}

void AnalogInput::setName(std::string name)
{
    this->name = name;
}

void AnalogInput::setPinPath(std::string pinPath)
{
    this->pinPath = pinPath;
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

std::string AnalogInput::getPinPath()
{
    return this->pinPath;
}

std::pair<float, float> AnalogInput::getMapFrom()
{
    return this->mapFrom;
}

std::pair<float, float> AnalogInput::getMapTo()
{
    return this->mapTo;
}
