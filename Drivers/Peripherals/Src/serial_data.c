#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "serial_data.h"

//Carl TODO: IMPLEMENT PSEUDO OVERLOAD USING WEAK ATTRIBUTE (BUT ADD IAR/GCC SYSTEM COMPAT)

void transmit_serial(const char* restrict format, ...)
{   
    if(format != NULL)
    {
#if defined(LOCAL_SYSTEM)
    printf(format, ...);
#elif defined(TARGET_PROCESSOR)
    char data_buf[500];
    snprintf(data_buf, sizeof(data_buf), format, ...);
    send_data_via_peripheral((const int8_t*)data_buf, min(strlen(data_buf), sizeof(data_buf)));
#else
#   error NETHER >LOCAL_SYSTEM< OR >TARGET_PROCESSOR< HAVE BEEN DEFINED
#endif
    }
}
