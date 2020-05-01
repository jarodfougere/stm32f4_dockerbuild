/**
 * @file rimot_rcc.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the 
 * reset and clock controller on the stm32f411re microcontroller
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

/**
 * @todo 
 * - functionality to enable / disable busses 
 *   when chip is in low power mode
 *
 *
 * 
 */

#include <stdint.h>
#include <limits.h> /* CHAR BIT */
#include <string.h>

#include "rimot_bus_region_offsets.h"
#include "rimot_register_padding.h"
#include "rimot_interrupts.h"
#include "rimot_cortex.h"
#include "rimot_cortex_config.h"
#include "rimot_rcc.h"
#include "rimot_rcc_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#define RCC_MAX_PLL_N_MUL 432
#define RCC_MIN_PLL_N_MUL 50
#define RCC_MIN_PLL_M_DIV 2
#define RCC_MAX_PLL_M_DIV 63

/* 
 * At bootup, internal RC oscillator (16MHz) is system clock
 * 
 * This variable contains is the sysClk frequency in Hz.
 * 
 * DO NOT RENAME. VARIABLE IS GLOBAL. 
 */
uint32_t SystemCoreClock = HSI_VALUE;

#define RCC_CLOCK_COUNT_STABILIZATION_MAX_COUNTS 200000UL
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)
/* PAGE 102, REFERENCE MANUAL */
struct rcc_regs
{
    volatile uint32_t CR;         /* Clock control register                   */
    volatile uint32_t PLLCFGR;    /* PLL configuration register               */
    volatile uint32_t CFGR;       /* Clock configuration register             */
    volatile uint32_t CIR;        /* Clock interrupt register                 */
    volatile uint32_t AHB1RSTR;   /* AHB1 peripheral reset register           */
    volatile uint32_t AHB2RSTR;   /* AHB2 peripheral reset register           */
    volatile uint32_t AHB3RSTR;   /* AHB3 peripheral reset register           */
    uint32_t RESERVED0;           /* Reserved                                 */
    volatile uint32_t APB1RSTR;   /* APB1 peripheral reset register           */
    volatile uint32_t APB2RSTR;   /* APB2 peripheral reset register           */
    uint32_t RESERVED1;           /* Reserved                                 */
    uint32_t RESERVED2;           /* Reserved                                 */
    volatile uint32_t AHB1ENR;    /* AHB1 peripheral clock register           */
    volatile uint32_t AHB2ENR;    /* AHB2 peripheral clock register           */
    volatile uint32_t AHB3ENR;    /* AHB3 peripheral clock register           */
    uint32_t RESERVED3;           /* Reserved                                 */
    volatile uint32_t APB1ENR;    /* APB1 peripheral clock enable register    */
    volatile uint32_t APB2ENR;    /* APB2 peripheral clock enable register    */
    uint32_t RESERVED4;           /* Reserved                                 */
    uint32_t RESERVED5;           /* Reserved                                 */
    volatile uint32_t AHB1LPENR;  /* AHB1 periph clock enable in LPM register */
    volatile uint32_t AHB2LPENR;  /* AHB2 periph clock enable in LPM register */
    volatile uint32_t AHB3LPENR;  /* AHB3 periph clock enable in LPM register */
    uint32_t RESERVED6;           /* Reserved                                 */
    volatile uint32_t APB1LPENR;  /* APB1 periph clk enable in LPM register   */
    volatile uint32_t APB2LPENR;  /* APB2 periph clk enable in LPM register   */
    uint32_t RESERVED7;           /* Reserved                                 */
    uint32_t RESERVED8;           /* Reserved                                 */
    volatile uint32_t BDCR;       /* Backup domain control register           */
    volatile uint32_t CSR;        /* Clock control & status register          */
    uint32_t RESERVED9;           /* Reserved                                 */
    uint32_t RESERVED10;          /* Reserved                                 */
    volatile uint32_t SSCGR;      /* Spread spectrum clock gen register       */
    volatile uint32_t PLLI2SCFGR; /* PLLI2S configuration register            */
    uint32_t RESERVED11;          /* Reserved                                 */
    volatile uint32_t DCKCFGR;    /* Dedicated Clocks configuration register  */
};

/* Instance */
#define _RCC ((struct rcc_regs *)RCC_BASE)

#define RCC_PLLCFGR_RST_VALUE 0x24003010U
#define RCC_PLLI2SCFGR_RST_VALUE 0x20003010U

