/**
 * @file rimot_spi.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the SPI peripheral
 * on teh stm32f411re microcontroller
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

#include "rimot_spi.h"
#include "rimot_spi_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_LL_debug.h"

#define SPI1_BASE (APB2PERIPH_BASE + 0x3000UL)
#define SPI2_BASE (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE (APB1PERIPH_BASE + 0x3C00UL)
#define SPI4_BASE (APB2PERIPH_BASE + 0x3400UL)
#define SPI5_BASE (APB2PERIPH_BASE + 0x5000UL)

#define I2S2ext_BASE (APB1PERIPH_BASE + 0x3400UL)
#define I2S3ext_BASE (APB1PERIPH_BASE + 0x4000UL)

/* SPI PERIPHERAL REGISTER STRUCTURE */
struct spi_regs
{
  volatile uint32_t CR1;     /* control register 1 (not used in I2S mode) */
  volatile uint32_t CR2;     /* control register                          */
  volatile uint32_t SR;      /* status register                           */
  volatile uint32_t DR;      /* data register                             */
  volatile uint32_t CRCPR;   /* CRC polynomial reg (not used in I2S mode) */
  volatile uint32_t RXCRCR;  /* RX CRC register (not used in I2S mode)    */
  volatile uint32_t TXCRCR;  /* TX CRC register (not used in I2S mode)    */
  volatile uint32_t I2SCFGR; /* I2S mode configuration register           */
  volatile uint32_t I2SPR;   /* I2S mode prescaler register               */
};

#define _SPI1 ((struct spi_regs*) SPI1_BASE)
#define _SPI2 ((struct spi_regs*) SPI2_BASE)
#define _SPI3 ((struct spi_regs*) SPI3_BASE)
#define _SPI4 ((struct spi_regs*) SPI4_BASE)
#define _SPI5 ((struct spi_regs*) SPI5_BASE)

#define _I2S2ext ((struct spi_regs*) I2S2ext_BASE)
#define _I2S2ext ((struct spi_regs*) I2S2ext_BASE)
#define _I2S3ext ((struct spi_regs*) I2S3ext_BASE)


void SPI1_IRQHandler(void)
{

}

void SPI2_IRQHandler(void)
{

}



void SPI3_IRQHandler(void)
{

}



void SPI4_IRQHandler(void)
{

}

void SPI5_IRQHandler(void)
{
    
}
