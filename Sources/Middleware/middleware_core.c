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


#if defined(MCU_APP)
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
#else
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#endif /* MCU_APP */

static void system_clock_config(void);
static void MX_GPIO_Init(void);
static void gpio_init(void);

#ifdef MCU_APP
static void gpio_init(void)
{
#if defined(USE_HAL_DRIVER)
    MX_GPIO_Init();
#else
#warning gpio_init has not provided a definition for gpio initialization \
independent of stm32 HAL APIS
#endif /* USE_HAL_DRIVER */
}
#endif /* MCU_APP */

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
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}
#endif /* MCU_APP */


static void system_clock_config(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    MX_ClockConfig();
#else
#error rimot_rcc_config FUNCTION HAS NOT BEEN FULLY COMPLETED IN ##__FILE__
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


/**
 * @brief This initializes the various drivers used by the middleware layer
 */
void middleware_init_core(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    HAL_Init();            /* use ST's init API */
    system_clock_config(); /* initialize system clocks */
    gpio_init();           /* initialize the mcu gpios */
#else
#warning drivers_init() func in middleware_core.c does not provide a call \
to an initialization function from the peripheral driver layer
#endif /* USE HAL DRIVER */
#else
    printf("CALLED middleware_init_core\n");
#endif /* MCU_APP */
}


