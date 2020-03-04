#ifndef RIMOT_DEBUG_HEADER
#define RIMOT_DEBUG_HEADER

#if !defined(NDEBUG)
/****************************************************************************
** USER CAN ADD THEIR OWN SOURCE MODULE SPECIFIC DEFINITIONS TO ENABLE DEBUGGING
**
** DON'T FORGET TO INCLUDE THE DEBUG HEADER IN EACH MODULE YOU WISH TO DEBUG
*****************************************************************************/

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
#if !defined(NDEBUG)
#define ASSERT(expression) do {                                         \
    if(!(expression))                                                   \
    {                                                                   \
        transmit_serial("ASSERT: ##expression FAILED"                   \
                        "on line %d of %s\n", __LINE__, __FILE__);      \
        while(1)                                                        \
        {                                                               \
        }                                                               \
    }                                                                   \
} while(0);  
#define FORCE_ASSERT ASSERT(0);
#else
#define ASSERT(expression) do {                                         \
    if(!(expression)                                                    \
    {                                                                   \
        transmit_serial("ASSERT: ##expression FAILED"                   \
                        "on line %d of %s. Application will not hang    \
                        because this is not a debug build.\n",          \
                        __LINE__, __FILE__);                            \
    }                                                                   \
}
#endif /* NOT DEFINED NDEBUG */


/* 
**    lowlevel assertion can't necessarily use serial peripherals. 
**    Best we can do is hang in debug build. but in release we can do nothing.
**
**    Test coverage for low level drivers is critically important.
*/
#if !defined(NDEBUG)
#define LL_ASSERT(expression) do {                                      \
    if(!(expression))                                                   \
    {                                                                   \
        while(1)                                                        \
        {                                                               \
        }                                                               \
    }                                                                   \
} while(0); 
#else
/* we cant hang in release and we cant tx because its low-level so just do nothing */
#define LL_ASSERT(expression) do {} while(0); 
#endif /* NOT DEFINED NDEBUG */
#define LL_FORCE_ASSERT LL_ASSERT(0) /* force an assertion. ie: hang forver */


#ifdef DEBUG
#error  DEBUG BUILD IS THE DEFAULT CONFIGURATION. RELEASE BUILDS WITH   \
        -DNDEBUG RATHER THAN DEBUG BUILDING WITH -DDEBUG
#endif /* DEBUG */

#endif /* RIMOT_DEBUG_HEADER */
