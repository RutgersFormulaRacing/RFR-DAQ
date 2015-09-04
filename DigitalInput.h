#ifndef _DIGITAL_INPUT_H_
#define _DIGITAL_INPUT_H_

#define EXPANDER_SIZE   16

#include <string>

class DigitalInput
{
    public:
    DigitalInput();
    ~DigitalInput();

    void setName(std::string);
    void setBank(unsigned char bank);
    void setChannel(unsigned char channel);
    void setPolarity(int polarity);

    std::string getName();
    unsigned char getBank();
    unsigned char getChannel();
    int getPolarity();

    unsigned char read();

    private:
    std::string name;
    unsigned char bank, channel;
    int polarity;
};

#endif
