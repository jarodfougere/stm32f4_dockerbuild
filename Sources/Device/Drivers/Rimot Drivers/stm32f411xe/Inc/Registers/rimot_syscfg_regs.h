#ifndef RIMOT_MCU_SYSTEM_REGS
#define RIMOT_MCU_SYSTEM_REGS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define SYSCFG_BASE (APB2PERIPH_BASE + 0x3800UL)

/* PAGE 139 REFERENCE MANUAL */
struct syscfg_regs
{
    hw_reg MEMRMP;      /*  memory remap register               */
    hw_reg PMC;         /* peripheral mode config register      */
    hw_reg EXTICR[4];   /* ext interrupt config registers       */
    pad32  RESERVED[2]; /* Reserved                             */
    hw_reg CMPCR;       /* Compensation cell control register   */
};

#define _SYSCFG ((struct syscfg_regs*) SYSCFG_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_SYSTEM_REGS */