/**
 * @file rimot_rtc.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the real
 * time clock on the stm32f411re microcontroller
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

#include "rimot_rtc.h"
#include "rimot_rtc_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define RTC_BASE (APB1PERIPH_BASE + 0x2800UL)

/* REAL TIME CLOCK REGISTERS */
struct rtc_regs
{
  volatile uint32_t TR;         /* time register                           */
  volatile uint32_t DR;         /* date register                           */
  volatile uint32_t CR;         /* control register                        */
  volatile uint32_t ISR;        /* initialization and status register      */
  volatile uint32_t PRER;       /* prescaler register                      */
  volatile uint32_t WUTR;       /* wakeup timer register                   */
  volatile uint32_t CALIBR;     /* calibration register                    */
  volatile uint32_t ALRMAR;     /* alarm A register                        */
  volatile uint32_t ALRMBR;     /* alarm B register                        */
  volatile uint32_t WPR;        /* write protection register               */
  volatile uint32_t SSR;        /* sub second register                     */
  volatile uint32_t SHIFTR;     /* shift control register                  */
  volatile uint32_t TSTR;       /* time stamp time register                */
  volatile uint32_t TSDR;       /* time stamp date register                */
  volatile uint32_t TSSSR;      /* time-stamp sub second register          */
  volatile uint32_t CALR;       /* calibration register                    */
  volatile uint32_t TAFCR;      /* tamper and alt function config register */
  volatile uint32_t ALRMASSR;   /* alarm A sub second register             */
  volatile uint32_t ALRMBSSR;   /* alarm B sub second register             */
  pad32 RESERVED;    /* Reserved                                */
  volatile uint32_t BKPR[20];   /* Backup registers                        */
};

#define _RTC ((struct rtc_regs*) RTC_BASE)


#if !defined(USE_HAL_DRIVER)

void RTC_WKUP_IRQHandler(void)
{

}

void RTC_Alarm_IRQHandler(void)
{

}


#endif