/**
 * @file rimot_i2c.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the
 * I2C peripheral on the stm32f411 microcontroller
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


#include "rimot_i2c.h"
#include "rimot_i2c_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define I2C1_BASE (APB1PERIPH_BASE + 0x5400UL)
#define I2C2_BASE (APB1PERIPH_BASE + 0x5800UL)
#define I2C3_BASE (APB1PERIPH_BASE + 0x5C00UL)

struct i2c_regs
{
  volatile uint32_t CR1;        /* Control register 1       */
  volatile uint32_t CR2;        /* Control register 2       */
  volatile uint32_t OAR1;       /* Own address register 1   */
  volatile uint32_t OAR2;       /* Own address register 2   */
  volatile uint32_t DR;         /* Data register            */
  volatile uint32_t SR1;        /* Status register 1        */
  volatile uint32_t SR2;        /* Status register 2        */
  volatile uint32_t CCR;        /* Clock control register   */
  volatile uint32_t TRISE;      /* TRISE register           */
  volatile uint32_t FLTR;       /* FLTR register            */
};

#define _I2C1 ((struct i2c_regs*) I2C1_BASE)
#define _I2C2 ((struct i2c_regs*) I2C2_BASE)
#define _I2C3 ((struct i2c_regs*) I2C3_BASE)

#endif /* !USE_HAL_DRIVER */

void I2C1_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}


void I2C3_EV_IRQHandler(void)
{

}

void I2C3_ER_IRQHandler(void)
{

}


