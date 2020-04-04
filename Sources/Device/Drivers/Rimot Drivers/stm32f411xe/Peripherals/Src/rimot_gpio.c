/**
 * @file rimot_gpio.c
 * @author Carl Mattatall
 * @brief This source module provides a low level driver for the
 * GPIO peripheral on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_gpio.h"
#include "rimot_gpio_register_masks.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"



#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00UL)


/* PAGE 157 */
#define GPIOA_MODER_RESET_VAL 0xA8000000
#define GPIOB_MODER_RESET_VAL 0x00000280
#define GPIOC_MODER_RESET_VAL 0x00000000
#define GPIOD_MODER_RESET_VAL 0x00000000
#define GPIOE_MODER_RESET_VAL 0x00000000
#define GPIOH_MODER_RESET_VAL 0x00000000

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


/* DATASHEET (NOT REFERENCE MANUAL) PAGE 39 */

/* This maps a pin on the mcu package to its gpio port */
static const struct pin_map pin_map[PACKAGE_PIN_COUNT] =
#if defined(STM32F411RE)    /* Production mcu. LQFP64 */
#error PLEASE DEFINE THE MCU_PIN_#->PORT MAP IN rimot_gpio.c FOR STM32F411RE
{

};
#elif defined(STM32F411VE) /* Eval board MCU, LQFP100 */
{
    [PA0] = {.port = _GPIOA, .bit = 0}, /* PA0 */
    [PA1] = {.port = _GPIOA, .bit = 1}, /* PA1 */
};
#warning THE pin# -> gpio port for STM32F411VE is not complete
#else
#error NEITHER STM32F411RE NOR STM32F411VE IS DEFINED. PLEASE SEE rimot_gpio.c
#endif


struct pin_map* gpio(mcu_word pin)
{
    return (struct pin_map*)&pin_map[pin];
}




void set_pin_mode(GPIO_MODE_t mode, mcu_word pin)
{
    switch(mode)
    {   
        /* VALID MODES */
        case GPIO_MODE_alternate:
        case GPIO_MODE_analog:
        case GPIO_MODE_input:
        case GPIO_MODE_output:
            /* See reference manual page 157 */

            /* Reset the curerent MODER bits for the pin */
            pin_map[pin].port->MODER &= ~(3 << (pin_map[pin].bit * 2)); 

            /* Set the new MODER bits for the pin */
            pin_map[pin].port->MODER |= (((mcu_word)mode) << 
                                        (pin_map[pin].bit * 2));
            break;
        default:
            /* Reset the bits to the default (digital input) */
            pin_map[pin].port->MODER &= ~(3 << (pin_map[pin].bit * 2)); 
#if !defined(NDEBUG)
            while(1); /* Hang forever */
#else
            break;
#endif  /* DEBUG BUILD */
    }
}
