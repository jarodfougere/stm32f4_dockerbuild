#ifndef RIMOT_MCUPIN
#define RIMOT_MCUPIN
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/* Check if we're building for a hosted environment or not */
#if defined(MCU_APP)

#include <stdint.h>

/* Header selection based on driver */
#if defined(USE_HAL_DRIVER)
#include "stm32f411xe.h" /* provide declaration of GPIO_Typedef */
#else
#include "rimot_gpio.h" /* provide declaration of struct gpio_regs */
#endif 

/* The possible states for a GPIO pin on the MCU */
enum pinstate 
{   
    /* I need to think of a better name than "pinstate" */
    PIN_RST,
    PIN_SET,
    PIN_TOGGLE,
};

/* Idiot check */
#if (PIN_RST == PIN_SET == PIN_TOGGLE) 
#error ONE OF PIN_RST , PIN_SET, PIN_TOGGLE ARE NOT UNIQUE. PLEASE SEE mcupin.h
#endif

/* Based on driver selection, alias the implementation of the gpio peripheral */
#if defined(USE_HAL_DRIVER)
#ifdef GPIO
#error >GPIO< HAS ALREADY BEEN DEFINED. PLEASE CHANGE THE NAME OF YOUR MACRO
#endif /* GPIO EXISTING DEFINITION CHECK */
#define GPIO GPIO_TypeDef
#else
#ifdef GPIO
#error >GPIO< HAS ALREADY BEEN DEFINED. PLEASE CHANGE THE NAME OF YOUR MACRO
#endif /* GPIO EXISTING DEFINITION CHECK */
#define GPIO struct gpio_regs
#endif /* HAL OR BAREMETAL ? */


/*
 * structure that consists of the gpio peripheral
 * instance and the pin number. The pin number is used
 * to mask the other control port values in the peripheral's
 * various control registers.
 */ 
struct mcu_pin
{   
    GPIO    *port;
    uint32_t bit;
};


/**
 * @fn writepin
 * @brief sets the output state of the given mcu_pin 
 * 
 * @param pin the pin structure for a given gpio peripheral
 * @param state the state to write the pin 
 */
void writepin(const struct mcu_pin *pin, enum pinstate state);


/**
 * @fn readpin
 * @brief Gets the state of the given mcu_pin
 * 
 * @param pin the pin structure for a given gpio peripheral
 * @return enum pinstate the state of the pin.
 */
enum pinstate readpin(const struct mcu_pin *pin);

#else
/* HEADER STUFF FOR A HOSTED (NON-MCU) APPLICATION GOES HERE */
#endif /* MCU_APP */

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_PIN */