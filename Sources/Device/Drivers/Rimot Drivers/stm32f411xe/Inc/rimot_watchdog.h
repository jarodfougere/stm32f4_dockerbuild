#ifndef RIMOT_MCU_WATCHDOG
#define RIMOT_MCU_WATCHDOG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

/* independent watchdog (prevent MCU freeze-hang ) */
struct iwdg_regs       
{
  hw_reg KR;   /* Key register           */
  hw_reg PR;   /* Prescaler register     */
  hw_reg RLR;  /* Reload register        */
  hw_reg SR;   /* Status register        */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_WATCHDOG */