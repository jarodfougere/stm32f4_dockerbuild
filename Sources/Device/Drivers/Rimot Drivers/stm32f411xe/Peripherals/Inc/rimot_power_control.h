#ifndef RIMOT_MCU_POWER_CONTROL
#define RIMOT_MCU_POWER_CONTROL
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define PWR_BASE (APB1PERIPH_BASE + 0x7000UL)


/* PAGE 86, REFERENCE MANUAL */
struct pwr_ctl_regs
{
  hw_reg CR;   /* power control register        |  offset: 0x00 */
  hw_reg CSR;  /* power control/status register |  offset: 0x04 */
};

#define _PWR ((struct pwr_ctl_regs*) PWR_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_POWER_CONTROL */