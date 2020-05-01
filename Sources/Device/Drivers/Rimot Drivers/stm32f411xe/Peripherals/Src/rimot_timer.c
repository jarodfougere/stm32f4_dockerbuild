/**
 * @file rimot_timer.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for
 * interfacing with the timers on the stm32f411re microcontroller
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

#if !defined(USE_HAL_DRIVER)


#include "rimot_timer.h"
#include "rimot_timer_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define TIM1_BASE  (APB2PERIPH_BASE + 0x0000UL)

#define TIM3_BASE  (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE  (APB1PERIPH_BASE + 0x0800UL)

#define TIM2_BASE  (APB1PERIPH_BASE + 0x0000UL)     
#define TIM5_BASE  (APB1PERIPH_BASE + 0x0C00UL)

#define TIM9_BASE  (APB2PERIPH_BASE + 0x4000UL)
#define TIM10_BASE (APB2PERIPH_BASE + 0x4400UL)
#define TIM11_BASE (APB2PERIPH_BASE + 0x4800UL)


/*
 * REFERENCE MANUAL PAGE 287:
 *  - TIM1
 * 
 * REFERENCE MANUAL PAGE 352:
 *  - TIM2 -> TIM5

 * REFERENCE MANUAL PAGE 397:
 *  - TIM9 -> TIM11
 */ 
struct timer_regs
{
  volatile uint32_t CR1;   /* Timer control register 1              */
  volatile uint32_t CR2;   /* Timer control register 2              */
  volatile uint32_t SMCR;  /* Timer slave mode control register     */
  volatile uint32_t DIER;  /* Timer DMA/interrupt enable register   */
  volatile uint32_t SR;    /* Timer status register                 */
  volatile uint32_t EGR;   /* Timer event generation register       */
  volatile uint32_t CCMR1; /* Timer capture/compare mode register 1 */
  volatile uint32_t CCMR2; /* Timer capture/compare mode register 2 */
  volatile uint32_t CCER;  /* Timer capture/compare enable register */
  volatile uint32_t CNT;   /* Timer counter register                */
  volatile uint32_t PSC;   /* Timer prescaler                       */
  volatile uint32_t ARR;   /* Timer auto-reload register            */
  volatile uint32_t RCR;   /* Timer repetition counter register     */
  volatile uint32_t CCR1;  /* Timer capture/compare register 1      */
  volatile uint32_t CCR2;  /* Timer capture/compare register 2      */
  volatile uint32_t CCR3;  /* Timer capture/compare register 3      */
  volatile uint32_t CCR4;  /* Timer capture/compare register 4      */
  volatile uint32_t BDTR;  /* Timer break and dead-time register    */
  volatile uint32_t DCR;   /* Timer DMA control register            */
  volatile uint32_t DMAR;  /* Timer DMA address for full transfer   */
  volatile uint32_t OR;    /* Timer option register                 */
};


#define _TIM1  ((struct timer_regs*) TIM1_BASE)
#define _TIM3  ((struct timer_regs*) TIM3_BASE)
#define _TIM4  ((struct timer_regs*) TIM4_BASE)
#define _TIM2  ((struct timer_regs*) TIM2_BASE)
#define _TIM5  ((struct timer_regs*) TIM5_BASE)
#define _TIM9  ((struct timer_regs*) TIM9_BASE)
#define _TIM10 ((struct timer_regs*) TIM10_BASE)
#define _TIM11 ((struct timer_regs*) TIM11_BASE)





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


void TIM5_IRQHandler(void)
{

}


#endif /* !USE_HAL_DRIVER */
