#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00UL)


struct gpio_regs
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


#define GPIOA ((struct gpio_regs*) GPIOA_BASE)
#define GPIOB ((struct gpio_regs*) GPIOB_BASE)
#define GPIOC ((struct gpio_regs*) GPIOC_BASE)
#define GPIOD ((struct gpio_regs*) GPIOD_BASE)
#define GPIOE ((struct gpio_regs*) GPIOE_BASE)
#define GPIOH ((struct gpio_regs*) GPIOH_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_GPIO */