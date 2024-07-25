#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio.h"
#include "math.h"
#include "utility.h"






void floatToChar(float number, char *buffer, int precision) {

    // Handle the case of a negative number
    if (number < 0) {               // If the number is negative
        *buffer++ = '-';            // Add the negative sign
        number = -number;           // Make the number positive
    }

    // Take the integer part
    int integerPart = (int)number;                              // Integer part
    float decimalPart = number - (float)integerPart;            // Decimal part

    // Convert the integer part            
    sprintf(buffer, "%d", integerPart);                         // Convert the integer part
    // Find the end of the string
    while (*buffer != '\0') {                                   // Search for the end of the string
        buffer++;                                               // Move the pointer
    }

    *buffer++ = '.';                                            // Add the decimal point

    // Convert the decimal part
    for (int i = 0; i < precision; i++) {                       // For the number of decimal places
        decimalPart *= 10;                                      // Multiply the decimal part by 10
        int num = (int)decimalPart;                             // Get the integer part
        *buffer++ = (char)('0' + num);                          // Add the integer part to the string
        decimalPart -= num;                                     // Subtract the integer part from the decimal part
    }

    // Terminate the string
    *buffer = '\0';
}



// Function to check the schedulability of the system
BaseType_t isSchedulable(float task1_C, float task1_T, float task2_C, float task2_T) {
    char buffer[10];
    // Calc the CPU utilization
    float utilization = (task1_C / task1_T) + (task2_C / task2_T) ;
    
    // Check the schedulability
    if (utilization <= 1.0) {
        floatToChar(utilization*100, buffer, 1);
        printf("FEASIBLE CPU UTILIZATION: %s\n", buffer);
        
        return pdTRUE;  // The system is schedulable
    } else {
        floatToChar(utilization*100, buffer, 1);
         printf("NOT FEASIBLE CPU UTILIZATION: %s\n ", buffer);
        return pdFALSE; // The system is not schedulable
    }
}

