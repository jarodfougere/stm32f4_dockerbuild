#ifndef LOWPOWER_SERIAL_DATA
#define LOWPOWER_SERIAL_DATA
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* 
    Portable (albeit not super useful) assertion semantic 
    WARNING: 
        Will fail if user has not provided a portable
        definition for transmit_serial
*/
#define ASSERT(expression) do {                                     \
    if(!(expression))                                               \
    {                                                               \
        while(1)                                                    \
        {                                                           \
            transmit_serial("ASSERTION ##expression FAILED\n");     \
        }                                                           \
    }                                                               \
} while(0);                                                         \


/* WARNING: NOT SURE IF IARCC SUPPORTS VA_ARGS */
void transmit_serial(const char* restrict format, ...);
#endif