#ifndef RIMOT_DEBUG_HEADER
#define RIMOT_DEBUG_HEADER

#if !defined(NDEBUG)
/****************************************************************************
** USER ADDS THEIR OWN SOURCE MODULE SPECIFIC DEFINITIONS TO ENABLE DEBUGGING
**
** DON'T FORGET TO INCLUDE THE DEBUG HEADER IN EACH MODULE YOU WISH TO DEBUG
*****************************************************************************/


//#define MJSON_DEBUG_ENABLE
#define COMMAND_PARSE_DEBUG_ENABLE



#else
#endif /* NOT DEFINED NDEBUG */

#include "serial_data.h"

/* 
    Portable assertion semantic not requiring an assertion header
    WARNING: 
        Will fail if user has not provided a portable
        definition for transmit_serial

        On host systems, transmit_serial (weakly) defaults to printf
*/
#define ASSERT(expression) do {                                     \
    if(!(expression))                                               \
    {                                                               \
        transmit_serial("ASSERT: ##expression FAILED"               \
                        "on line %d of %s\n", __LINE__, __FILE__);  \
        while(1)                                                    \
        {                                                           \
        }                                                           \
    }                                                               \
} while(0);  
#define FORCE_ASSERT ASSERT(0);

#ifdef DEBUG
#error DEBUG BUILD IS THE DEFAULT CONFIGURATION. RELEASE BUILDS WITH -DNDEBUG
#endif /* DEBUG */

#endif /* RIMOT_DEBUG_HEADER */