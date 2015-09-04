#include "utils.h"

#include <wiringPi.h>
#include <mcp23s17.h>

int lastChipSelect;

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    //*ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void findAndReplace(std::string* str, char replace, char with)
{
    for(unsigned int i = 0; i < str->length(); i++)
    {
        if(str->at(i) == replace)
            str->at(i) = with;
    }
}

void setupChipSelect()
{
    mcp23s17Setup(CS_BASE, 0, 0);

    for(int i = 0; i < 16; i++)
    {
        pinMode(CS_BASE + i, OUTPUT);

        #ifdef DEBUG
            if(i & 0x01)
                digitalWrite(CS_BASE + i, 1);
            else
                digitalWrite(CS_BASE + i, 0);
        #endif

        digitalWrite(CS_BASE + i, 1);
    }
}

void setupDigitalInputs()
{
    mcp23s17Setup(CS_BASE + 16, 0, 1);
    //mcp23s17Setup(CS_BASE + 32, 0, 2);

    for(int i = 0; i < 16; i++)
    {
        pinMode(CS_BASE + 16 + i, INPUT);
        pullUpDnControl(CS_BASE + 16 + i, PUD_UP);
    }

    /*for(int i = 0; i < 16; i++)
    {
        pinMode(CS_BASE + 32 + i, INPUT);
        pullUpDnControl(CS_BASE + 32 + i, PUD_UP);
    }*/
}
