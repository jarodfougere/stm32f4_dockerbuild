#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_pin_aliases.h"

/* modes for a given mcu gpio pin */
typedef enum
{   
    /* Critical that the values are unsigned */
    GPIO_MODE_input     = 0U,
    GPIO_MODE_output    = 1U,       
    GPIO_MODE_alternate = 2U, /* PERIPHERAL FUNCS. */
    GPIO_MODE_analog    = 3U, 
}   GPIO_MODE_t;

/* transition speeds for a given mcu gpio pin */
typedef enum
{
    GPIO_SPEED_low  = 0U,
    GPIO_SPEED_med  = 1U,
    GPIO_SPEED_fast = 2U,
    GPIO_SPEED_high = 3U,
}   GPIO_SPEED_t;

/* output modes for a gvien mcu gpio pin */
typedef enum
{
    GPIO_OUTPUT_MODE_push_pull  = 0U,
    GPIO_OUTPUT_MODE_open_drain = 1U,
}   GPIO_OUTPUT_MODE_t;


/**
 * @fn gpio_pinLookup
 * @brief Returns a structure that maps a pin number on the
 * MCU to a GPIO port peripheral and the bit in that peripheral's
 * registers corresponding to the mcu pin.
 * 
 * @param pin the number of the pin on the mcu.
 * @return struct pin_map* the mapping structure
 */
struct pin_map* gpio_pinlookup(mcu_word mcu_pin_number);


/**
 * @fn gpio_setPinMode
 * @brief Set the pin mode of a given gpio pin
 * 
 * @param mode one of GPIO_MODE_t
 * @param pin  the mcu pin number
 */
void gpio_setPinMode(GPIO_MODE_t mode, mcu_word pin);


/**
 * @fn gpio_enablePinClock
 * @brief enables the AHB bus clock for the gpio peripheral corresponding
 * to the mcu pin number.
 * 
 * @param mcu_pin_number : the number of the mcu pin desired to be used as a 
 * gpio
 */
void gpio_enablePinClock(MCUPIN_t pin);




#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_GPIO */