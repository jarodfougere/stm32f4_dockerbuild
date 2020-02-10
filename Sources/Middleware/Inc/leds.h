#ifndef LOWPOWER_LEDS
#define LOWPOWER_LEDS
#include <stdint.h>
#include "mcupin.h"


#if defined(MCU_APP)
typedef enum
{
    LED_TYPE_gpio,
    LED_TYPE_rf,
    LED_TYPE_system
}   LED_TYPE_t;


typedef enum
{
    LED_MODE_off,
    LED_MODE_green,
    LED_MODE_red,
    LED_MODE_red_blink,
    LED_MODE_green_blink,
    LED_MODE_red_green_blink,
}   LED_MODE_t;

typedef struct
{
    mcu_pin_t green;
    mcu_pin_t red;
}   rg_led_t;

/* monocolor leds are only a single pin */
typedef mcu_pin_t led_t;


void set_led(rg_led_t led, LED_MODE_t mode);

#endif
#endif
