#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"

struct pin_map
{
    struct gpio_port *port; /* The port register structure  */
    mcu_word          bit;  /* The pin# for the port        */
};

/* modes for a given mcu gpio pin */
typedef enum
{   
    /* Critical that the values are unsigned */
    GPIO_MODE_input     = 0UL,
    GPIO_MODE_output    = 1UL,       
    GPIO_MODE_alternate = 2UL,
    GPIO_MODE_analog    = 3UL,  
}   GPIO_MODE_t;

/* transition speeds for a given mcu gpio pin */
typedef enum
{
    GPIO_SPEED_low  = 0UL,
    GPIO_SPEED_med  = 1UL,
    GPIO_SPEED_fast = 2UL,
    GPIO_SPEED_high = 3UL,
}   GPIO_SPEED_t;

/* output modes for a gvien mcu gpio pin */
typedef enum
{
    GPIO_OUTPUT_MODE_push_pull  = 0UL,
    GPIO_OUTPUT_MODE_open_drain = 1UL,
}   GPIO_OUTPUT_MODE_t;


/**
 * @fn set_pin_mode
 * @brief Set the pin mode of a given gpio pin
 * 
 * @param mode one of GPIO_MODE_t
 * @param pin  the mcu pin number
 */
void set_pin_mode(GPIO_MODE_t mode, mcu_word pin);

struct pin_map* gpio(mcu_word pin);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_GPIO */