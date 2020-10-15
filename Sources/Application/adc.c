/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "gpio.h"


ADC_HandleTypeDef adc1Config;

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

/*
Conversion method - see 11.8.2 and 11.8.3 in reference manual
ADC Configuration
Clock -  
Resolution - 12 bit
Conversion Mode - Single (ScanConvMode = DISABLE)
Conversion Trigger - Software
EOC - Single conversion
Data Alignment - Right
DMA Continuous Requests - DISABLE  (no DMA)
References: 
* stm32f411 reference manual
* ADC_Init() in stm32f4xx_hal_adc.c shows how ADC configuration parameters are handled
*/
  adc1Config.Instance = ADC1;
  adc1Config.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  adc1Config.Init.Resolution = ADC_RESOLUTION_12B;
  adc1Config.Init.ScanConvMode = DISABLE;
  adc1Config.Init.ContinuousConvMode = DISABLE;
  adc1Config.Init.DiscontinuousConvMode = DISABLE;
  adc1Config.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  adc1Config.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  adc1Config.Init.DMAContinuousRequests = DISABLE;
  adc1Config.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

  // HAL_ADC_Init is in stm32f4xx_hal_adc.c
  // It calls HAL_ADC_MspInit (in this file) which configures MCU IO
  // and ADC_Init (in stm32f4xx_hal_adc.c) which configures ADC control
  // registers CR1 and CR2
  if (HAL_ADC_Init(&adc1Config) != HAL_OK)
  {
    Error_Handler();
  }

}

// MCU Analog Inputs
// PA6 - Analog Input 0 - ADC CH 6
// PA7 - Analog Input 1 - ADC CH 7
// PB0 - Analog Input 2 - ADC CH 8
// PB1 - Analog Input 3 - ADC CH 9
// PA0 - RF1 FWD - ADC CH 0
// PA1 - RF1 REF - ADC CH 1
// PA4 - RF2 FWD - ADC CH 4
// PA5 - RF2 REF - ADC CH 5

// Replaces template in stm32f4xx_hal_adc.c
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  
  if(adcHandle->Instance==ADC1)
  {
    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    GPIO_InitStruct.Pin = RF1_FWD_Pin|RF1_REF_Pin|RF2_FWD_Pin|RF2_REF_Pin|BATTERY_0_Pin|BATTERY_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BATTERY_2_Pin|BATTERY_3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
   
   }
}

// Replaces template in stm32f4xx_hal_adc.c
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    HAL_GPIO_DeInit(GPIOA, RF1_FWD_Pin|RF1_REF_Pin|RF2_FWD_Pin|RF2_REF_Pin|BATTERY_0_Pin|BATTERY_1_Pin);

    HAL_GPIO_DeInit(GPIOB, BATTERY_2_Pin|BATTERY_3_Pin);

  }
} 

bool convertAnalogInput(channel, data)
{
    // Start conversion on channel (see stm32f4xx_hal_adc.c)
    //    HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
    // Wait for conversion to complete (see stm32f4xx_hal_adc.c)
    //    HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
    // Read the data (see stm32f4xx_hal_adc.c)
    //    uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
    // Condition the data to millivolts
    // return OK or ERROR

}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
