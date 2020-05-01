/**
 * @file rimot_flash.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level "driver" for the 
 * FLASH access control peripheral on the STM32f411RE microcontrlller
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

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_flash_ctl.h"
#include "rimot_flash_register_masks.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"


#define FLASH_R_BASE (AHB1PERIPH_BASE + 0x3C00UL)

/* PAGE 59, REFERENCE MANUAL */
struct flash_regs
{   
    volatile uint32_t ACR;      /* FLASH access control register        */
    volatile uint32_t KEYR;     /* FLASH key register                   */
    volatile uint32_t OPTKEYR;  /* FLASH option key register            */
    volatile uint32_t SR;       /* FLASH status register                */
    volatile uint32_t CR;       /* FLASH control register               */
    volatile uint32_t OPTCR;    /* FLASH option control register        */
    volatile uint32_t OPTCR1;   /* FLASH option control register 1      */
};

#define _FLASH ((struct flash_regs*) FLASH_R_BASE)

/**
 * @todo I WAS ORIGINALLY PLANNING TO SET THE FLASH WAIT TIME BASED ON 
 * THE PARAMETERS IN RCC REGISTERS AND THE DEFINED HSE_VALUE / HSI_VALUE
 * I HAVE NOT YET IMPLEMENTED THAT
 */
#if 0

/* HCLK frequency to set FLASH latency 1 in power scale 1  */
#define FLASH_SCALE1_LATENCY1_FREQ   30000000U      

/* HCLK frequency to set FLASH latency 2 in power scale 1  */
#define FLASH_SCALE1_LATENCY2_FREQ   64000000U      

/* HCLK frequency to set FLASH latency 3 in power scale 1  */
#define FLASH_SCALE1_LATENCY3_FREQ   90000000U      

/* HCLK frequency to set FLASH latency 1 in power scale 2  */
#define FLASH_SCALE2_LATENCY1_FREQ   30000000U     

/* HCLK frequency to set FLASH latency 2 in power scale 2  */
#define FLASH_SCALE2_LATENCY2_FREQ   64000000U      


/* HCLK frequency to set FLASH latency 1 in power scale 3  */
#define FLASH_SCALE3_LATENCY1_FREQ   30000000U   

/* HCLK frequency to set FLASH latency 2 in power scale 3  */
#define FLASH_SCALE3_LATENCY2_FREQ   64000000U    

#endif 


void flashSetPrefetchBuffer(FLASH_PREFETCH_BUFFER_MODE_t mode)
{
    switch(mode)
    {
        case FLASH_PREFETCH_BUFFER_MODE_disabled:
        {
            _FLASH->ACR &= ~ACR_PRFTEN;
        }
        break;
        case FLASH_PREFETCH_BUFFER_MODE_enabled:
        {
            _FLASH->ACR |= ACR_PRFTEN;
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}



void flashSetPrefetchDataCacheMode(FLASH_PREFETCH_DATA_CACHE_MODE_t mode)
{
    switch(mode)
    {
        case FLASH_PREFETCH_DATA_CACHE_MODE_disabled:
        {
            _FLASH->ACR &= ~ACR_DCEN;
        }
        break;
        case FLASH_PREFETCH_DATA_CACHE_MODE_enabled:
        {
            _FLASH->ACR |= ACR_DCEN;
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}


void flashSetInstructionCacheMode(FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_t mode)
{
    switch(mode)
    {
        case FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_disabled:
        {
            _FLASH->ACR &= ~ACR_ICEN;
        }
        break;
        case FLASH_PREFETCH_INSTRUCTION_CACHE_MODE_enabled:
        {
            _FLASH->ACR |= ACR_ICEN;
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}

void flashSetWaitCycles(FLASH_WAIT_CYCLES_t cycles)
{   
    _FLASH->ACR &= ~ACR_LATENCY;
    uint32_t latency = 0;
    switch(cycles)
    {
        case FLASH_WAIT_CYCLES_0:
        case FLASH_WAIT_CYCLES_1:
        case FLASH_WAIT_CYCLES_2:
        case FLASH_WAIT_CYCLES_3:
        case FLASH_WAIT_CYCLES_4:
        case FLASH_WAIT_CYCLES_5:
        case FLASH_WAIT_CYCLES_6:
        case FLASH_WAIT_CYCLES_7:
        case FLASH_WAIT_CYCLES_8:
        case FLASH_WAIT_CYCLES_9:
        case FLASH_WAIT_CYCLES_10:
        case FLASH_WAIT_CYCLES_11:
        case FLASH_WAIT_CYCLES_12:
        case FLASH_WAIT_CYCLES_13:
        case FLASH_WAIT_CYCLES_14:
        case FLASH_WAIT_CYCLES_15:
        {
            latency = cycles << ACR_LATENCY_POS;
        }
        break;
        default:
        {   
            /* PUT MAX AMOUNT OF LATENCY IN DEFAULT CASE */
            latency = ACR_LATENCY;

            LL_ASSERT(0);
        }
        break;
    }
    
    _FLASH->ACR |= latency;

    LL_ASSERT(((_FLASH->ACR & ACR_LATENCY) >> ACR_LATENCY_POS) == latency);
    
}


void flashUnlockACR(void)
{
    _FLASH->KEYR = 0x45670123;

    volatile uint32_t forcedWait;
    for(forcedWait = 0; forcedWait < 100; forcedWait++);

    _FLASH->KEYR = 0xCDEF89AB; 
}



int flash_isBusy(void)
{
    return !!(_FLASH->SR & SR_BSY);
}

#if !defined(USE_HAL_DRIVER)
void FLASH_IRQHandler(void)
{   
    uint32_t flag_pos = 0;
    uint32_t flags = _FLASH->SR;
    do
    {
        switch(1 << flag_pos)
        {
            case SR_RDERR:
            {

            }
            break;
            case SR_PGSERR:
            {

            }
            break;
            case SR_PGPERR:
            {

            }
            break;
            case SR_PGAERR:
            {

            }
            break;
            case SR_WRPERR:
            {

            }
            break;
            case SR_OPERR:
            {

            }
            break;
            default:
            {
                /* dO ONTHING */
            }
            break;
        }
        flag_pos++;
    }   while((flags >>= 1));
}
#endif