/* Max frequency of family in Hz */
#define RCC_MAX_FREQUENCY 100000000U

/* Frequency min for PLLVCO output, in Hz */
#define RCC_PLLVCO_OUTPUT_MIN 100000000U

/* Frequency min for PLLVCO input, in Hz */
#define RCC_PLLVCO_INPUT_MIN 950000U

/* Frequency max for PLLVCO input, in Hz */
#define RCC_PLLVCO_INPUT_MAX 2100000U

/* Frequency max for PLLVCO output, in Hz */
#define RCC_PLLVCO_OUTPUT_MAX 432000000U

#define RCC_PLLN_MIN_VALUE 50U
#define RCC_PLLN_MAX_VALUE 432U

struct rdyflags
{
    char PLL;
    char PLLI2S;
    char HSE;
    char HSI;
    char LSI;
    char LSE;
};

static volatile struct rdyflags readyflags =
    {
        .PLL = 0,
        .PLLI2S = 0,
        .HSE = 0,
        .HSI = 0,
        .LSI = 0,
        .LSE = 0,
};

/* See page 104 reference manual */
/* Maps value of HPRE bits to prescaler value on SYSCLK -> HPREDIV -> HCLK */
static const uint32_t HCLK_DIV_TBL[] =
    {
        /* Invalid values */
        [RCC_HCLK_DIV_1] = 1,
        [1] = 1,
        [2] = 1,
        [3] = 1,
        [4] = 1,
        [5] = 1,
        [6] = 1,
        [7] = 1,

        /* Valid values */
        [RCC_HCLK_DIV_2] = 2,
        [RCC_HCLK_DIV_4] = 4,
        [RCC_HCLK_DIV_8] = 8,
        [RCC_HCLK_DIV_16] = 16,
        [RCC_HCLK_DIV_64] = 64,
        [RCC_HCLK_DIV_128] = 128,
        [RCC_HCLK_DIV_256] = 256,
        [RCC_HCLK_DIV_512] = 512,
};

/* Maps val of PREPRE bits to prescaler value on HCLK -> PREPREDIV -> APBCLK */
static const uint32_t APBCLK_DIV_TBL[] =
    {
        /* Invalid values */
        [RCC_APB_CLK_DIV_1] = 1,
        [1] = 1,
        [2] = 1,
        [3] = 1,

        /* Valid values */
        [RCC_APB_CLK_DIV_2] = 2,
        [RCC_APB_CLK_DIV_4] = 4,
        [RCC_APB_CLK_DIV_8] = 8,
        [RCC_APB_CLK_DIV_16] = 16,
};

static const uint32_t PLLP_DIV_TBL[] =
    {
        [RCC_PLL_P_DIV_2] = 2,
        [RCC_PLL_P_DIV_4] = 4,
        [RCC_PLL_P_DIV_6] = 6,
        [RCC_PLL_P_DIV_8] = 8,
};

