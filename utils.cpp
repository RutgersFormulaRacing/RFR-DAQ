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

uint8_t crc8(const void *vptr, int len)
{
	const uint8_t *data = vptr;
	unsigned crc = 0;
	int i, j;
	for (j = len; j; j--, data++) {
		crc ^= (*data << 8);
		for(i = 8; i; i--) {
			if (crc & 0x8000)
				crc ^= (0x1070 << 3);
			crc <<= 1;
		}
	}
	return (uint8_t)(crc >> 8);
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
    mcp23s17Setup(GPIO_BASE, 1, 0);
    //Each of the digital input banks are connected to the CS expander
    //The included mcp23s17 library doesn't support this
    //So, setup the mcp23s17 to be on RPI_CS1 (like the analog banks are setup)
    //This will talk to both of the banks
    //Change the CS expander to select the correct GPIO bank
    //Then read, and all is good
    //This means that these pins are recycled for each bank

    for(int bank = 0; bank < 2; bank++)
    {
        //Select the correct GPIO bank with CS expander
        digitalWrite(DIGITAL_BANK_0 + bank, 0);

        for(int i = 0; i < 16; i++)
        {
            pinMode(GPIO_BASE + i, INPUT);
            pullUpDnControl(GPIO_BASE + i, PUD_UP);
        }

        //Deselect the correct GPIO bank with CS expander
        digitalWrite(DIGITAL_BANK_0 + bank, 1);
    }

    /*for(int i = 0; i < 16; i++)
    {
        pinMode(CS_BASE + 32 + i, INPUT);
        pullUpDnControl(CS_BASE + 32 + i, PUD_UP);
    }*/
}
