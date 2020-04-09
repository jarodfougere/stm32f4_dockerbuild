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
#include "rimot_LL_debug.h"
#include "rimot_region_base_addresses.h"

static uint32_t tickCount;


uint32_t getTick(void)
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
                        case NonMaskableInt_IRQn: 
                        case MemoryManagement_IRQn: 
                        case BusFault_IRQn:      
                        case UsageFault_IRQn:   
                        case SVCall_IRQn:       
                        case DebugMonitor_IRQn:   
                        case PendSV_IRQn:        
                        case SysTick_IRQn: 
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



/**
 * @brief Sets up the minimum configuration in the system control block.
 * @note you wont find this in any of the mainline call tree.
 * It gets called by startup code BEFORE the call to main.
 */
void SystemInit(void)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    /* set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
#endif

#if defined (DATA_IN_ExtSRAM) || defined (DATA_IN_ExtSDRAM)
    SystemInit_ExtMemCtl(); 
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

#ifdef VECT_TAB_SRAM
    /* Vector Table Internal SRAM (Update system control block VTAB alias) */
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; 
#else
    /* Vector Table Internal FLASH (Update system control block VTAB alias) */
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
#endif
}



/******************************************************************************/
/*******************************************************************************
 *                              CORTEX INTERUPTS 
 *
 ******************************************************************************/
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
  * @brief This function handles Debug monitor pause exception.
  * @note for crying out loud if you ever comment this out you can't 
  * actually debug your application. SO DON'T COMMENT IT OUT.
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
    tickCount++;
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
