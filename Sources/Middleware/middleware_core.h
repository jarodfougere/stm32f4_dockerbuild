#ifndef RIMOT_MIDDLEWARE_CORE
#define RIMOT_MIDDLEWARE_CORE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#define SYSTICK_FREQ 1000U  /* 1 KHz */

/**
 * @brief Application-facing blocking delay
 * 
 * @param ms 
 */
void delay_ms(uint32_t ms);


/**
 * @brief This exposes driver initialization to the application module while still hiding implementation details
 * 
 */
void middleware_init_core(void);


#if !defined(USE_HAL_DRIVER)
/**
 * @brief using mainline to test driver functions
 * so this function is exposed from midleware core module
 * 
 * @todo: AFTER DRIVER TESTING, THIS FUNCTION
 * SHOULD BE MADE STATIC AND NOT EXPOSED IN HEADER
 */
void sysTickCallBack(void);
#endif /* !USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MIDDLEWARE_CORE */
