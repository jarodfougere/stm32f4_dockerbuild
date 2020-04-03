#ifndef RIMOT_MCU_
#define RIMOT_MCU_
#ifdef __cplusplus
extern "C" {
#endif /* C linkage  */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)

/* PAGE 102, REFERENCE MANUAL */
struct rcc_regs
{
    hw_reg CR;         /* Clock control register                   */
    hw_reg PLLCFGR;    /* PLL configuration register               */
    hw_reg CFGR;       /* Clock configuration register             */
    hw_reg CIR;        /* Clock interrupt register                 */
    hw_reg AHB1RSTR;   /* AHB1 peripheral reset register           */
    hw_reg AHB2RSTR;   /* AHB2 peripheral reset register           */
    hw_reg AHB3RSTR;   /* AHB3 peripheral reset register           */
    pad32 RESERVED0;   /* Reserved                                 */
    hw_reg APB1RSTR;   /* APB1 peripheral reset register           */
    hw_reg APB2RSTR;   /* APB2 peripheral reset register           */
    pad32 RESERVED1;   /* Reserved                                 */
    pad32 RESERVED2;   /* Reserved                                 */
    hw_reg AHB1ENR;    /* AHB1 peripheral clock register           */
    hw_reg AHB2ENR;    /* AHB2 peripheral clock register           */
    hw_reg AHB3ENR;    /* AHB3 peripheral clock register           */
    pad32 RESERVED3;   /* Reserved                                 */
    hw_reg APB1ENR;    /* APB1 peripheral clock enable register    */
    hw_reg APB2ENR;    /* APB2 peripheral clock enable register    */
    pad32 RESERVED4;   /* Reserved                                 */
    pad32 RESERVED5;   /* Reserved                                 */
    hw_reg AHB1LPENR;  /* AHB1 periph clock enable in LPM register */
    hw_reg AHB2LPENR;  /* AHB2 periph clock enable in LPM register */
    hw_reg AHB3LPENR;  /* AHB3 periph clock enable in LPM register */
    pad32 RESERVED6;   /* Reserved                                 */
    hw_reg APB1LPENR;  /* APB1 periph clk enable in LPM register   */
    hw_reg APB2LPENR;  /* APB2 periph clk enable in LPM register   */
    pad32 RESERVED7;   /* Reserved                                 */
    pad32 RESERVED8;   /* Reserved                                 */
    hw_reg BDCR;       /* Backup domain control register           */
    hw_reg CSR;        /* Clock control & status register          */
    pad32 RESERVED9;   /* Reserved                                 */ 
    pad32 RESERVED10;  /* Reserved                                 */
    hw_reg SSCGR;      /* Spread spectrum clock gen register       */
    hw_reg PLLI2SCFGR; /* PLLI2S configuration register            */
    pad32 RESERVED11;  /* Reserved                                 */
    hw_reg DCKCFGR;    /* Dedicated Clocks configuration register  */
}; 

#define _RCC ((struct rcc_regs*) RCC_BASE)


#ifdef __cplusplus
}
#endif /* C linkage  */
#endif /* RIMOT_MCU_  */