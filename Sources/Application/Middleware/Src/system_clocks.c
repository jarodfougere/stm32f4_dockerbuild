#include "drivers.h"
#include "middleware.h"
#include "system_clocks.h"

static void rimot_rcc_config(void);
static void MX_ClockConfig(void);

void system_clock_config(void)
{
#if defined(USE_HAL_DRIVER)
    MX_ClockConfig();
#else
    rimot_rcc_config();
#endif
}

static void rimot_rcc_config(void)
{
    RCC->CFGR |= RCC_CFGR_MCO2_1;

    RCC->CR |= RCC_CR_HSEBYP; /* THE dev board uses the STLink 8MHz MCO as HSE input. it does not use an xtal by default. Thus we bypass clock source */

    if (RCC_CR_HSEBYP != (RCC->CR & RCC_CR_HSEBYP))
    {
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif
    }
}

static void MX_ClockConfig(void)
{    
    #if 0
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage 
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 72;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 3;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        while(1);
    }
    #endif 


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
    LL_ASSERT(HAL_RCC_ClockConfig(&ClkInit, FLASH_LATENCY_3) == HAL_OK)


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
    LL_ASSERT(HAL_RCC_OscConfig(&OscInit) == HAL_OK)

    /* Select the PLL as system clock source and configure the HCLK, PCLK1 and  
     * PCLK2 clocks dividers 
     */
    ClkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    ClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
    ClkInit.APB1CLKDivider = RCC_HCLK_DIV2;
    ClkInit.APB2CLKDivider = RCC_HCLK_DIV1;
    LL_ASSERT(HAL_RCC_ClockConfig(&ClkInit, FLASH_LATENCY_3) == HAL_OK)

    /* Optional: Disable HSI Oscillator 
     * (if the HSI is no longer needed by the application) 
     */
    OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    OscInit.HSIState = RCC_HSI_OFF;
    OscInit.PLL.PLLState = RCC_PLL_NONE;
    LL_ASSERT(HAL_RCC_OscConfig(&OscInit) == HAL_OK)
}

static void MX_GPIO_Init(void)
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

void sys_init(void)
{
    HAL_Init();

    system_clock_config();
    MX_GPIO_Init();

    //adc_init();
    init_comms_interface();
}
