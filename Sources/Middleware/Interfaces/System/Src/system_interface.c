#include <string.h>
#include "system_interface.h"

#if defined (MCU_APP)
#warning NO BAREMETAL DRIVER HAS BEEN INCLUDED IN THIS MODULE YET. 
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

    /**
      * @todo 
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

