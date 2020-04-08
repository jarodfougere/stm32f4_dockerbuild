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


#if 0 
/* INCLUDED FOR REFERENCE */

#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do {                                                     \
                                                            __IO uint32_t tmpreg = 0x00U;                        \
                                                            MODIFY_REG(PWR->CR, PWR_CR_VOS, (__REGULATOR__));   \
                                                            /* Delay after an RCC peripheral clock enabling */  \
                                                            tmpreg = READ_BIT(PWR->CR, PWR_CR_VOS);             \
                                                            UNUSED(tmpreg);                                     \
                                                          } while(0U)


#endif 


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_POWER_CONTROL */