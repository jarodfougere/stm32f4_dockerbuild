#ifndef RIMOT_FLASH_CONTROLLER
#define RIMOT_FLASH_CONTROLLER
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"
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

#define FLASH_CTL ((struct flash_regs*) FLASH_R_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_FLASH_CONTROLLER */