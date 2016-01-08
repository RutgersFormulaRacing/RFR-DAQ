#ifndef _UTILS_H_
#define _UTILS_H_

#define DEBUG   1

#define SERIAL_SYNC_PIN 7

#define CS_BASE         100
#define CAN_SPI         CS_BASE
#define ADC_BANK_0      CS_BASE+1
#define DIGITAL_BANK_0  CS_BASE+5
#define GPIO_BASE       CS_BASE + 16

#include <string>

typedef struct dataFrameEntry
{
    std::string name;
    float filter;
};

extern int lastChipSelect;

char* itoa(int value, char* result, int base);
void findAndReplace(std::string* str, char replace, char with);

uint8_t crc8(const void *vptr, int len);

void setupChipSelect();
void setupDigitalInputs();

#endif
