
#include <stdint.h>
#include <limits.h>

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"

extern TIM_HandleTypeDef htim3;
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

void NMI_Handler(void)
{}


void HardFault_Handler(void)
{

    while (1)
    {
    }
}


void MemManage_Handler(void)
{

    while (1)
    {
    }
}


void BusFault_Handler(void)
{
    while (1)
    {
    }
}

void UsageFault_Handler(void)
{
    while (1)
    {
    }
}

/******************************************************************************/
/*                      PERIPHERAL INTERRUPTS                                 */
/*          For the available peripheral interrupt handler names              */
/*          please refer to the startup file (startup_stm32f4xx.S).           */
/*              (or just refer to the device reference manual)                */
/******************************************************************************/

void OTG_FS_IRQHandler(void)
{
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}


void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim3);
}
