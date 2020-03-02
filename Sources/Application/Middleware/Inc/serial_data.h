#ifndef RIMOT_SERIAL_DATA
#define RIMOT_SERIAL_DATA
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

enum comms_interface
{
    USB_serial,
    UART_serial,
    I2C_serial
};

/* WARNING: NOT SURE IF IARCC SUPPORTS VA_ARGS */
void transmit_serial(const char* restrict format, ...);



void init_comms_interface(void);
#endif
