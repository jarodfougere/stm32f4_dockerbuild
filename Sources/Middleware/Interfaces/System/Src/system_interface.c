#include <string.h>
#include "system_interface.h"

#if defined (MCU_APP)
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
#else 
#error ALTERNATIVE DRIVERS FOR THE SYSTEM INTERFACE HAVE NOT BEEN PROVIDED. \
please see system_inteterface.c
#endif /* MCU_APP */



int doesOutpostIDmatch(const char *id)
{   
#ifndef NDEBUG
        if(NULL == id)
        {
            while(1)
            {
                /* hang forever. caller is an idiot */
            }
        }
#endif /* DEBUG BUILD */

    /*
     * TODO: 
     *  - load outpost ID from EEPROM
     *  - compare with id.
     * 
     *  if equal, return 0,
     * 
     * else return 1
     *
     */


    return 0; 
}