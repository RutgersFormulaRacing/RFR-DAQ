#ifndef _GPIO_EXPANDER_H_
#define _GPIO_EXPANDER_H_

#define CAN_CS      0
#define ADC_CS      1
#define GPIO_CS     5

class GPIOExpander
{
    public:
        GPIOExpander(int cs);
        GPIOExpander(GPIOExpander *CSExpander, int cs);

        void init();

        void setup(char bank, char pin, bool input);
        void pullup(char bank, char pin, bool en);

        void write(char bank, char pin, bool state);
        bool read(char bank, char pin);

    private:
        int cs;
        char stateA, stateB;
        char dirA, dirB;
        char pullupA, pullupB;

        GPIOExpander *CSExpander;

};

#endif
