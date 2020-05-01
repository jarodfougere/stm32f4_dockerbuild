/**
 * @file rimot_syscfg.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level interface for 
 * configuring the syscfg registers on the stm32f411re microcontroller
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

#include <stdint.h>

#include "rimot_syscfg.h"
#include "rimot_syscfg_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define SYSCFG_BASE (APB2PERIPH_BASE + 0x3800UL)

/* PAGE 139 REFERENCE MANUAL */
struct syscfg_regs
{
    volatile uint32_t MEMRMP;    /*  memory remap register               */
    volatile uint32_t PMC;       /* peripheral mode config register      */
    volatile uint32_t EXTICR[4]; /* ext interrupt config registers       */
    pad32 RESERVED[2];           /* Reserved                             */
    volatile uint32_t CMPCR;     /* Compensation cell control register   */
};

#define _SYSCFG ((struct syscfg_regs *)SYSCFG_BASE)

#endif /* !USE_HAL_DRIVER */
