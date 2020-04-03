/**
 * @file analog_measurements.c
 * @author Carl Mattatall
 * @brief This source module provide an "analog measurement" abstraction
 * for modules (such as battery interface and RF interface) at the
 * middleware layer. The abstraction bundles implementation details of
 * the dma and adc peripherals.
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "analog_measurements.h"

#if defined(MCU_APP) /* Cross compiling for the target microcontroller */
#if defined(USE_HAL_DRIVER) /* We want to use the STM32 HAL APIS */
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
ADC_HandleTypeDef hadc1; 
#else  
#include "rimot_adc.h"
#endif /* HAL OR BAREMETAL? */


//TODO: PUT SOMETHING USEFUL HERE
#warning adc_error_handler function doesn't do anythng meaningful and \
hangs forever
static void adc_error_handler(void)
{   
    while(1)
    {
        /* hang forever */
    }
}


/**
 * @brief This function configures the ADC channels to be used by battery 
 * monitoring/rf modules
 * 
 */
static void MX_ADC1_Init(void)
{   
    ADC_ChannelConfTypeDef sConfig = {0};
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if(HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        adc_error_handler();
    }

    /*  Configure for the selected ADC regular channel its corresponding rank 
     *  in the sequencer and its sample time. 
     */
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        adc_error_handler();
    }
}
#endif /* MCU_APP */


void adc_init(void)
{   
#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
    /* for now we are using the STM32HAL APIs. We may write our own in the future to improve performance */
    MX_ADC1_Init();  
#else
    rimot_ADC_init(void);
#endif /* HAL OR BAREMETAL */
#else
#if !defined(NDEBUG)
    printf("executed adc_init in analog_measurements.c\n"
    "The ADC is configured!\n");
#endif /* DEBUG BUILD */
#endif /* RUNNING ON MCU OR HOSTING ON OPERATING SYSTEM? */
}
