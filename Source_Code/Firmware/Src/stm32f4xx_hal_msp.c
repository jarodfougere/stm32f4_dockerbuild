/**
 * @file stm32f4xx_hal_msp.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-10-07
 *
 * @copyright Copyright (c) 2020
 *
 * @note
 * @todo
 */

#include <stdint.h>
#include <limits.h>

#include "stm32f4xx_hal.h"


void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    // HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
}
