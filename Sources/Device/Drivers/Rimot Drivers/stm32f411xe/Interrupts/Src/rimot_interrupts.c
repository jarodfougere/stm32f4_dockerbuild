#warning NO DOXYGEN HEADER IN RIMOT_INTERRUPTS.C

#include "rimot_interrupts.h"
#include "rimot_register_bit_ops.h"
#include "rimot_register_field_sizes.h"
#include "core_cm4.h" 
#include "rimot_LL_debug.h"

void interruptSetPrioGroup(NVIC_PRIO_GROUP_t priorityGroup)
{   
    /* FOR NOW I'M JUST MAXING THE POSSIBLE BITCOUNT TO ASSIGN INTERUPT PRIOS */

    /* 
       If caller does interruptSetPriority and prio group is not group 4, 
       chip could potentially lock up. 

       If you're maintaining this, be very careful about touchign this file
       in general.
    */
    __NVIC_SetPriorityGrouping(priorityGroup);
}


void interruptSetPriority(  ISRCODE_t code, 
                            NVIC_PREEMPTION_PRIO_t preEmption, 
                            NVIC_SUBPRIO_t subprio)
{   
    /* Validate interrupt code */
    switch(code)
    {
        case ISRCODE_WWDG: 
        case ISRCODE_PVD: 
        case ISRCODE_TAMP_STAMP: 
        case ISRCODE_RTC_WKUP:  
        case ISRCODE_FLASH:  
        case ISRCODE_RCC:  
        case ISRCODE_EXTI0:  
        case ISRCODE_EXTI1:  
        case ISRCODE_EXTI2:  
        case ISRCODE_EXTI3:  
        case ISRCODE_EXTI4:  
        case ISRCODE_DMA1_Stream0:  
        case ISRCODE_DMA1_Stream1:  
        case ISRCODE_DMA1_Stream2:  
        case ISRCODE_DMA1_Stream3:  
        case ISRCODE_DMA1_Stream4:  
        case ISRCODE_DMA1_Stream5:  
        case ISRCODE_DMA1_Stream6:  
        case ISRCODE_ADC:  
        case ISRCODE_EXTI9_5:  
        case ISRCODE_TIM1_BRK_TIM9:  
        case ISRCODE_TIM1_UP_TIM10:  
        case ISRCODE_TIM1_TRG_COM_TIM11:  
        case ISRCODE_TIM1_CC:  
        case ISRCODE_TIM2:  
        case ISRCODE_TIM3:  
        case ISRCODE_TIM4:  
        case ISRCODE_I2C1_EV:  
        case ISRCODE_I2C1_ER:  
        case ISRCODE_I2C2_EV:  
        case ISRCODE_I2C2_ER:  
        case ISRCODE_SPI1:  
        case ISRCODE_SPI2:  
        case ISRCODE_USART1:  
        case ISRCODE_USART2:  
        case ISRCODE_EXTI15_10:  
        case ISRCODE_RTC_Alarm:  
        case ISRCODE_OTG_FS_WKUP:  
        case ISRCODE_DMA1_Stream7:  
        case ISRCODE_SDIO:  
        case ISRCODE_TIM5:  
        case ISRCODE_SPI3:  
        case ISRCODE_DMA2_Stream0:  
        case ISRCODE_DMA2_Stream1:  
        case ISRCODE_DMA2_Stream2:  
        case ISRCODE_DMA2_Stream3:  
        case ISRCODE_DMA2_Stream4:  
        case ISRCODE_OTG_FS:  
        case ISRCODE_DMA2_Stream5:  
        case ISRCODE_DMA2_Stream6:  
        case ISRCODE_DMA2_Stream7:  
        case ISRCODE_USART6:  
        case ISRCODE_I2C3_EV:  
        case ISRCODE_I2C3_ER:  
        case ISRCODE_FPU:  
        case ISRCODE_SPI4:  
        case ISRCODE_SPI5:  
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
                        case ISRCODE_NonMaskableInt: 
                        case ISRCODE_MemoryManagement: 
                        case ISRCODE_BusFault:      
                        case ISRCODE_UsageFault:   
                        case ISRCODE_SVCall:       
                        case ISRCODE_DebugMonitor:   
                        case ISRCODE_PendSV:        
                        case ISRCODE_SysTick: 
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
                            return;
                        }
                        break;
                    }
                }
                break;
                default:
                {
                    LL_ASSERT(0);
                    return;
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
            return;
        } 
        break;
    }
}


void interruptSetState(ISRCODE_t code, INTERRUPT_STATE_t state)
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


