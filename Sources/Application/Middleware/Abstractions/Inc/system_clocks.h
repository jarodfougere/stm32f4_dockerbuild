#ifndef RIMOT_SYSTEM_CLOCKS
#define RIMOT_SYSTEM_CLOCKS
#include <stdint.h>
#include "debug.h"


/**
 * @brief Initializes the system clocks 
 * 
 */
void system_clock_config(void);


/**
 * @brief Initializes the system clocks and system peripherals
 * 
 */
void sys_init(void);

#endif /* RIMOT_SYSTEM_CLOCKS */