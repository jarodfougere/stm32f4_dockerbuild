#include "analog_measurements.h"

#if defined(MCU_APP)

#include "drivers.h"


ADC_HandleTypeDef hadc1; 


static void adc_error_handler(void)
{   
    //TODO: PUT SOMETHING USEFUL HERE
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
    /* for now we are using the STM32HAL APIs. We may write our own in the future to improve performance */
    MX_ADC1_Init();  
    #else
    printf("executed adc_init in analog_measurements.c\n"
    "The ADC is configured!\n");
    #endif /* MCU_APP */
}



