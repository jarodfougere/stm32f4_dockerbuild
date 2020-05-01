/**
 * @file middleware_core.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This file provides core functionality for the middleware module. 
 *         examples of this functionality include driver init wrapping and
 *         conditional compilation / driver selection, delays, RTC, 
 *         timestamps, and tickcounts.
 * @version 0.1
 * @date 2020-03-12
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <limits.h>
#include <stdint.h>

#include "middleware_core.h"
#if defined(MCU_APP)

/* low-level drivers */
#if defined(USE_HAL_DRIVER)
#include "stm32f4xx_hal.h"

#else
#include "rimot_flash_ctl.h"
#include "rimot_rcc.h"
#include "rimot_mcu_dbg.h"
#include "rimot_gpio.h"
#include "rimot_rtc.h"
#include "rimot_iwdg.h"
#include "rimot_wwdg.h"
#include "rimot_power_control.h"
#include "rimot_syscfg.h"
#include "rimot_interrupts.h"
#include "rimot_cortex.h"
#include "rimot_rtc.h"
#endif /* !USE_HAL_DRIVER */

#else
/* OS HEADERS */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#endif /* PLATFORM SELECTION */

#include "rimot_LL_debug.h"

#if defined(USE_HAL_DRIVER)
#warning THOMAS
/* PUT DEFINITIONS HERE */

#else
#if defined(STM32F411RE) /* Production mcu package */
#define PRESCALE_PLL_Q RCC_PLL_Q_DIV_3
#define PRESCALE_PLL_P RCC_PLL_P_DIV_2
#define PRESCALE_PLL_M 6U
#define PRESCALE_PLL_N 72U
#define PRESCALE_HCLK RCC_HCLK_DIV_1
#define PRESCALE_APB1 RCC_APB_CLK_DIV_2
#define PRESCALE_APB2 RCC_APB_CLK_DIV_1
#elif defined(STM32F411VE) /* Development board mcu package */
#define PRESCALE_PLL_Q RCC_PLL_Q_DIV_3
#define PRESCALE_PLL_P RCC_PLL_P_DIV_2
#define PRESCALE_PLL_M 4U
#define PRESCALE_PLL_N 72U
#define PRESCALE_HCLK RCC_HCLK_DIV_1
#define PRESCALE_APB1 RCC_APB_CLK_DIV_2
#define PRESCALE_APB2 RCC_APB_CLK_DIV_1
#else /* MCU PACKAGE SELECTION */
#error MCU PACKAGE NOT DEFINED
#endif /* MCU_PACKAGE DEFINITION CHECK */
#endif /* USE_HAL_DRIVER */

#if !defined(USE_HAL_DRIVER)
#define DELAY_MS_MAX_DELAY UINT_MAX
static volatile uint32_t tickCnt;
#endif /* !USE_HAL_DRIVER */

#if !defined(USE_HAL_DRIVER)
static void middlewareClockConfigSetSafetyPrescalers(void)
{
#if defined(MCU_APP)
    /* 
     * We set the highest possible HClk dividers so that we dont 
     * cause a hardware fault by transitioning to an illegal 
     * clocking value (exceed min/max threshholds) as part of
     * the configuration stage for application clock scaling
     */

    rcc_set_HClk_Div(RCC_HCLK_DIV_512);
    rcc_set_PLL_M_Div(63);
    rcc_set_PLL_N_Mul(50);
    rcc_set_PLL_P_Div(RCC_PLL_P_DIV_2);
    rcc_set_PLL_Q_Div(RCC_PLL_Q_DIV_2);
    rcc_set_APB_clock_Div(RCC_APB_NUM_1, RCC_APB_CLK_DIV_16);
    rcc_set_APB_clock_Div(RCC_APB_NUM_2, RCC_APB_CLK_DIV_16);
#else
    printf("Executed %s on line %s of %s\n", __func__, __LINE__, __FILE__);
#endif /* MCU_APP */
}
#endif /* !USE_HAL_DRIVER */

