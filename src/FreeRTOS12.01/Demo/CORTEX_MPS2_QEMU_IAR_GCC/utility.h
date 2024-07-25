// convert.h

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <math.h>

void floatToChar(float numero, char *buffer, int precisione);
BaseType_t isSchedulable(float task1_C, float task1_T, float task2_C, float task2_T);
#endif // UTIL_H
