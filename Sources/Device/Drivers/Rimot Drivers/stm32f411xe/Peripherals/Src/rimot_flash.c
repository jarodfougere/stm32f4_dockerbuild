/**
 * @file rimot_flash.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level "driver" for the 
 * FLASH access control peripheral on the STM32f411RE microcontrlller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_flash_ctl.h"
#include "rimot_flash_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"


#define FLASH_R_BASE (AHB1PERIPH_BASE + 0x3C00UL)

/* PAGE 59, REFERENCE MANUAL */
struct flash_regs
{   
    hw_reg ACR;      /* FLASH access control register        */
    hw_reg KEYR;     /* FLASH key register                   */
    hw_reg OPTKEYR;  /* FLASH option key register            */
    hw_reg SR;       /* FLASH status register                */
    hw_reg CR;       /* FLASH control register               */
    hw_reg OPTCR;    /* FLASH option control register        */
    hw_reg OPTCR1;   /* FLASH option control register 1      */
};

#define _FLASH ((struct flash_regs*) FLASH_R_BASE)


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


void FLASH_IRQHandler(void)
{

}