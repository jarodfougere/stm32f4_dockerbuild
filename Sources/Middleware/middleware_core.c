/**
 * @file middleware_core.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This file provides core functionality for the middleware module. 
 *         examples of this functionality include driver init wrapping and
 *         conditional compilation / driver selection, delays, RTC, 
 *         timestamps, and tickcounts.
 * @version 0.1
 * @date 2020-03-12
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "middleware_core.h"

#if defined(MCU_APP)
/* low-level drivers */
#include "rimot_flash_ctl.h"
#include "rimot_rcc.h"
#include "rimot_mcu_dbg.h"
#include "rimot_rtc.h"
#include "rimot_iwdg.h"
#include "rimot_wwdg.h"
#include "rimot_power_control.h"
#include "rimot_syscfg.h"
#include "rimot_interrupts.h"
#include "rimot_rtc.h"
#else
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#endif /* PLATFORM SELECTION */


void delay_ms(uint32_t ms)
{
#if defined(MCU_APP)
    uint32_t tickstart = get_tick();
    while((get_tick() - tickstart) < ms)
    {
        /* THIS DELAY IS BLOCKING */

        /** TODO: STOP IF VARIABLE IS ABOUT TO OVERFLOW */
    }
#endif /* MCU APP */
}


uint32_t get_tick(void)
{
    #warning REMEMBER TO FIX get_tick. IT USED TO CONTAIN HAL_GETTICK
    return 0;
}

/*
ADDED FOR REFERENCE  #####
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
*/


/**
 * @brief This initializes the various drivers used by the middleware layer
 */
void middleware_init_core(void)
{
#if defined(MCU_APP)
    flashSetInstructionCacheMode(FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_enabled);
    flashSetPrefetchDataCacheMode(FLASH_PREFETCH_DATA_CACHE_MODE_enabled);
    flashSetPrefetchBuffer(FLASH_PREFETCH_BUFFER_MODE_enabled);

    /* Maximize the number of bits we can preEmpt */
    interruptSetPrioGroup(NVIC_PRIO_GROUP_4);

    /* Enable the systick interrupt */
    interruptSetState(SysTick_IRQn, INTERRUPT_STATE_enabled);

    /* Enable Clock for internal voltage regulator */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_pwr);

    /** TODO: consider enabling the self-calibration voltage trimmer thing in pwr control register */

#else
    printf("CALLED middleware_init_core\n");
#endif /* MCU_APP */
}






