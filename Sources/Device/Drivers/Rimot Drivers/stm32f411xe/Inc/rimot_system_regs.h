#ifndef RIMOT_MCU_SYSTEM_REGS
#define RIMOT_MCU_SYSTEM_REGS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

struct system_regs
{
    hw_reg MEMRMP;       /*  memory remap register               */
    hw_reg PMC;          /* peripheral mode config register      */
    hw_reg EXTICR[4];    /* ext interrupt config registers       */

    /**************************************************************************/
    /****/   mcu_word RESERVED[2]; /* overlay register alignment  ****/
    /**************************************************************************/

    hw_reg CMPCR;       /* Compensation cell control register    */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_SYSTEM_REGS */