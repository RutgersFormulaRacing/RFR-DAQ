#ifndef _ANALOG_INPUT_H_
#define _ANALOG_INPUT_H_

#include <utility>
#include <string>

class AnalogInput
{
    public:
        AnalogInput();
        ~AnalogInput();

        void setName(std::string name);
        void setPinPath(std::string pinPath);
        void setMapFrom(std::pair<float, float> mapFrom);
        void setMapTo(std::pair<float, float> mapTo);

        std::string getName();
        std::string getPinPath();
        std::pair<float, float> getMapFrom();
        std::pair<float, float> getMapTo();

    private:
        std::string name;
        std::string pinPath;

        std::pair<float, float> mapFrom;
        std::pair<float, float> mapTo;
};

#endif
