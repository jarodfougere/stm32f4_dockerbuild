#ifndef LOWPOWER_GPIO
#define LOWPOWER_GPIO
#include <stdint.h>

#define __IO volatile
#include "stm32f303x8.h"
/*
COMMENT DESCRIBING WHAT THE MODULE DOES.
IT CAN BE BRIEF.

INCLUDE THIS HEADER TO HAVE ACCESS TO THE GPIO PERIPHERAL DRIVER FOR THE 
LOW POWER SENSOR CARD

##### LIST THE FUNCTIONS IN THE HEADER #####


*/


/* CONSTANT DEFINES */

/* FUNCTION-LIKE DEFINES */

/* 
JAROD TODO: 
            - MACRO TO TEST IF GPIO REGISTER IS LOCKED
            - 
*/


/* ENUMS */
typedef enum PIN_LEVEL
{
    PIN_LEVEL_low  = 0,
    PIN_LEVEL_high = 1,
}   PIN_LEVEL_t;



/* AGGREGATE TYPES (STRUCT, UNIONS) */


/* FUNCTION PROTOTYPES */

/* write the bits (PARAM2) of the gpio port (@PARAM1) to level (@PARAM3) */
void writePin(GPIO_TypeDef* port, uint32_t bit, PIN_LEVEL_t level);


#endif