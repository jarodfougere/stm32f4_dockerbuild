#ifndef RIMOT_MIDDLEWARE_CORE
#define RIMOT_MIDDLEWARE_CORE
#include <stdint.h>

/**
 * @brief Application-facing blocking delay
 * 
 * @param ms 
 */
void delay_ms(uint32_t ms);

/**
 * @brief Get the systick value.
 * 
 * @return uint32_t tick value.
 */
uint32_t get_tick(void);


/**
 * @brief This exposes driver initialization to the application module while still hiding implementation details
 * 
 */
void middleware_init_core(void);


#endif