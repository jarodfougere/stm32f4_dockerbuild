/**
 * @file rimot_cortex_interrupts.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This module provides a Low level driver for functions
 * relating to the control unit on stm32f411 microcontroller.
 * 
 * The mcu control unit is cortex M-4.
 * 
 * @note For declarations of these functions, see the 
 * startup assembly code for the firmware. They are not
 * declared in header files.
 * 
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
 */

#include <stdint.h>

#include "rimot_cortex.h"
#include "rimot_interrupts.h"
#include "rimot_cortex_config.h"


#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

/* 
 * THIS DOES THE AUTOMATIC INCLUSION OF THE COMPILER 
 * BUILT-INS FOR CMSIS COMLPIANCE 
 */
#include "cmsis_compiler.h" 
#include "rimot_LL_debug.h"


static void (*cortexIncTick)(void) = NULL;


void cortexInitSysTick(void (*cbFunc)(void), uint32_t clocksPerSysTickISR)
{
    LL_ASSERT(NULL != cbFunc);
    LL_ASSERT(clocksPerSysTickISR <= SysTick_LOAD_RELOAD_Msk);

    cortexIncTick = cbFunc;
    LL_ASSERT(0 == SysTick_Config(clocksPerSysTickISR));
}


void cortexDisable_Fault_IRQ_Handling(void)
{   
    /* From cmsis-compliant built-in for toolchain */
    __disable_fault_irq(); 
}


void cortexEnable_Fault_IRQ_Handling(void)
{   
    /* From cmsis-compliant built-in for toolchain */
    __enable_fault_irq();  
}


void cortexDisable_Exception_IRQ_Handling(void)
{   
     /* From cmsis-compliant built-in for toolchain */
    __disable_irq();
}


void cortexEnable_Exception_IRQ_Handling(void)
{   
     /* From cmsis-compliant built-in for toolchain */
    __enable_irq();
}



uint32_t cortexGetPriorityMask(void)
{
    return __get_PRIMASK();
}



void cortexSystemReset(void)
{
    NVIC_SystemReset();
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
/******************************************************************************/
/*                          EXCEPTION HANDLERS                                */
/******************************************************************************/
/******************************************************************************/

#if !defined(USE_HAL_DRIVER)

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
    while(1)
    {
        
    }
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
    cortexIncTick();
}

#endif

