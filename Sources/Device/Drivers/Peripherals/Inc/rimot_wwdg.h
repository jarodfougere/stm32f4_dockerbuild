#ifndef RIMOT_WINDOW_WATCHDOG
#define RIMOT_WINDOW_WATCHDOG
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */

#include "rimot_register_padding.h"
#include "rimot_bus_region_offsets.h"

#define WWDG_BASE (APB1PERIPH_BASE + 0x2C00UL)

    /* PAGE 430, REFERENCE MANUAL */
    struct wwdg_regs
    {
        volatile uint32_t CR;  /* Control register       */
        volatile uint32_t CFR; /* Configuration register */
        volatile uint32_t SR;  /* Status register        */
    };

#define _WWDG ((struct wwdg_regs *)WWDG_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_WINDOW_WATCHDOG */
