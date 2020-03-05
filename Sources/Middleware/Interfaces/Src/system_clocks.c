#include "drivers.h"
#include "system_clocks.h"


static void clock_config_error_handler(void);

/**
 * @brief This function configures the rcc peripheral based on STM32CubeMX 
 * peripheral initialization. It depends on the STM32 HAL APIs
 * 
 */
static void MX_ClockConfig(void);

void system_clock_config(void)
{
#if defined(USE_HAL_DRIVER)
    MX_ClockConfig();
#else
    #error rimot_rcc_config FUNCTION HAS NOT BEEN FULLY COMPLETED IN ##__FILE__
#endif
}


static void rimot_rcc_config(void)
{
    RCC->CFGR |= RCC_CFGR_MCO2_1;

    RCC->CR |= RCC_CR_HSEBYP; /* THE dev board uses the STLink 8MHz MCO as HSE input. it does not use an xtal by default. Thus we bypass clock source */

    if (RCC_CR_HSEBYP != (RCC->CR & RCC_CR_HSEBYP))
    {
        clock_config_error_handler();
    }
}

static void MX_ClockConfig(void)
{    
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
    if(HAL_RCC_ClockConfig(&ClkInit, FLASH_LATENCY_3) != HAL_OK)
    {
        clock_config_error_handler();
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
    if(HAL_RCC_OscConfig(&OscInit) != HAL_OK)
    {
        clock_config_error_handler();
    }

    /* Select the PLL as system clock source and configure the HCLK, PCLK1 and  
     * PCLK2 clocks dividers 
     */
    ClkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    ClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
    ClkInit.APB1CLKDivider = RCC_HCLK_DIV2;
    ClkInit.APB2CLKDivider = RCC_HCLK_DIV1;
    if(HAL_RCC_ClockConfig(&ClkInit, FLASH_LATENCY_3) != HAL_OK)
    {
        clock_config_error_handler();
    }

    /* Optional: Disable HSI Oscillator 
     * (if the HSI is no longer needed by the application) 
     */
    OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    OscInit.HSIState = RCC_HSI_OFF;
    OscInit.PLL.PLLState = RCC_PLL_NONE;
    if(HAL_RCC_OscConfig(&OscInit) != HAL_OK)
    {
        clock_config_error_handler();
    }
}

static void MX_GPIO_Init(void)
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/**
 * @brief This is meant to execute upon clock configuration error
 * 
 */
static void clock_config_error_handler(void)
{
    while(1)
    {
        /* hang forever */
    }
}



void delay_ms(uint32_t ms)
{   
    #if defined(USE_HAL_DRIVER)
    HAL_Delay(ms);
    #else
    #error AN ALTERNATIVE FUNCTION IMPLEMENTATION HAS NOT BEEN PROVIDED TO \
    HAL_Delay in timings.c
    #endif
}