#if !defined(USE_HAL_DRIVER)
static void sysTickCallBack(void)
{
    tickCnt++;
}
#endif /* !USE_HAL_DRIVER */

#if !defined(USE_HAL_DRIVER)
/* ### THIS IS A MONITOR FUNCTION ### */
__NOINLINE __attribute__(flatten) static uint32_t getTick(void)
{
    cortexDisable_Exception_IRQ_Handling(); /* Critical section start */
    uint32_t tick = tickCnt;
    cortexEnable_Exception_IRQ_Handling(); /* Critical section end */
    return tick;
}
#endif /* USE_HAL_DRIVER */

void delay_ms(uint32_t ms)
{
    uint32_t tickstart;
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    HAL_Delay(ms);
#else
    tickstart = getTick();
    while ((getTick() - tickstart) < ms)
    {
        /* Wait */
    }
#endif /* USE_HAL_DRIVER */
#else
    tickstart = (uint32_t)clock();
    while ((clock() - tickstart) < ms * CLOCKS_PER_SEC * 1000)
        ;
    printf("Executed %s for %u ms, on line %s of %s\n",
           __func__, ms, __LINE__, __FILE__);
#endif /* MCU APP */
}

static void flashConfig_init(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
#warning THOMAS

    /* PUT HAL IMPLEMENTATION OF CONFIGURING FLASH WAIT CYCLES HERE */

#else
    /* SEE REFERENCE MANUAL PAGE 45 */
#if !defined(NDEBUG)
    flashSetWaitCycles(FLASH_WAIT_CYCLES_10);
#else
    flashSetWaitCycles(FLASH_WAIT_CYCLES_3);
#endif

    /* Configure Cortex exec cycle and ART accellerator mode for pipelining */
    flashSetInstructionCacheMode(FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_enabled);
    flashSetPrefetchDataCacheMode(FLASH_PREFETCH_DATA_CACHE_MODE_enabled);
    flashSetPrefetchBuffer(FLASH_PREFETCH_BUFFER_MODE_enabled);

    /* this has to happen AFTER prefetch and flash funcs are configured */
    interruptSetPrioGroup(NVIC_PRIO_GROUP_4);
#endif /* USE_HAL_DRIVER */
#else
    printf("Executed %s on line %s of %s\n", __func__, __LINE__, __FILE__);
#endif
}

static void periphBusInit(void)
{
#if defined(MCU_APP)

    /* HAL IMPLEMENTATION GOES HERE */

#if defined(USE_HAL_DRIVER)

#else
    /* Enable Clock for internal voltage regulator */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_pwr);

    /* DMA BUS clocks */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_dma1);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_dma2);

    /* USART clocks */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_usart1);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_usart2);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_usart6);

    rccEnablePeriphClock(RCC_PERIPH_CLOCK_syscfg);

    /* Timer peripheral clocks */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim11);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim10);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim9);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim1);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim2);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim3);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim4);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_tim5);

    rcc_set_APB_clock_Div(RCC_APB_NUM_1, PRESCALE_APB1);
    rcc_set_APB_clock_Div(RCC_APB_NUM_2, PRESCALE_APB2);
#endif /* USE_HAL_DRIVER */
#else
    printf("Executed %s on line %s of %s\n", __func__, __LINE__, __FILE__);
#endif
}

static void MCO2_monitorSysClock(void)
{
#if defined(MCU_APP)

    /* HAL IMPLEMENTATION GOES HERE */

#if defined(USE_HAL_DRIVER)
#else
    gpio_enablePinClock(MCUPIN_PC9);
    gpio_setPinMode(MCUPIN_PC9, GPIO_MODE_alternate);
    gpio_setPinAlternateFunc(MCUPIN_PC9, GPIO_ALT_FUNC_0);
    gpio_setPinSpeed(MCUPIN_PC9, GPIO_SPEED_max);
    gpio_setPinPull(MCUPIN_PC9, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSupplyMode(MCUPIN_PC9, GPIO_PIN_SUPPLY_MODE_push_pull);

    /* Divide by 4 so sysclock is viewable on lower-end oscilloscopes */
    rcc_setMCO2_Prescaler(RCC_MCO_PRESCALER_4);

    rcc_setMCO2_Src(RCC_MCO2_SRC_sysclk);
#endif /* USE_HAL_DRIVER */
#endif /* MCU_APP */
}

static void clockConfig(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
#warning THOMAS
#else
    middlewareClockConfigSetSafetyPrescalers();

    rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_hse);
    rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_hsi);
    rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_lsi);
    rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_lse);
    rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_pll);
    rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_plli2s);

    /********************************************/
    /*  IF YOU DON'T WANT TO SUFFER LIKE I DID, */
    /*  READ PAGE 96 OF REFERENCE MANUAL        */
    /********************************************/

