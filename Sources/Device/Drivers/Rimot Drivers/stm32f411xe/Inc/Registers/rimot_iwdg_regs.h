#ifndef RIMOT_MCU_WATCHDOG
#define RIMOT_MCU_WATCHDOG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

#define IWDG_BASE (APB1PERIPH_BASE + 0x3000UL)


/* independent watchdog (prevent MCU freeze-hang ) */
struct iwdg_regs       
{
  hw_reg KR;   /* Key register           */
  hw_reg PR;   /* Prescaler register     */
  hw_reg RLR;  /* Reload register        */
  hw_reg SR;   /* Status register        */
};

#define IWDG ((struct iwdg_regs*) IWDG_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_WATCHDOG */