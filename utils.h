#ifndef _UTILS_H_
#define _UTILS_H_

#define DEBUG   1

#define CS_BASE         100
#define ADC_BANK_0      CS_BASE+1
#define DIGITAL_BANK_0  CS_BASE+8

#include <string>

typedef struct dataFrameEntry
{
    std::string name;
    float filter;
};

extern int lastChipSelect;

char* itoa(int value, char* result, int base);
void findAndReplace(std::string* str, char replace, char with);

void setupChipSelect();
void setupDigitalInputs();

#endif
