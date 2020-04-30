/**
 * @file rimot_exti.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level "driver" for the 
 * external interrupt peripheral on the stm32f411RE microcontroller
 * @version 0.1
 * @date 2020-04-02
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

#include "rimot_exti.h"
#include "rimot_exti_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define EXTI_BASE (APB2PERIPH_BASE + 0x3C00UL)

/* PAGE 208, REFERENCE MANUAL */
struct exti_regs
{
    volatile uint32_t IMR;   /* EXTI Interrupt mask reg         | offset: 0x00    */
    volatile uint32_t EMR;   /* EXTI Event mask reg             | offset: 0x04    */
    volatile uint32_t RTSR;  /* EXTI Rising trig selection reg  | offset: 0x08    */ 
    volatile uint32_t FTSR;  /* EXTI Falling trig selection reg | offset: 0x0C    */ 
    volatile uint32_t SWIER; /* EXTI SW interrupt event reg     | offset: 0x10    */ 
    volatile uint32_t PR;    /* EXTI Pending reg,               | offset: 0x14    */
};

#define _EXTI ((struct exti_regs*) EXTI_BASE)




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


void EXTI9_5_IRQHandler(void)
{

}


void EXTI15_10_IRQHandler(void)
{

}
