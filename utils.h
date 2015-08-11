#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

typedef unsigned char byte;

char* itoa(int value, char* result, int base);

int xmlValueParse(std::string str);

#endif
