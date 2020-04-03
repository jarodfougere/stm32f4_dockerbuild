#ifndef RIMOT_WINDOW_WATCHDOG
#define RIMOT_WINDOW_WATCHDOG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define WWDG_BASE (APB1PERIPH_BASE + 0x2C00UL)

/* PAGE 430, REFERENCE MANUAL */
struct wwdg_regs
{
    hw_reg CR;  /* Control register       */
    hw_reg CFR; /* Configuration register */
    hw_reg SR;  /* Status register        */
};

#define _WWDG ((struct wwdg_regs*) WWDG_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_WINDOW_WATCHDOG */