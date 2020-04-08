/**
 * @file middleware_core.c
 * @author Carl Mattatall
 * @brief  This file provides core functionality for the middleware module. 
 *         examples of this functionality include driver init wrapping and
 *         conditional compilation / driver selection, delays, RTC, 
 *         timestamps, and tickcounts.
 * @version 0.1
 * @date 2020-03-12
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "middleware_core.h"

/* Cortex Control Unit CMSIS provided fucntions and macros */


#warning DONT FORGET TO REMOVE THESE DRIVERS AND PUT THEM INTO THE DRIVER SELECTION SECTION LATER. COMMENT FROM MIDDLEWARE_CORE.C
/* MOVE THESE LATER */
#include "rimot_flash_ctl.h"
#include "rimot_rcc.h"
#include "rimot_mcu_dbg.h"
#include "rimot_rtc.h"
#include "rimot_iwdg.h"
#include "rimot_wwdg.h"
#include "rimot_power_control.h"
#include "rimot_syscfg.h"
#include "rimot_interrupts.h"
/* END OF MOVE THESE LATER. MOVE ONCE MIDDLEWARE CORE IS STANDALONE */


#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
#else
/* My own low-level drivers */
#include "rimot_flash_ctl.h"
#include "rimot_rcc.h"
#include "rimot_mcu_dbg.h"
#include "rimot_rtc.h"
#include "rimot_iwdg.h"
#include "rimot_wwdg.h"
#include "rimot_power_control.h"
#include "rimot_syscfg.h"
#endif /* DRIVER SELECTION FOR MCU*/
#else
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#endif /* PLATFORM SELECTION */


static void system_clock_config(void);
static void MX_GPIO_Init(void);
static void gpio_init(void);



#ifdef MCU_APP
static void MX_ClockConfig(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /* Configure the main internal regulator output voltage */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 8;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif
    }

    /* Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
    PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
    PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif
    }
}
#endif /* MCU_APP */

#ifdef MCU_APP
static void MX_GPIO_Init(void)
{   
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    
}
#endif /* MCU_APP */


static void system_clock_config(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
#else
#endif /* USE HAL DRIVER */
#else
#endif /* MCU APP */
}



void delay_ms(uint32_t ms)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    HAL_Delay(ms);
#else
#error AN ALTERNATIVE FUNCTION IMPLEMENTATION HAS NOT BEEN PROVIDED TO \
    HAL_Delay in middlware_core.c
#endif /* USE HAL DRIVER */
#else
#warning THE OS-HOSTED FIRMWARE APPLICATION DOES NOT HAVE AN IMPLEMENTATION \
FOR delay_ms in middleware_core.c
#endif /* MCU APP */
}


uint32_t get_tick(void)
{
#if defined(MCU_APP)
    return HAL_GetTick();
#if defined(USE_HAL_DRIVER)
#else
#error AN ALTERNATIVE FUNCTION IMPLEMENTATION HAS NOT BEEN PROVIDED TO \
        get_tick in middleware_core.c
#endif /* USE HAL DRIVER */
#else
#warning THE OS-HOSTED FIRMWARE APPLICATION DOES NOT HAVE AN IMPLEMENTATION \
FOR get_tick in middleware_core.c
#endif /* MCU APP */
}


static void middlewareLLInit(void)
{
    flashSetInstructionCacheMode(FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_enabled);
    flashSetPrefetchDataCacheMode(FLASH_PREFETCH_DATA_CACHE_MODE_enabled);
    flashSetPrefetchBuffer(FLASH_PREFETCH_BUFFER_MODE_enabled);

    /* Maximize the number of bits we can preEmpt */
    interruptSetPrioGroup(NVIC_PRIO_GROUP_4);

    /* Enable the systick interrupt */
    interruptSetState(ISRCODE_SysTick, INTERRUPT_STATE_enabled);

    rccEnableAPB1Clk(RCC_APB1_CLOCK_TYPE_voltageReg, RCC_CLOCKSTATE_enabled);

    /** TODO: consider enabling the self-calibration voltage trimmer thing in pwr control register */


}

/**
 * @brief This initializes the various drivers used by the middleware layer
 */
void middleware_init_core(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)




    #warning DON'T FORGET TO UNCOMMENT THE HAL INIT ONCE YOU FIX LOWLEVEL FLASH AND RCC DRIVERS. THIS COMMENT IS IN MIDDLEWARE_CORE.C
    /*
    HAL_Init();           
    MX_ClockConfig();
    MX_GPIO_Init();
    */


#else
#warning drivers_init() func in middleware_core.c does not provide a call \
to an initialization function from the peripheral driver layer
#endif /* USE HAL DRIVER */
#else
    printf("CALLED middleware_init_core\n");
#endif /* MCU_APP */
}






