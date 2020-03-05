#if defined(MCU_APP)
#include "drivers.h"

ADC_HandleTypeDef hadc1; /* this cannot be made static. Interrupt interrupt handler references the ADC peripheral */
#endif

#include "analog_measurements.h"

static void MX_ADC1_Init(void);

void adc_init(void)
{   
    /* for now we are using the STM32HAL APIs. We may write our own in the future to improve performance */
    MX_ADC1_Init();  
}

static void adc_error_handler(void)
{   
    //TODO: PUT SOMETHING USEFUL HERE
    while(1)
    {
        /* hang forever */
    }
}

static void MX_ADC1_Init(void)
{   
    #if defined(MCU_APP)
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
    #else
    
    #endif
}