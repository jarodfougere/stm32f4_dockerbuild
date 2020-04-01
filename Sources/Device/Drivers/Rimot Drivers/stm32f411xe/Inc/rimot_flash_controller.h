#ifndef RIMOT_FLASH_CONTROLLER
#define RIMOT_FLASH_CONTROLLER
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

struct flash_controller
{   
    hw_reg ACR;      /* FLASH access control register        */
    hw_reg KEYR;     /* FLASH key register                   */
    hw_reg OPTKEYR;  /* FLASH option key register            */
    hw_reg SR;       /* FLASH status register                */
    hw_reg CR;       /* FLASH control register               */
    hw_reg OPTCR;    /* FLASH option control register        */
    hw_reg OPTCR1;   /* FLASH option control register 1      */
};


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_FLASH_CONTROLLER */