void rccEnablePeriphClock(RCC_PERIPH_CLOCK_t periph_clock)
{
    switch (periph_clock)
    {
    case RCC_PERIPH_CLOCK_adc:
    {
        _RCC->APB2ENR |= (APB2ENR_ADC1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioa:
    {
        _RCC->AHB1ENR |= (AHB1ENR_GPIOAEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpiob:
    {
        _RCC->AHB1ENR |= (AHB1ENR_GPIOBEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioc:
    {
        _RCC->AHB1ENR |= (AHB1ENR_GPIOCEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpiod:
    {
        _RCC->AHB1ENR |= (AHB1ENR_GPIODEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioe:
    {
        _RCC->AHB1ENR |= (AHB1ENR_GPIOEEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioh:
    {
        _RCC->AHB1ENR |= (AHB1ENR_GPIOHEN);
    }
    break;
    case RCC_PERIPH_CLOCK_dma1:
    {
        _RCC->AHB1ENR |= (AHB1ENR_DMA1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_dma2:
    {
        _RCC->AHB1ENR |= (AHB1ENR_DMA2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_crc:
    {
        _RCC->AHB1ENR |= (AHB1ENR_CRCEN);
    }
    break;
    case RCC_PERIPH_CLOCK_usb:
    {
        _RCC->AHB2ENR |= (AHB2ENR_OTGFSEN);
    }
    break;
    case RCC_PERIPH_CLOCK_pwr:
    {
        _RCC->APB1ENR |= (APB1ENR_PWREN);
    }
    break;
    case RCC_PERIPH_CLOCK_i2c3:
    {
        _RCC->APB1ENR |= (APB1ENR_I2C3EN);
    }
    break;
    case RCC_PERIPH_CLOCK_i2c2:
    {
        _RCC->APB1ENR |= (APB1ENR_I2C2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_i2c1:
    {
        _RCC->APB1ENR |= (APB1ENR_I2C1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_usart1:
    {
        _RCC->APB2ENR |= (APB2ENR_USART1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_usart2:
    {
        _RCC->APB1ENR |= (APB1ENR_USART2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_usart6:
    {
        _RCC->APB2ENR |= (APB2ENR_USART6EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi5:
    {
        _RCC->APB2ENR |= (APB2ENR_SPI5EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi4:
    {
        _RCC->APB2ENR |= (APB2ENR_SPI4EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi3:
    {
        _RCC->APB1ENR |= (APB1ENR_SPI3EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi2:
    {
        _RCC->APB1ENR |= (APB1ENR_SPI2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi1:
    {
        _RCC->APB2ENR |= (APB2ENR_SPI1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_wwdg:
    {
        _RCC->APB1ENR |= (APB1ENR_WWDGEN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim5:
    {
        _RCC->APB1ENR |= (APB1ENR_TIM5EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim4:
    {
        _RCC->APB1ENR |= (APB1ENR_TIM4EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim3:
    {
        _RCC->APB1ENR |= (APB1ENR_TIM3EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim2:
    {
        _RCC->APB1ENR |= (APB1ENR_TIM2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim1:
    {
        _RCC->APB2ENR |= (APB2ENR_TIM1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim11:
    {
        _RCC->APB2ENR |= (APB2ENR_TIM11EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim10:
    {
        _RCC->APB2ENR |= (APB2ENR_TIM10EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim9:
    {
        _RCC->APB2ENR |= (APB2ENR_TIM9EN);
    }
    break;
    case RCC_PERIPH_CLOCK_syscfg:
    {
        _RCC->APB2ENR |= (APB2ENR_SYSCFGEN);
    }
    break;
    case RCC_PERIPH_CLOCK_sdio:
    {
        _RCC->APB2ENR |= (APB2ENR_SDIOEN);
    }
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rccDisablePeriphClock(RCC_PERIPH_CLOCK_t clock)
{
    switch (clock)
    {
    case RCC_PERIPH_CLOCK_adc:
    {
        _RCC->APB2ENR &= ~(APB2ENR_ADC1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioa:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOAEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpiob:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOBEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioc:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOCEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpiod:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIODEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioe:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOEEN);
    }
    break;
    case RCC_PERIPH_CLOCK_gpioh:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOHEN);
    }
    break;
    case RCC_PERIPH_CLOCK_dma1:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_DMA1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_dma2:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_DMA2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_crc:
    {
        _RCC->AHB1ENR &= ~(AHB1ENR_CRCEN);
    }
    break;
    case RCC_PERIPH_CLOCK_usb:
    {
        _RCC->AHB2ENR &= ~(AHB2ENR_OTGFSEN);
    }
    break;
    case RCC_PERIPH_CLOCK_pwr:
    {
        _RCC->APB1ENR &= ~(APB1ENR_PWREN);
    }
    break;
    case RCC_PERIPH_CLOCK_i2c3:
    {
        _RCC->APB1ENR &= ~(APB1ENR_I2C3EN);
    }
    break;
    case RCC_PERIPH_CLOCK_i2c2:
    {
        _RCC->APB1ENR &= ~(APB1ENR_I2C2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_i2c1:
    {
        _RCC->APB1ENR &= ~(APB1ENR_I2C1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_usart1:
    {
        _RCC->APB2ENR &= ~(APB2ENR_USART1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_usart2:
    {
        _RCC->APB1ENR &= ~(APB1ENR_USART2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_usart6:
    {
        _RCC->APB2ENR &= ~(APB2ENR_USART6EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi5:
    {
        _RCC->APB2ENR &= ~(APB2ENR_SPI5EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi4:
    {
        _RCC->APB2ENR &= ~(APB2ENR_SPI4EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi3:
    {
        _RCC->APB1ENR &= ~(APB1ENR_SPI3EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi2:
    {
        _RCC->APB1ENR &= ~(APB1ENR_SPI2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_spi1:
    {
        _RCC->APB2ENR &= ~(APB2ENR_SPI1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_wwdg:
    {
        _RCC->APB1ENR &= ~(APB1ENR_WWDGEN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim5:
    {
        _RCC->APB1ENR &= ~(APB1ENR_TIM5EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim4:
    {
        _RCC->APB1ENR &= ~(APB1ENR_TIM4EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim3:
    {
        _RCC->APB1ENR &= ~(APB1ENR_TIM3EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim2:
    {
        _RCC->APB1ENR &= ~(APB1ENR_TIM2EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim1:
    {
        _RCC->APB2ENR &= ~(APB2ENR_TIM1EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim11:
    {
        _RCC->APB2ENR &= ~(APB2ENR_TIM11EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim10:
    {
        _RCC->APB2ENR &= ~(APB2ENR_TIM10EN);
    }
    break;
    case RCC_PERIPH_CLOCK_tim9:
    {
        _RCC->APB2ENR &= ~(APB2ENR_TIM9EN);
    }
    break;
    case RCC_PERIPH_CLOCK_syscfg:
    {
        _RCC->APB2ENR &= ~(APB2ENR_SYSCFGEN);
    }
    break;
    case RCC_PERIPH_CLOCK_sdio:
    {
        _RCC->APB2ENR &= ~(APB2ENR_SDIOEN);
    }
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rccCoreInit(void)
{
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_pwr);
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_syscfg);
}

int rcc_enablePLL(void)
{
    int status = 0;
    uint32_t count = 0;

    if (_RCC->CR & CR_PLLRDY)
    {
        /* PLL ALREADY ENABLED */
    }
    else
    {
        _RCC->CR |= CR_PLLON;

        /* Debug mode sanity check */
        LL_ASSERT(_RCC->CR & CR_PLLON);

        /* Wait for hardware to set the PLL_READY flag */
        do
        {
            if (++count > RCC_CLOCK_COUNT_STABILIZATION_MAX_COUNTS)
            {
                status = 1;
                break;
            }
        } while (!(_RCC->CR & CR_PLLRDY));
    }
    return status;
}

int rcc_enableHSE(void)
{
    int status = 0;
    uint32_t count = 0;

    if (_RCC->CR & CR_HSERDY)
    {
        /* HSE ALREADY READY */
    }
    else
    {
        _RCC->CR |= CR_HSEON;

        /* Debug mode sanity check */
        LL_ASSERT(_RCC->CR & CR_HSEON);

        /* Wait for hardware to set HSE ready flag */
        do
        {
            if (++count > RCC_CLOCK_COUNT_STABILIZATION_MAX_COUNTS)
            {
                status = 1;
                break;
            }
        } while (!(_RCC->CR & CR_HSERDY));
    }
    return status;
}

int rcc_enableHSI(void)
{
    int status = 0;
    uint32_t count = 0;

    if (_RCC->CR & CR_HSIRDY)
    {
        /* HSI already enabled */
    }
    else
    {
        _RCC->CR |= CR_HSION;

        /* Debug mode sanity check */
        LL_ASSERT(_RCC->CR & CR_HSION);

        do
        {
            if (++count > RCC_CLOCK_COUNT_STABILIZATION_MAX_COUNTS)
            {
                status = 1;
                break;
            }
        } while (!(_RCC->CR & CR_HSIRDY));
    }
    return status;
}

int rcc_HSE_isReady(void)
{
    return !!(_RCC->CR & CR_HSERDY);
}

int rcc_HSI_isReady(void)
{
    return !!(_RCC->CR & CR_HSIRDY);
}

int rcc_PLL_isReady(void)
{
    return !!(_RCC->CR & CR_PLLRDY);
}

void rcc_set_PLL_Q_Div(RCC_PLL_Q_DIV_t div)
{
    _RCC->PLLCFGR &= ~(PLLCFGR_PLLQ_MSK);
    switch (div)
    {
    /* DIVISION FACTORS 0 AND 1 ARE INVALID */
    case RCC_PLL_Q_DIV_2:
    case RCC_PLL_Q_DIV_3:
    case RCC_PLL_Q_DIV_4:
    case RCC_PLL_Q_DIV_5:
    case RCC_PLL_Q_DIV_6:
    case RCC_PLL_Q_DIV_7:
    case RCC_PLL_Q_DIV_8:
    case RCC_PLL_Q_DIV_9:
    case RCC_PLL_Q_DIV_10:
    case RCC_PLL_Q_DIV_11:
    case RCC_PLL_Q_DIV_12:
    case RCC_PLL_Q_DIV_13:
    case RCC_PLL_Q_DIV_14:
    case RCC_PLL_Q_DIV_15:
    {
        _RCC->PLLCFGR |= div << PLLCFGR_PLLQ_POS;
    }
    break;
    default:
    {
        /* Min PLLQ valid value is division factor of 2 */
        _RCC->PLLCFGR |= RCC_PLL_Q_DIV_2 << PLLCFGR_PLLQ_POS;
        LL_ASSERT(0); /* Hang in debug mode */
    }
    break;
    }
}

void rcc_set_PLLSRC(RCC_PLLSRC_t in)
{
    _RCC->PLLCFGR &= ~(PLLCFGR_PLLSRC);
    switch (in)
    {
    case RCC_PLLSRC_hse:
    case RCC_PLLSRC_hsi:
    {
        _RCC->PLLCFGR |= in << PLLCFGR_PLLSRC_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    }
}

void rcc_set_PLL_P_Div(RCC_PLL_P_DIV_t div)
{
    _RCC->PLLCFGR &= ~(PLLCFGR_PLLP);
    switch (div)
    {
    case RCC_PLL_P_DIV_2:
    case RCC_PLL_P_DIV_4:
    case RCC_PLL_P_DIV_6:
    case RCC_PLL_P_DIV_8:
    {
        _RCC->PLLCFGR |= div << PLLCFGR_PLLP_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rcc_set_PLL_N_Mul(unsigned int mul)
{
    uint32_t factor = mul;
    if (factor < RCC_MIN_PLL_N_MUL)
    {
        factor = RCC_MIN_PLL_N_MUL;
    }
    else if (factor > RCC_MAX_PLL_N_MUL)
    {
        factor = RCC_MAX_PLL_N_MUL;
    }

    _RCC->PLLCFGR &= ~(PLLCFGR_PLLN);
    _RCC->PLLCFGR |= factor << PLLCFGR_PLLN_POS;
}

void rcc_set_PLL_M_Div(unsigned int mul)
{
    uint32_t factor = mul;
    if (factor < RCC_MIN_PLL_M_DIV)
    {
        factor = RCC_MIN_PLL_M_DIV;
    }
    else if (factor > RCC_MAX_PLL_M_DIV)
    {
        factor = RCC_MAX_PLL_M_DIV;
    }

    _RCC->PLLCFGR &= ~(PLLCFGR_PLLM);
    _RCC->PLLCFGR |= factor << PLLCFGR_PLLM_POS;
}

void rcc_set_APB_clock_Div(RCC_APB_NUM_t num, RCC_APB_CLK_DIV_t div)
{
    switch (num)
    {
    case RCC_APB_NUM_1:
    {
        _RCC->CFGR &= ~(CFGR_PPRE1);
        switch (div)
        {
        case RCC_APB_CLK_DIV_2:
        case RCC_APB_CLK_DIV_4:
        case RCC_APB_CLK_DIV_8:
        case RCC_APB_CLK_DIV_16:
        {
            _RCC->CFGR |= div << CFGR_PPRE1_POS;
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
    case RCC_APB_NUM_2:
    {
        _RCC->CFGR &= ~(CFGR_PPRE2);
        switch (div)
        {
        case RCC_APB_CLK_DIV_1:
        case RCC_APB_CLK_DIV_2:
        case RCC_APB_CLK_DIV_4:
        case RCC_APB_CLK_DIV_8:
        case RCC_APB_CLK_DIV_16:
        {
            _RCC->CFGR |= div << CFGR_PPRE2_POS;
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
    break;
    }
}

void rcc_set_HClk_Div(RCC_HCLK_DIV_t div)
{
    _RCC->CFGR &= ~(CFGR_HPRE);
    switch (div)
    {
    case RCC_HCLK_DIV_1:
    case RCC_HCLK_DIV_2:
    case RCC_HCLK_DIV_4:
    case RCC_HCLK_DIV_8:
    case RCC_HCLK_DIV_16:
    case RCC_HCLK_DIV_64:
    case RCC_HCLK_DIV_128:
    case RCC_HCLK_DIV_256:
    case RCC_HCLK_DIV_512:
    {
        _RCC->CFGR |= div << CFGR_HPRE_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rcc_set_SysClkSrc(RCC_SYSCLK_SOURCE_t src)
{
    switch (src)
    {
    case RCC_SYSCLK_SOURCE_hse:
    case RCC_SYSCLK_SOURCE_hsi:
    case RCC_SYSCLK_SOURCE_pll:
    {
        _RCC->CFGR &= ~(CFGR_SW);
        _RCC->CFGR |= src << CFGR_SW_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

RCC_SYSCLK_SOURCE_t rcc_get_SysClkSrc(void)
{
    return (RCC_SYSCLK_SOURCE_t)((_RCC->CFGR & CFGR_SWS) >> CFGR_SWS_POS);
}

void rcc_setHSEmode(RCC_HSE_MODE_t mode)
{
    _RCC->CR &= ~(CR_HSEBYP);
    switch (mode)
    {
    case RCC_HSE_MODE_bypass:
    case RCC_HSE_MODE_feedback:
    {
        _RCC->CR |= mode << CR_HSEBYP_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_t evt)
{
    switch (evt)
    {
    case RCC_CLK_RDY_lsi:
    case RCC_CLK_RDY_lse:
    case RCC_CLK_RDY_hsi:
    case RCC_CLK_RDY_hse:
    case RCC_CLK_RDY_plli2s:
    case RCC_CLK_RDY_pll:
    {
        _RCC->CIR |= (1 << evt);
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rcc_disable_ClkRdy_IRQ(RCC_CLK_RDY_t evt)
{
    switch (evt)
    {
    case RCC_CLK_RDY_lsi:
    case RCC_CLK_RDY_lse:
    case RCC_CLK_RDY_hsi:
    case RCC_CLK_RDY_hse:
    case RCC_CLK_RDY_plli2s:
    case RCC_CLK_RDY_pll:
    {
        _RCC->CIR &= ~(1 << evt);
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rcc_setMCO2_Src(RCC_MCO2_SRC_t src)
{
    _RCC->CFGR &= ~CFGR_MCO2;
    switch (src)
    {
    case RCC_MCO2_SRC_sysclk:
    case RCC_MCO2_SRC_plli2s:
    case RCC_MCO2_SRC_hse:
    case RCC_MCO2_SRC_pll:
    {
        _RCC->CFGR |= src << CFGR_MCO2_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rcc_setMCO2_Prescaler(RCC_MCO_PRESCALER_t scale)
{
    _RCC->CFGR &= ~CFGR_MCO2PRE;
    switch (scale)
    {
    case RCC_MCO_PRESCALER_1:
    case RCC_MCO_PRESCALER_2:
    case RCC_MCO_PRESCALER_3:
    case RCC_MCO_PRESCALER_4:
    case RCC_MCO_PRESCALER_5:
    {
        _RCC->CFGR |= scale << CFGR_MCO2PRE_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

void rccSystemCoreClockUpdate(void)
{
    uint32_t tmp = 0;
    uint32_t pllvco = 0;
    uint32_t pllp = 2;
    uint32_t pllsource = 0;
    uint32_t pllm = 2;

    /* Check source of sysclk in SWS bits */
    tmp = _RCC->CFGR & CFGR_SWS;
    tmp >>= CFGR_SWS_POS;
    switch ((RCC_SYSCLK_SOURCE_t)tmp)
    {
    case RCC_SYSCLK_SOURCE_hsi: /* HSI used as system clock source */
    {
        SystemCoreClock = HSI_VALUE;
    }
    break;
    case RCC_SYSCLK_SOURCE_hse: /* HSE used as system clock source */
    {
        SystemCoreClock = HSE_VALUE;
    }
    break;
    case RCC_SYSCLK_SOURCE_pll: /* PLL used as system clock source */
    {
        /* Compute PLL output frequency from prescaling bits */
        pllsource = (_RCC->PLLCFGR & PLLCFGR_PLLSRC);
        pllsource >>= PLLCFGR_PLLSRC_POS;
        pllm = _RCC->PLLCFGR & PLLCFGR_PLLM;
        switch ((RCC_PLLSRC_t)pllsource)
        {
        case RCC_PLLSRC_hse:
        {
            uint32_t plln = _RCC->PLLCFGR & PLLCFGR_PLLN;
            plln >>= PLLCFGR_PLLN_POS;

            /** @todo VALIDITY CHECK ON PLLN */

            pllvco = (HSE_VALUE / pllm) * plln;
        }
        break;
        case RCC_PLLSRC_hsi:
        {
            uint32_t plln = _RCC->PLLCFGR & PLLCFGR_PLLN;
            plln >>= PLLCFGR_PLLN_POS;
            pllvco = (HSI_VALUE / pllm) * plln;
        }
        break;
        default:
        {
            /* 
                     * Yeah this should literally never 
                     * happen because a bit can only have 2 states.
                     * If it happens there is an error with the 
                     * bitmasking
                     */
            LL_ASSERT(0);
        }
        break;
        }
        pllp = ((_RCC->PLLCFGR & PLLCFGR_PLLP));
        pllp >>= PLLCFGR_PLLP_POS;

        SystemCoreClock = pllvco / PLLP_DIV_TBL[pllp];
    }
    break;
    default:
    {
        /* Default to HSI RC in case of error */
        SystemCoreClock = HSI_VALUE;
    }
    break;
    }

    /* Compute HCLK */
    RCC_HCLK_DIV_t hpre = (RCC_HCLK_DIV_t)((_RCC->CFGR & CFGR_HPRE) >> CFGR_HPRE_POS);
    uint32_t hclk_prescaler = 1;
    switch ((RCC_HCLK_DIV_t)hpre)
    {
    case RCC_HCLK_DIV_1:
    case RCC_HCLK_DIV_2:
    case RCC_HCLK_DIV_4:
    case RCC_HCLK_DIV_8:
    case RCC_HCLK_DIV_16:
    case RCC_HCLK_DIV_64:
    case RCC_HCLK_DIV_128:
    case RCC_HCLK_DIV_256:
    case RCC_HCLK_DIV_512:
    {
        hclk_prescaler = HCLK_DIV_TBL[hpre];
    }
    break;
    default:
    {
        LL_ASSERT(0);
        /* In production build, just let the value be 1 */
    }
    break;
    }
    SystemCoreClock /= hclk_prescaler;
}

void rccSetRTC_HSE_Div(RCC_HSE_RTC_DIV_t div)
{
    _RCC->CFGR &= ~CFGR_RTCPRE;
    switch (div)
    {
    case RCC_HSE_RTC_DIV_2:
    case RCC_HSE_RTC_DIV_3:
    case RCC_HSE_RTC_DIV_4:
    case RCC_HSE_RTC_DIV_5:
    case RCC_HSE_RTC_DIV_6:
    case RCC_HSE_RTC_DIV_7:
    case RCC_HSE_RTC_DIV_8:
    case RCC_HSE_RTC_DIV_9:
    case RCC_HSE_RTC_DIV_10:
    case RCC_HSE_RTC_DIV_11:
    case RCC_HSE_RTC_DIV_12:
    case RCC_HSE_RTC_DIV_13:
    case RCC_HSE_RTC_DIV_14:
    case RCC_HSE_RTC_DIV_15:
    case RCC_HSE_RTC_DIV_16:
    case RCC_HSE_RTC_DIV_17:
    case RCC_HSE_RTC_DIV_18:
    case RCC_HSE_RTC_DIV_19:
    case RCC_HSE_RTC_DIV_20:
    case RCC_HSE_RTC_DIV_21:
    case RCC_HSE_RTC_DIV_22:
    case RCC_HSE_RTC_DIV_23:
    case RCC_HSE_RTC_DIV_24:
    case RCC_HSE_RTC_DIV_25:
    case RCC_HSE_RTC_DIV_26:
    case RCC_HSE_RTC_DIV_27:
    case RCC_HSE_RTC_DIV_28:
    case RCC_HSE_RTC_DIV_29:
    case RCC_HSE_RTC_DIV_30:
    case RCC_HSE_RTC_DIV_31:
    {
        _RCC->CFGR |= div << CFGR_RTCPRE_POS;
    }
    break;
    default:
    {
        LL_ASSERT(0);
    }
    break;
    }
}

/******************************************************************************/
/******************************************************************************/
/*                       EXCEPTION AND IRQ SERVICE ROUTINES                   */
/******************************************************************************/
/******************************************************************************/

void RCC_IRQHandler(void)
{
    /* Get the interrupt flags */
    uint32_t isr_flags = _RCC->CIR & (CIR_LSIRDYF |
                                      CIR_LSERDYF |
                                      CIR_HSIRDYF |
                                      CIR_HSERDYF |
                                      CIR_PLLRDYF |
                                      CIR_PLLI2SRDYF |
                                      CIR_CSSF);

    /* check if cause of interrupt is a fault exception */
    uint32_t flag_pos = 0;
    do
    {
        if (_RCC->CIR & (1 << flag_pos))
        {
            switch (1 << flag_pos)
            {
            case CIR_LSIRDYF_POS:
            {
                readyflags.LSI = 1;
                _RCC->CIR |= (1 << (16 + flag_pos));
            }
            break;
            case CIR_LSERDYF_POS:
            {
                readyflags.LSE = 1;
                _RCC->CIR |= (1 << (16 + flag_pos));
            }
            break;
            case CIR_HSIRDYF_POS:
            {
                readyflags.HSI = 1;
                _RCC->CIR |= (1 << (16 + flag_pos));
            }
            break;
            case CIR_HSERDYF_POS:
            {
                readyflags.HSE = 1;
                _RCC->CIR |= (1 << (16 + flag_pos));
            }
            break;
            case CIR_PLLRDYF_POS:
            {
                readyflags.PLL = 1;
                _RCC->CIR |= (1 << (16 + flag_pos));
            }
            break;
            case CIR_PLLI2SRDYF_POS:
            {
                readyflags.PLLI2S = 1;
                _RCC->CIR |= (1 << (16 + flag_pos));
            }
            break;
            case CIR_CSSF_POS: /* HW GENERATED A CLOCK SECURITY EXCEPTION */
            {
                /** 
                     * @todo THIS MAY INDICATE A REVERSE ENGINEER ATTEMPT. 
                     * DEVICE STATE SHOULD IMMEDIATELY LOCK AND JUMP TO 
                     * BOOTLOADER TO PREVENT TAMPER 
                     */
                _RCC->CIR |= (1 << (16 + flag_pos));

                LL_ASSERT(0);
            }
            break;
            default:
            {
                /* Do nothing. We just check next flag */
            }
            }
        }

        flag_pos++;
        isr_flags >>= 1;

        /* The flag pos check is just for extra safety. probably redundant */
    } while (isr_flags && (flag_pos < (sizeof(flag_pos) * CHAR_BIT)));

    /* Clear interrupt flag */

    /* Check if cause of interrupt is a flag exception */
    isr_flags = _RCC->CSR & (CSR_LPWRRSTF |
                             CSR_WWDGRSTF |
                             CSR_IWDGRSTF |
                             CSR_SFTRSTF |
                             CSR_PORRSTF |
                             CSR_PINRSTF |
                             CSR_BORRSTF);
    flag_pos = 0;
    do
    {
        switch ((1 << flag_pos))
        {
        case CSR_LPWRRSTF_POS:
        {
            /* Low-power management reset occurred */
        }
        break;
        case CSR_WWDGRSTF_POS:
        {
            /* WWDG Threshhold exception reset occured */
        }
        break;
        case CSR_IWDGRSTF_POS:
        {
            /* IDWG Timeout exception reset occured */
        }
        break;
        case CSR_SFTRSTF_POS:
        {
            /* cortex Soft reset occured */
        }
        break;
        case CSR_PORRSTF_POS:
        {
            /* PwrOn/PwrDown Reset occured */
        }
        break;
        case CSR_PINRSTF_POS:
        {
            /* NRST pin reset occurred */
        }
        break;
        case CSR_BORRSTF_POS:
        {
            /* Brownout reset occureed */
        }
        break;
        default:
        {
            /* Do nothing, go to next flag */
        }
        break;
        }
    } while (isr_flags && (flag_pos < (sizeof(flag_pos) * CHAR_BIT)));

    /* Clear flag exception bits in RCC:CSR */
    _RCC->CSR |= CSR_RMVF;
}

uint32_t rccGetSystemCoreClock(void)
{
    return SystemCoreClock;
}

uint32_t rccGetHClkFreq(void)
{
    RCC_HCLK_DIV_t hclk = (RCC_HCLK_DIV_t)((_RCC->CFGR & CFGR_HPRE) >> CFGR_HPRE_POS);
    return rccGetSystemCoreClock() * HCLK_DIV_TBL[hclk];
}
