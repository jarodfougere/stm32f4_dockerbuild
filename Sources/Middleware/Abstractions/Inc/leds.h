#ifndef RIMOT_LEDS
#define RIMOT_LEDS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

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
    struct mcu_pin green;
    struct mcu_pin red;
}   rg_led_t;

/* monocolor leds are only a single pin */
typedef struct mcu_pin led_t;


void set_led(rg_led_t *led, LED_MODE_t mode);

#else /* MCU_APP IS NOT DEFINED */


#endif /* MCU_APP */

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_LEDS */
