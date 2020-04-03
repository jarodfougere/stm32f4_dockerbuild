#ifndef RIMOT_MCU_IIC
#define RIMOT_MCU_IIC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define I2C1_BASE (APB1PERIPH_BASE + 0x5400UL)
#define I2C2_BASE (APB1PERIPH_BASE + 0x5800UL)
#define I2C3_BASE (APB1PERIPH_BASE + 0x5C00UL)

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

#define _I2C1 ((struct i2c_regs*) I2C1_BASE)
#define _I2C2 ((struct i2c_regs*) I2C2_BASE)
#define _I2C3 ((struct i2c_regs*) I2C3_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_IIC */