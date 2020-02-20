#ifndef RIMOT_SERIAL_DATA
#define RIMOT_SERIAL_DATA
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

                                                       \


/* WARNING: NOT SURE IF IARCC SUPPORTS VA_ARGS */
void transmit_serial(const char* restrict format, ...);
#endif