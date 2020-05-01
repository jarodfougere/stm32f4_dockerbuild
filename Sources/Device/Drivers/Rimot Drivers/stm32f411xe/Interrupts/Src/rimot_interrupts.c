/**
 * @file rimot_interrupts.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides driver functionality for 
 * the NVIC and Cortex-M control unit exceptions on the stm32f411
 * microcontroller
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. 
 * 
 * 
 * @todo Cortex and interrupt module functions are kinda tangled
 */

#include "rimot_interrupts.h"
#include "rimot_cortex_config.h"
#include "rimot_cortex.h"

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"
#include "rimot_LL_debug.h"

void interruptSetPrioGroup(NVIC_PRIO_GROUP_t priorityGroup)
{
    switch (priorityGroup)
    {
    case NVIC_PRIO_GROUP_0:
    case NVIC_PRIO_GROUP_1:
    case NVIC_PRIO_GROUP_2:
    case NVIC_PRIO_GROUP_3:
    case NVIC_PRIO_GROUP_4:
    {
        __NVIC_SetPriorityGrouping(priorityGroup);
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void interruptSetPrio(IRQn_Type code,
                      NVIC_PREEMPTION_PRIO_t preEmption,
                      NVIC_SUBPRIO_t subprio)
{
    /* Validate interrupt code */
    switch (code)
    {
    case WWDG_IRQn:
    case PVD_IRQn:
    case TAMP_STAMP_IRQn:
    case RTC_WKUP_IRQn:
    case FLASH_IRQn:
    case RCC_IRQn:
    case EXTI0_IRQn:
    case EXTI1_IRQn:
    case EXTI2_IRQn:
    case EXTI3_IRQn:
    case EXTI4_IRQn:
    case DMA1_Stream0_IRQn:
    case DMA1_Stream1_IRQn:
    case DMA1_Stream2_IRQn:
    case DMA1_Stream3_IRQn:
    case DMA1_Stream4_IRQn:
    case DMA1_Stream5_IRQn:
    case DMA1_Stream6_IRQn:
    case ADC_IRQn:
    case EXTI9_5_IRQn:
    case TIM1_BRK_TIM9_IRQn:
    case TIM1_UP_TIM10_IRQn:
    case TIM1_TRG_COM_TIM11_IRQn:
    case TIM1_CC_IRQn:
    case TIM2_IRQn:
    case TIM3_IRQn:
    case TIM4_IRQn:
    case I2C1_EV_IRQn:
    case I2C1_ER_IRQn:
    case I2C2_EV_IRQn:
    case I2C2_ER_IRQn:
    case SPI1_IRQn:
    case SPI2_IRQn:
    case USART1_IRQn:
    case USART2_IRQn:
    case EXTI15_10_IRQn:
    case RTC_Alarm_IRQn:
    case OTG_FS_WKUP_IRQn:
    case DMA1_Stream7_IRQn:
    case SDIO_IRQn:
    case TIM5_IRQn:
    case SPI3_IRQn:
    case DMA2_Stream0_IRQn:
    case DMA2_Stream1_IRQn:
    case DMA2_Stream2_IRQn:
    case DMA2_Stream3_IRQn:
    case DMA2_Stream4_IRQn:
    case OTG_FS_IRQn:
    case DMA2_Stream5_IRQn:
    case DMA2_Stream6_IRQn:
    case DMA2_Stream7_IRQn:
    case USART6_IRQn:
    case I2C3_EV_IRQn:
    case I2C3_ER_IRQn:
    case FPU_IRQn:
    case SPI4_IRQn:
    case SPI5_IRQn:
    case NonMaskableInt_IRQn:
    case MemoryManagement_IRQn:
    case BusFault_IRQn:
    case UsageFault_IRQn:
    case SVCall_IRQn:
    case DebugMonitor_IRQn:
    case PendSV_IRQn:
    case SysTick_IRQn:
    {
        /* Validate priority group */
        switch (preEmption)
        {
        case NVIC_PREEMPTION_PRIO_0:
        case NVIC_PREEMPTION_PRIO_1:
        case NVIC_PREEMPTION_PRIO_2:
        case NVIC_PREEMPTION_PRIO_3:
        case NVIC_PREEMPTION_PRIO_4:
        case NVIC_PREEMPTION_PRIO_5:
        case NVIC_PREEMPTION_PRIO_6:
        case NVIC_PREEMPTION_PRIO_7:
        case NVIC_PREEMPTION_PRIO_8:
        case NVIC_PREEMPTION_PRIO_9:
        case NVIC_PREEMPTION_PRIO_10:
        case NVIC_PREEMPTION_PRIO_11:
        case NVIC_PREEMPTION_PRIO_12:
        case NVIC_PREEMPTION_PRIO_13:
        case NVIC_PREEMPTION_PRIO_14:
        case NVIC_PREEMPTION_PRIO_15:
        {
            switch (subprio)
            {
            case NVIC_SUBPRIO_0:
            case NVIC_SUBPRIO_1:
            case NVIC_SUBPRIO_2:
            case NVIC_SUBPRIO_3:
            case NVIC_SUBPRIO_4:
            case NVIC_SUBPRIO_5:
            case NVIC_SUBPRIO_6:
            case NVIC_SUBPRIO_7:
            case NVIC_SUBPRIO_8:
            case NVIC_SUBPRIO_9:
            case NVIC_SUBPRIO_10:
            case NVIC_SUBPRIO_11:
            case NVIC_SUBPRIO_12:
            case NVIC_SUBPRIO_13:
            case NVIC_SUBPRIO_14:
            case NVIC_SUBPRIO_15:
            {
                /* Yeah it looks ugly but its inside 80 chars */
                __NVIC_SetPriority(code,
                                   NVIC_EncodePriority(
                                       __NVIC_GetPriorityGrouping(),
                                       preEmption,
                                       subprio));
            }
            break;
            default:
            {
                LL_ASSERT(0);
            }
            break;
            }
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        }
    }
    break;
    default:
    {
        /* Error on behalf of caller */
        LL_ASSERT(0);
    }
    break;
    }
}

void interruptSetState(IRQn_Type code, INTERRUPT_STATE_t state)
{
    switch (state)
    {
    case INTERRUPT_STATE_disabled:
    {
        NVIC_DisableIRQ(code);
    }
    break;
    case INTERRUPT_STATE_enabled:
    {
        NVIC_EnableIRQ(code);
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

#if !defined(USE_HAL_DRIVER)

/** @todo I DON'T KNOW WHERE I SHOULD PUT THESE 3 IN TERMS OF MODULE DESIGN */

void PVD_IRQHandler(void)
{
}

void TAMP_STAMP_IRQHandler(void)
{
}

void FPU_IRQHandler(void)
{
}

#endif