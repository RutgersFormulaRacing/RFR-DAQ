#ifndef _UTILS_H_
#define _UTILS_H_

#define DEBUG   1

#define SERIAL_SYNC_PIN 7

#define CS_BASE         100
#define ADC_BANK_0      CS_BASE+1
#define DIGITAL_BANK_0  CS_BASE+8

#include <string>

typedef struct dataFrameEntry
{
    std::string name;
    float filter;
};

typedef struct i2cDevice
{
    std::string name;
    unsigned char address;

    i2cDevice(std::string n, unsigned char a) : name(n), address(a){}
};

typedef struct spiDevice
{
    std::string name;
    unsigned char chipSelect;
};

extern int lastChipSelect;

char* itoa(int value, char* result, int base);
void findAndReplace(std::string* str, char replace, char with);

void setupChipSelect();
void setupDigitalInputs();

#endif
