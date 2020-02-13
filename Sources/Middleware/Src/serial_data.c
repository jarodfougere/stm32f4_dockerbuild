#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "serial_data.h"


// JAROD TODO: MOVE THIS TO PERIPHERAL MODULE AND ACTUALLY SPECIFY A PERIPH FOR SERIAL DATA (EG: UART, USB, ETC...)
void send_data_via_peripheral(const int8_t *data_buf, size_t len)
{
    printf("CALLING send_data_via_peripheral. USER MUST DEFINE THIS FUNCTION ON A PER-CHIPSET BASIS\n");
}


void transmit_serial(const char* restrict format, ...)
{   
    const char msg_delim[] = "\r\n";
    va_list args;
    va_start(args, format);
#if defined(MCU_APP)
    char data_buf[500];
    vsnprintf(data_buf, sizeof(data_buf) - strlen(msg_delim), format, args);    //-2 because room for cr/lf delimiter

    /* put serial rx delimiter on the end of message */
    if(NULL == strstr(data_buf, msg_delim))
    {
        strcat(data_buf, msg_delim);
    }
    send_data_via_peripheral((const int8_t*)data_buf, sizeof(data_buf));
#else
    vprintf(format, args);
#endif
}


