/**
 * @file rimot_sdio.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the 
 * secure digital i/o functionality of the stm32f411re microcontroller
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

#include "rimot_sdio.h"
#include "rimot_sdio_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#define SDIO_BASE (APB2PERIPH_BASE + 0x2C00UL)

/* PAGE 652, REFERENCE MANUAL */
struct sdio_regs
{
    volatile uint32_t PWR;           /* Power control register */
    volatile uint32_t CLKCR;         /* Clock control register */
    volatile uint32_t ARG;           /* Argument register */
    volatile uint32_t CMD;           /* Command register */
    volatile uint32_t RESPCMD;       /* Command responsse register */
    volatile uint32_t RESP[4];       /* SDIO response register */
    volatile uint32_t DTIMER;        /* Data timeout period register */
    volatile uint32_t DLEN;          /* Data length register */
    volatile uint32_t DCTL;          /* Data control register */
    volatile uint32_t DCNT;          /* Data count register */
    volatile uint32_t STA;           /* Status register */ 
    volatile uint32_t ICR;           /* Int clear reg. Write only. Write bit to "re-arm" */
    volatile uint32_t MSK;           /* Interrupt status bit mask register */
    pad32  RESERVED1[2];  /* Reserved */
    volatile uint32_t FIFOCNT;       /* Fifo counter register */
    volatile uint32_t RESERVED2[13]; /* Reserved */
    volatile uint32_t FIFO;          /* Data FIFO register */
};

#define _SDIO ((struct sdio_regs*) SDIO_BASE)



void SDIO_IRQHandler(void)
{

}

