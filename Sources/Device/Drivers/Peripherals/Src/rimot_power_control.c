/**
 * @file rimot_power_control.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low-level driver for the power control
 * unit on the stm32f411re microcontroller
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

#include "rimot_power_control.h"
#include "rimot_power_control_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_padding.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define PWR_BASE (APB1PERIPH_BASE + 0x7000UL)

/* PAGE 86, REFERENCE MANUAL */
struct pwr_ctl_regs
{
    volatile uint32_t CR;  /* power control register        |  offset: 0x00 */
    volatile uint32_t CSR; /* power control/status register |  offset: 0x04 */
};

#define _PWR ((struct pwr_ctl_regs *)PWR_BASE)

/* Maximum frequency for system clock at power scale1, in Hz */
#define RCC_MAX_FREQUENCY_SCALE1 RCC_MAX_FREQUENCY

/* Maximum frequency for system clock at power scale2, in Hz */
#define RCC_MAX_FREQUENCY_SCALE2 84000000U

/* Maximum frequency for system clock at power scale3, in Hz */
#define RCC_MAX_FREQUENCY_SCALE3 64000000U
