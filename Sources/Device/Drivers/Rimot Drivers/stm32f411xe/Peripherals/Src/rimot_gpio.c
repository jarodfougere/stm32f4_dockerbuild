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

#include "rimot_rcc.h"
#include "rimot_rcc_register_masks.h"
#include "rimot_gpio.h"
#include "rimot_gpio_register_masks.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_register_bit_ops.h"
#include "rimot_LL_debug.h"




#define GPIO_PORT_BASE (AHB1PERIPH_BASE + 0x00000000U)
#define _GPIO ((struct gpio*)GPIO_PORT_BASE)

#if 0 /* UNUSED. KEPT FOR LEGACY AND ADDRESS VERIFICATION PURPOSES */
#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00UL)

#define _GPIOA ((struct gpio_port*) GPIOA_BASE)
#define _GPIOB ((struct gpio_port*) GPIOB_BASE)
#define _GPIOC ((struct gpio_port*) GPIOC_BASE)
#define _GPIOD ((struct gpio_port*) GPIOD_BASE)
#define _GPIOE ((struct gpio_port*) GPIOE_BASE)
#define _GPIOH ((struct gpio_port*) GPIOH_BASE)
#endif 


/* RESET VALUES FOR MODER REGISTER */
#define GPIOA_MODER_RESET_VAL 0xA8000000
#define GPIOB_MODER_RESET_VAL 0x00000280
#define GPIOC_MODER_RESET_VAL 0x00000000
#define GPIOD_MODER_RESET_VAL 0x00000000
#define GPIOE_MODER_RESET_VAL 0x00000000
#define GPIOH_MODER_RESET_VAL 0x00000000

struct gpio_port
{
    hw_reg MODER;    /* GPIO port mode register                0x0000    */
    hw_reg OTYPER;   /* GPIO port output type register         0X0004    */
    hw_reg OSPEEDR;  /* GPIO port output speed register        0X0008    */
    hw_reg PUPDR;    /* GPIO port pull-up/pull-down register   0X000C    */
    hw_reg IDR;      /* GPIO port input data register          0X0010    */
    hw_reg ODR;      /* GPIO port output data register         0X0014    */
    hw_reg BSRR;     /* GPIO port bit set/reset register       0X0018    */
    hw_reg LCKR;     /* GPIO port configuration lock register  0X001C    */
    hw_reg AFRL;     /* GPIO alternate function low register   0X0020    */
    hw_reg AFRH;     /* GPIO alternate function high register  0X0024    */
    PAD_BETWEEN(GPIO, 0x0024, 0x0400); /* PAD TO NEXT STRUCT             */
};

struct gpio
{   
    /* Reference this using enum GPIO_PORT_IDX_t */
    struct gpio_port port[8];
};

void gpio_enablePinClock(MCUPIN_t pin)
{
    switch(pin_aliasLookup(pin).port_idx)
    {
    case GPIO_PORT_IDX_A:
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOAEN);
        break;
    case GPIO_PORT_IDX_B:
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOBEN);
        break;
    case GPIO_PORT_IDX_C:
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOCEN);
        break;
    case GPIO_PORT_IDX_D:
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIODEN);
        break;
    case GPIO_PORT_IDX_E:
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIODEN);
        break;
    case GPIO_PORT_IDX_H:
        _RCC->AHB1ENR &= ~(AHB1ENR_GPIOHEN);
        break;
    default:
#if !defined(NDEBUG)
        while(1); /* Hang for programmer to catch */
#else
        break;
#endif /* DEBUG BUILD */
    }
}


void gpio_setPinMode(GPIO_MODE_t mode, mcu_word pin)
{   
    struct pin_map map = pin_aliasLookup(pin);
    /* Reset the curerent MODER bits for the pin */
    _GPIO->port[map.port_idx].MODER &= ~MODER(map.bit);
    switch(mode)
    {   
        /* VALID MODES */
        case GPIO_MODE_alternate:
        case GPIO_MODE_analog:
        case GPIO_MODE_input:
        case GPIO_MODE_output:
            /* Set the new MODER bits */
            _GPIO->port[map.port_idx].MODER |= MODER(map.bit) & mode;
            break;
        default:
#if !defined(NDEBUG)
            while(1); /* Hang forever */
#else
            break;
#endif  /* DEBUG BUILD */
    }
}
