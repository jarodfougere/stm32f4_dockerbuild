#ifndef RIMOT_SYSTEM_CLOCKS
#define RIMOT_SYSTEM_CLOCKS
#include <stdint.h>


/**
 * @brief Initializes the system clocks 
 * 
 */
void system_clock_config(void);


/**
 * @brief Application-facing blocking delay
 * 
 * @param ms 
 */
void delay_ms(uint32_t ms);


#endif /* RIMOT_SYSTEM_CLOCKS */