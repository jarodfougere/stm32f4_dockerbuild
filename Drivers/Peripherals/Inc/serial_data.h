#ifndef LOWPOWER_SERIAL_DATA
#define LOWPOWER_SERIAL_DATA
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* WARNING: NOT SURE IF IARCC SUPPORTS VA_ARGS */
void transmit_serial(const char* restrict format, ...);

#endif