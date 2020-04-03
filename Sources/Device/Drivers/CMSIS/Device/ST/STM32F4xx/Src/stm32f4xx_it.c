/**
 * @file stm32f4xx_it.c
 * @author Carl Mattatall
 * @brief This source module contains the base interrupt handler functions
 * NAMED IN THE STARTUP CODE for the stm32f411re microcontroller.
 * @note DO NOT CHANGE THE NAME OF THE FUNCTIONS WITHOUT CHANGING THEIR
 * NAMES IN THE STARTUP ASSEMBLY CODE
 * @version 0.1
 * @date 2020-04-03
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

/* Low Level Driver Selection */
#if defined(USE_HAL_DRIVER)
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
#include "stm32f4xx_it.h"

extern PCD_HandleTypeDef  hpcd_USB_OTG_FS;
extern ADC_HandleTypeDef  hadc1;
#else
#warning stm32f4xx_it.c DOES NOT HAVE HEADER FILES FOR BARE METAL PERIPHERALS
#endif



/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/


/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{

    while (1)
    {
        /* Hang forever */
    }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
    while (1)
    {
        /* Hang forever */
    }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
    while (1)
    {
        /* Hang forever */
    }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{

    while (1)
    {
        /* hang forever */
    }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{

}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{

}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
    #if defined(USE_HAL_DRIVER)
    HAL_IncTick();
    #else
    #warning NO BARE METAL FUNCTION PROVIDED FOR SysTick_Handler
    #endif
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

/**
 * @brief This function handles wakeup of the USB Peripheral in OTG mode
 * 
 */
void OTG_FS_WKUP_IRQHandler(void)
{
    /* TODO: System transmits prepared payloads to outpost after ~ 10s */
    #if defined(USE_HAL_DRIVER)
    HAL_Delay(100);
    #else
    #warning NO BARE METAL FUNCTION PROVIDED OTF_FS_WKUP_IRQHANDLER
    #endif 
}

void WWDG_IRQHandler(void)
{

}

void PVD_IRQHandler(void)
{

}

void TAMP_STAMP_IRQHandler(void)
{

}

void RTC_WKUP_IRQHandler(void)
{

}

void FLASH_IRQHandler(void)
{

}

void RCC_IRQHandler(void)
{

}

void EXTI0_IRQHandler(void)
{

}

void EXTI1_IRQHandler(void)
{

}

void EXTI2_IRQHandler(void)
{

}

void EXTI3_IRQHandler(void)
{

}

void EXTI4_IRQHandler(void)
{

}

void DMA1_Stream0_IRQHandler(void)
{

}

void DMA1_Stream1_IRQHandler(void)
{

}

void DMA1_Stream2_IRQHandler(void)
{

}

void DMA1_Stream3_IRQHandler(void)
{

}

void DMA1_Stream4_IRQHandler(void)
{

}

void DMA1_Stream5_IRQHandler(void)
{

}

void DMA1_Stream6_IRQHandler(void)
{

}

void ADC_IRQHandler(void)
{

}

void EXTI9_5_IRQHandler(void)
{

}

void TIM1_BRK_TIM9_IRQHandler(void)
{

}

void TIM1_UP_TIM10_IRQHandler(void)
{

}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{

}

void TIM1_CC_IRQHandler(void)
{

}

void TIM2_IRQHandler(void)
{

}

void TIM3_IRQHandler(void)
{

}

void TIM4_IRQHandler(void)
{

}

void I2C1_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}

void SPI1_IRQHandler(void)
{

}

void SPI2_IRQHandler(void)
{

}

void USART1_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{

}

void EXTI15_10_IRQHandler(void)
{

}

void RTC_Alarm_IRQHandler(void)
{

}


void DMA1_Stream7_IRQHandler(void)
{

}

void SDIO_IRQHandler(void)
{

}

void TIM5_IRQHandler(void)
{

}

void SPI3_IRQHandler(void)
{

}

void DMA2_Stream0_IRQHandler(void)
{

}

void DMA2_Stream1_IRQHandler(void)
{

}

void DMA2_Stream2_IRQHandler(void)
{

}

void DMA2_Stream3_IRQHandler(void)
{

}

void DMA2_Stream4_IRQHandler(void)
{

}

void DMA2_Stream5_IRQHandler(void)
{

}

void DMA2_Stream6_IRQHandler(void)
{

}

void DMA2_Stream7_IRQHandler(void)
{

}

void USART6_IRQHandler(void)
{

}

void I2C3_EV_IRQHandler(void)
{

}

void I2C3_ER_IRQHandler(void)
{

}

void FPU_IRQHandler(void)
{

}

void SPI4_IRQHandler(void)
{

}

void SPI5_IRQHandler(void)
{
    
}
