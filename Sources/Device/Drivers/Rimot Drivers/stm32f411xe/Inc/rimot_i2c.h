#ifndef RIMOT_MCU_IIC
#define RIMOT_MCU_IIC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

struct i2c_regs
{
  hw_reg CR1;        /* Control register 1       */
  hw_reg CR2;        /* Control register 2       */
  hw_reg OAR1;       /* Own address register 1   */
  hw_reg OAR2;       /* Own address register 2   */
  hw_reg DR;         /* Data register            */
  hw_reg SR1;        /* Status register 1        */
  hw_reg SR2;        /* Status register 2        */
  hw_reg CCR;        /* Clock control register   */
  hw_reg TRISE;      /* TRISE register           */
  hw_reg FLTR;       /* FLTR register            */
};


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_IIC */