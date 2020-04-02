#ifndef RIMOT_MCU_SDIO
#define RIMOT_MCU_SDIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define SDIO_BASE (APB2PERIPH_BASE + 0x2C00UL)

/* PAGE 652, REFERENCE MANUAL */
struct sdio_regs
{
    hw_reg PWR;           /* Power control register */
    hw_reg CLKCR;         /* Clock control register */
    hw_reg ARG;           /* Argument register */
    hw_reg CMD;           /* Command register */
    hw_reg RESPCMD;       /* Command responsse register */
    hw_reg RESP[4];       /* SDIO response register */
    hw_reg DTIMER;        /* Data timeout period register */
    hw_reg DLEN;          /* Data length register */
    hw_reg DCTL;          /* Data control register */
    hw_reg DCNT;          /* Data count register */
    hw_reg STA;           /* Status register */ 
    hw_reg ICR;           /* Int clear reg. Write only. Write bit to "re-arm" */
    hw_reg MSK;           /* Interrupt status bit mask register */
    pad32  RESERVED1[2];  /* Reserved */
    hw_reg FIFOCNT;       /* Fifo counter register */
    hw_reg RESERVED2[13]; /* Reserved */
    hw_reg FIFO;          /* Data FIFO register */
};

#define _SDIO ((struct sdio_regs*) SDIO_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_SDIO */