#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "serial_data.h"

//Carl TODO: IMPLEMENT PSEUDO OVERLOAD USING WEAK ATTRIBUTE (BUT ADD IAR/GCC SYSTEM COMPAT)


void transmit_serial(const char* restrict format, ...)
{     
    va_list args;
    va_start(args, format);
#if defined(MY_SYSTEM)
    vprintf(format, args);
#elif defined(TARGET_PROCESSOR)
    char data_buf[500];
    vsnprintf(data_buf, sizeof(data_buf), format, args);
    send_data_via_peripheral((const int8_t*)data_buf, min(strlen(data_buf), sizeof(data_buf)));
#else
#   error NETHER >LOCAL_SYSTEM< OR >TARGET_PROCESSOR< HAVE BEEN DEFINED
#endif
}