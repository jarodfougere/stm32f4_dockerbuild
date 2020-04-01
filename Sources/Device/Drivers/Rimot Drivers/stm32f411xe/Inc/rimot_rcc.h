#ifndef RIMOT_MCU_
#define RIMOT_MCU_
#ifdef __cplusplus
extern "C" {
#endif /* C linkage  */

#include "rimot_peripheral_regs.h"

/* RESET AND CLOCK CONTROLLER STRUCTURE */
struct rcc_regs
{
  hw_reg CR;         /* Clock control register                   */
  hw_reg PLLCFGR;    /* PLL configuration register               */
  hw_reg CFGR;       /* Clock configuration register             */
  hw_reg CIR;        /* Clock interrupt register                 */
  hw_reg AHB1RSTR;   /* AHB1 peripheral reset register           */
  hw_reg AHB2RSTR;   /* AHB2 peripheral reset register           */
  hw_reg AHB3RSTR;   /* AHB3 peripheral reset register           */
           mcu_word RESERVED0;  /* Reserved                                 */
  hw_reg APB1RSTR;   /* APB1 peripheral reset register           */
  hw_reg APB2RSTR;   /* APB2 peripheral reset register           */
           mcu_word RESERVED1;  /* Reserved                                 */
           mcu_word RESERVED2;  /* Reserved                                 */
  hw_reg AHB1ENR;    /* AHB1 peripheral clock register           */
  hw_reg AHB2ENR;    /* AHB2 peripheral clock register           */
  hw_reg AHB3ENR;    /* AHB3 peripheral clock register           */
           mcu_word RESERVED3;  /* Reserved                                 */
  hw_reg APB1ENR;    /* APB1 peripheral clock enable register    */
  hw_reg APB2ENR;    /* APB2 peripheral clock enable register    */
           mcu_word RESERVED4;  /* Reserved                                 */
           mcu_word RESERVED5;  /* Reserved                                 */
  hw_reg AHB1LPENR;  /* AHB1 periph clock enable in LPM register */
  hw_reg AHB2LPENR;  /* AHB2 periph clock enable in LPM register */
  hw_reg AHB3LPENR;  /* AHB3 periph clock enable in LPM register */
           mcu_word RESERVED6;  /* Reserved                                 */
  hw_reg APB1LPENR;  /* APB1 periph clk enable in LPM register   */
  hw_reg APB2LPENR;  /* APB2 periph clk enable in LPM register   */
           mcu_word RESERVED7;  /* Reserved                                 */
           mcu_word RESERVED8;  /* Reserved                                 */
  hw_reg BDCR;       /* Backup domain control register           */
  hw_reg CSR;        /* Clock control & status register          */
           mcu_word RESERVED9;  /* Reserved                                 */ 
           mcu_word RESERVED10; /* Reserved                                 */
  hw_reg SSCGR;      /* Spread spectrum clock gen register       */
  hw_reg PLLI2SCFGR; /* PLLI2S configuration register            */
           mcu_word RESERVED11; /* Reserved                                 */
  hw_reg DCKCFGR;    /* Dedicated Clocks configuration register  */
}; 


#ifdef __cplusplus
}
#endif /* C linkage  */
#endif /* RIMOT_MCU_  */