#if !defined(NDEBUG)
    MCO2_monitorSysClock();
#endif
    rcc_setHSEmode(RCC_HSE_MODE_feedback);
    LL_ASSERT(0 == rcc_enableHSE());

    /* Setup HSE and PLL */
    rcc_set_PLL_M_Div(PRESCALE_PLL_M);
    rcc_set_PLL_N_Mul(PRESCALE_PLL_N);
    rcc_set_PLL_P_Div(PRESCALE_PLL_P);
    rcc_set_PLL_Q_Div(PRESCALE_PLL_Q);
    rcc_set_HClk_Div(PRESCALE_HCLK);
    rcc_set_PLLSRC(RCC_PLLSRC_hse);
    LL_ASSERT(0 == rcc_enablePLL());

    rcc_set_SysClkSrc(RCC_SYSCLK_SOURCE_pll);
#endif /* USE_HAL_DRIVER */
#else
    printf("Executed %s on line %s of %s\n", __func__, __LINE__, __FILE__);
#endif
}

static void initSysTick(void)
{
#if defined(MCU_APP)
#warning THOMAS
#if defined(USE_HAL_DRIVER)

#else
    cortexInitSysTick(sysTickCallBack, (uint32_t)(rccGetSystemCoreClock() / SYSTICK_FREQ));
    interruptSetPrio(SysTick_IRQn, NVIC_PREEMPTION_PRIO_0, NVIC_SUBPRIO_0);
    interruptSetState(SysTick_IRQn, INTERRUPT_STATE_enabled);
#endif /* USE_HAL_DRIVER */
#else
    printf("Executed %s on line %s of %s\n", __func__, __LINE__, __FILE__);
#endif
}

/**
 * @brief This initializes the clock configuration and other settings required 
 * by drivers in the middleware layer 
 */
void middleware_init_core(void)
{
#if defined(MCU_APP)

#if defined(USE_HAL_DRIVER)

#else
    rccCoreInit();
    rccSystemCoreClockUpdate();
    flashConfig_init();

#if defined(STM32F411VE) /* Turn on Blue LED on eval board */
    gpio_enablePinClock(MCUPIN_PD15);
    gpio_setPinMode(MCUPIN_PD15, GPIO_MODE_output);
    gpio_setPinPull(MCUPIN_PD15, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSpeed(MCUPIN_PD15, GPIO_SPEED_low);
    gpio_setPinSupplyMode(MCUPIN_PD15, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setDigitalPinState(MCUPIN_PD15, GPIO_PIN_STATE_high);
#endif

    clockConfig();
    rccSystemCoreClockUpdate(); /* Update the software-tracked sysClk freqeuncy */
    initSysTick();
    periphBusInit();

#if defined(STM32F411VE) /* Turn on green LED on eval board */
    gpio_enablePinClock(MCUPIN_PD12);
    gpio_setPinMode(MCUPIN_PD12, GPIO_MODE_output);
    gpio_setPinPull(MCUPIN_PD12, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSpeed(MCUPIN_PD12, GPIO_SPEED_max);
    gpio_setPinSupplyMode(MCUPIN_PD12, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setDigitalPinState(MCUPIN_PD12, GPIO_PIN_STATE_high);
#endif
#endif /* USE_HAL_DRIVER */
#else
    printf("Executed %s on line %s of %s\n", __func__, __LINE__, __FILE__);
#endif /* MCU_APP */
}
