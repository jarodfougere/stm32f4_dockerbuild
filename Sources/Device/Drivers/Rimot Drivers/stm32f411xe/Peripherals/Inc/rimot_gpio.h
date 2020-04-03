#ifndef RIMOT_MCU_GPIO
#define RIMOT_MCU_GPIO
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"

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

struct pin_map
{
    struct gpio_port *port;
    mcu_word          bit;
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