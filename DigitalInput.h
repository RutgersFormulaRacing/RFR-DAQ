#ifndef _DIGITAL_INPUT_H_
#define _DIGITAL_INPUT_H_

#define EXPANDER_SIZE   16

#include "GPIOExpander.h"

#include <string>
#include <vector>

class DigitalInput
{
    public:
    DigitalInput(GPIOExpander *csExpander, std::vector<GPIOExpander*>* GPIOBanks);
    ~DigitalInput();

    void setName(std::string);
    void setBank(unsigned char bank);
    void setChannel(unsigned char channel);
    void setPolarity(int polarity);

    std::string getName();
    unsigned char getBank();
    unsigned char getChannel();
    int getPolarity();

    void setup();
    bool read();

    private:
    GPIOExpander *csExpander;
    std::vector<GPIOExpander*> *GPIOBanks;

    std::string name;
    unsigned char bank, channel;
    int polarity;
};

#endif
