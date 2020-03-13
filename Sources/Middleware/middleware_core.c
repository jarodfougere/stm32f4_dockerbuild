/**
 * @file middleware_core.c
 * @author Carl Mattatall
 * @brief  This file provides core functionality for the middleware module. 
 *         examples of this functionality include driver init wrapping and
 *         conditional compilation / driver selection.
 * @version 0.1
 * @date 2020-03-12
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "middleware_core.h"

#if defined(MCU_APP)
#include "drivers.h"
#else
#include "usb_middleware.h" /* for printf debugging / debug messages */
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
/**
 * @brief This function configures the rcc peripheral based on STM32CubeMX 
 * peripheral initialization. It depends on the STM32 HAL APIs
 * 
 */
static void MX_ClockConfig(void)
{

#if 0
    RCC_ClkInitTypeDef ClkInit;
    RCC_OscInitTypeDef OscInit;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /*  Voltage scaling allows optimizing the power consumption when    
     *  the device is clocked below the maximum system frequency (100MHz). 
     * 
     *  To update the voltage scaling value regarding system frequency,
     *  refer to STM32F411 datasheet.  
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /* Select HSI as system clock source to allow modification of the PLL 
     * configuration 
     */
    ClkInit.ClockType = RCC_CLOCKTYPE_SYSCLK;
    ClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    if (HAL_RCC_ClockConfig(&ClkInit, FLASH_LATENCY_3) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif /* DEBUG MODE */
    }

    /* Enable HSE Oscillator, select it as PLL source and finally activate the
     * PLL 
     */
    OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;

    /* CONFIGURE PIN PARAMS FOR XTALin / XTALout. 
     * Bypass : Xtal out (feedback) is Hi-Z
     * On     : Xtal out used to drive the oscillator.
     * 
     * Typically, this means bypass mode is used for a user-provided
     * self-driven oscillator. ie: signal generator or clock IC 
     */
    OscInit.HSEState = RCC_HSE_ON;
    OscInit.HSEState = RCC_HSE_BYPASS;

    /* Connect input clocks to periperal clocks. For proper prescaler values, 
     * see STM32F411 datasheet. 
     */
    OscInit.PLL.PLLState = RCC_PLL_ON;
    OscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    OscInit.PLL.PLLM = 4;
    OscInit.PLL.PLLN = 72;
    OscInit.PLL.PLLP = RCC_PLLP_DIV4;
    OscInit.PLL.PLLQ = 3;
    if (HAL_RCC_OscConfig(&OscInit) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif /* DEBUG MODE */
    }

    /* Select the PLL as system clock source and configure the HCLK, PCLK1 and  
     * PCLK2 clocks dividers 
     */
    ClkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    ClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
    ClkInit.APB1CLKDivider = RCC_HCLK_DIV2;
    ClkInit.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&ClkInit, FLASH_LATENCY_3) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif /* DEBUG MODE */
    }

    /* Optional: Disable HSI Oscillator 
     * (if the HSI is no longer needed by the application) 
     */
    OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    OscInit.HSIState = RCC_HSI_OFF;
    OscInit.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&OscInit) != HAL_OK)
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif /* DEBUG MODE */
    }

#endif
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

/**
 * @brief Initializes the system clocks. 
 * Uses conditional compilation to perform driver selection from
 * private config function calls.
 */
static void system_clock_config(void)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    MX_ClockConfig();
#else
#error rimot_rcc_config FUNCTION HAS NOT BEEN FULLY COMPLETED IN ##__FILE__
#endif /* USE HAL DRIVER */
#else
    usb_printf("executed system clock config in system_clocks.c\n");
#endif /* MCU APP */
}

/**
 * @brief delay (blocking) exposed to the application layer
 * 
 * @param ms The delay duration in milliseconds
 */
void delay_ms(uint32_t ms)
{
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    HAL_Delay(ms);
#else
#error AN ALTERNATIVE FUNCTION IMPLEMENTATION HAS NOT BEEN PROVIDED TO \
    HAL_Delay in timings.c
#endif /* USE HAL DRIVER */
#else
#endif /* MCU APP */
}

/**
 * @brief This initializes the various drivers used by the middleware layer
 */
void middleware_init(void)
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
    printf("CALLED MIDDLEWARE_INIT\n");
#endif /* MCU_APP */
}
