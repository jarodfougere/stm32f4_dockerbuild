#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "serial_data.h"



void transmit_serial(const char* restrict format, ...)
{   
    va_list args;
    va_start(args, format);
#if defined(MCU_APP)
    const char msg_delim[] = "\r\n";
    char data_buf[500];
    vsnprintf(data_buf, sizeof(data_buf) - strlen(msg_delim), format, args);

    /* put serial rx delimiter on the end of message */
    if(NULL == strstr(data_buf, msg_delim))
    {
        strcat(data_buf, msg_delim);
    }

    //USER ADDS THEIR IMPLEMENTATION OF SERIAL TRANSMISSION USING MCU PERIPHERAL
#else
    vprintf(format, args);
#endif
}


