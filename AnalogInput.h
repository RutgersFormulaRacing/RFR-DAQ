#ifndef _ANALOG_INPUT_H_
#define _ANALOG_INPUT_H_

#include <string>
#include <utility>
#include <vector>

class AnalogInput
{
    public:
        AnalogInput();
        ~AnalogInput();

        void setName(std::string name);
        void setBank(unsigned char bank);
        void setChannel(unsigned char channel);
        void setMapFrom(std::pair<float, float> mapFrom);
        void setMapTo(std::pair<float, float> mapTo);

        std::string getName();
        unsigned char getBank();
        unsigned char getChannel();
        std::pair<float, float> getMapFrom();
        std::pair<float, float> getMapTo();

        float read();

    private:
        std::string name;
        unsigned char bank, channel;
        std::pair<float, float> mapFrom;
        std::pair<float, float> mapTo;

        std::vector<int> dataFrames;
};

#endif
