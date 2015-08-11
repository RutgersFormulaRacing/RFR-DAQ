#ifndef _DIGITALINPUT_H_
#define _DIGITALINPUT_H_

#include <stdint.h>
#include <string>

class DigitalInput
{
    public:
        DigitalInput();
        ~DigitalInput();

    private:
        std::string name;
        std::string pinPath;
};

#endif // _DIGITALINPUT_H_
