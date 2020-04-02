#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

/*  
 * PUTTING THESE HERE SO I CAN CHECK AGAINST MY COMPUTED ADDRESSES.
 * WHILE DEBUGGING.
 * 
 * GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
 * GPIOB_BASE (AHB1PERIPH_BASE + 0x0400UL)
 * GPIOC_BASE (AHB1PERIPH_BASE + 0x0800UL)
 * GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00UL)
 * GPIOE_BASE (AHB1PERIPH_BASE + 0x1000UL)
 * 
 * NOTICE THAT THERE IS A 0x08 BYTE GAP 
 * BETWEEN GPIOE AND GPIOH
 * (since sizeof(gpio_Struct ) == 0x0400).
 * PRESUMABLY, THIS IS WHERE GPIOF AND GPIOG
 * MIGHT GO ON A LARGER DIE.
 * 
 * GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00UL)
 *
 */


/* 
 * I want to just have an enum for port A -> H and an array of gpio_ports,
 *  but the offset for port h means I can't validate that the indices for 
 *  "GPIOF" or "GPIOG" wound't be access and that constitues UB... :(
 *
 * IF I CAN STATICALLY ASSERT THAT THE MEMORY BETWEEN GPIOE AND GPIOH 
 * WILL NOT BE ACCESSED, THEN THERE IS A VERY ELEGANT SOLUTION BECAUSE
 * THE SIZEOF gpio_port instances are constant and word-aligned :)
 * 
 * TODO:
 * Find a way to statically assert that no memory can be accessed between
 * 0x1400 and 0x1C00
 * 
 * EXAMPLE OF THE PORT REFERENCING
 * enum GPIOx
 * {
 *     GPIOA = 0,
 *     GPIOB = 1,
 *     GPIOC = 2,
 *     GPIOD = 3,
 *     GPIOE = 4,
 *     GPIOF = 5, <--- MUST BE ABLE TO GUARANTEE THAT ACCESS OF THIS
 *                     GPIO PORT ARRAY IDX GENERATES AN ERROR AT COMPILE TIME
 *     GPIOG = 6, <--- SAME APPLIES TO THIS INDEX AS WELL.
 *     GPIOH = 7
 * };
 * 
 * EXAMPLE OF THE CONTIGUOUS ARRAY OVERLAY:
 * struct gpio_regs
 * {
 *     struct
 *     {
 *         hw_reg MODER;    
 *         hw_reg OTYPER;   
 *         hw_reg OSPEEDR;  
 *         hw_reg PUPDR;    
 *         hw_reg IDR;      
 *         hw_reg ODR;      
 *         hw_reg BSRR;     
 *         hw_reg LCKR;     
 *         hw_reg AFR[2];   
 *     }   PORTS[NUM_GPIO_PORTS]; <--- NUM == 8
 * };
 * 
 */


/* PAGE 157 REFERENCE MANUAL */
struct gpio_port
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

#define _GPIOA ((struct gpio_port*) GPIOA_BASE)
#define _GPIOB ((struct gpio_port*) GPIOB_BASE)
#define _GPIOC ((struct gpio_port*) GPIOC_BASE)
#define _GPIOD ((struct gpio_port*) GPIOD_BASE)
#define _GPIOE ((struct gpio_port*) GPIOE_BASE)
#define _GPIOH ((struct gpio_port*) GPIOH_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_GPIO */