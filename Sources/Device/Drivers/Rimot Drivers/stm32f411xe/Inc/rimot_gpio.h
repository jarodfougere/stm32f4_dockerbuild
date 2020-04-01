#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

struct gpio_periph
{
  hw_reg MODER;    /* GPIO port mode register                    */
  hw_reg OTYPER;   /* GPIO port output type register             */
  hw_reg OSPEEDR;  /* GPIO port output speed register            */
  hw_reg PUPDR;    /* GPIO port pull-up/pull-down register       */
  hw_reg IDR;      /* GPIO port input data register              */
  hw_reg ODR;      /* GPIO port output data register             */
  hw_reg BSRR;     /* GPIO port bit set/reset register           */
  hw_reg LCKR;     /* GPIO port configuration lock register      */
  hw_reg AFR[2];   /* GPIO alternate function registers          */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_GPIO */