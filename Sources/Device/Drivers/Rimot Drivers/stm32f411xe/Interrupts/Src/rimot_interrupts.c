/**
 * @file rimot_interrupts.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides driver functionality for 
 * the NVIC and Cortex-M control unit exceptions on the stm32f411
 * microcontroller
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_interrupts.h"
#include "rimot_register_bit_ops.h"
#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

#include "rimot_LL_debug.h"

/* Priority assignment macro */
#define NVIC_SetPrio(code, prio, subprio)                   \
__NVIC_SetPriority(code, NVIC_EncodePriority(               \
                            __NVIC_GetPriorityGrouping(),   \
                                prio,                       \
                                subprio))

/* Do not declare static -> externed in cortex_interrupts.c */
uint32_t tickCount;

uint32_t interruptGetTickCount(void)
{
    return tickCount;
}


void interruptSetPrioGroup(NVIC_PRIO_GROUP_t priorityGroup)
{   
    __NVIC_SetPriorityGrouping(priorityGroup);
}


void interruptSetPriority(  IRQn_Type code, 
                            NVIC_PREEMPTION_PRIO_t preEmption, 
                            NVIC_SUBPRIO_t subprio)
{   
    /* Validate interrupt code */
    switch(code)
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

        /* 
         * KINDA SKEPTICAL ABOUT PUTTING 
         * THE CORTEX CODES HERE.
         * 
         * I HAVE A HARD TIME BELIEVING THAT
         * ALL CORTEX implementaions/ISAs 
         * LET THE SOFTWARE CONFIGURE 
         * THE CORTEX EXCEPTION PREEMPTION
         * PRIORITIES IN THE NVIC...
         */
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
            switch(preEmption)
            {
                case NVIC_PRIO_GROUP_0:
                case NVIC_PRIO_GROUP_1:
                case NVIC_PRIO_GROUP_2:
                case NVIC_PRIO_GROUP_3:
                case NVIC_PRIO_GROUP_4:
                {
                    switch(subprio)
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
                            NVIC_SetPrio(code, preEmption, subprio);
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
        {
            /* 
             * These are valid codes but they
             * are not software configurable 
             */
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
    switch(state)
    {
        case INTERRUPT_STATE_disabled:
        {
            NVIC_EnableIRQ(code);
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






void interruptsInitSystickFreq(uint32_t clocksPerSysTickISR)
{
    LL_ASSERT(0 == SysTick_Config(clocksPerSysTickISR));
}



void PVD_IRQHandler(void)
{

}

void TAMP_STAMP_IRQHandler(void)
{
}



void FPU_IRQHandler(void)
{

}
