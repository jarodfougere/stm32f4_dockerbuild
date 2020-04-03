/**
 * @file leds.c
 * @author Carl Mattatall
 * @brief This module provides an "led" abstraction for modules
 * at the middleware layer that hides the details of the LED
 * pinout, cathode configuration, and polarity / current pull-push
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

/* platform check */
#if defined(MCU_APP)

/* driver selection */
#if defined(USE_HAL_DRIVER)
#include "stm32f4xx.h"      /* CMSIS definitions */ 
#include "stm32f4xx_hal.h"  /* stm32 hal apis */
#else
#include "rimot_gpio.h" /* my baremetal register overlay */
#endif 

#include "leds.h"


void set_led(rg_led_t *led, LED_MODE_t mode)
{   
    /* TODO: use lookup table for the led_t structures. not switch  */
    /* [APRIL 2, 2020 - CARL MATTATALL]                             */
    switch(mode)
    {
        case LED_MODE_off:
            writepin(&led->green, PIN_RST);
            writepin(&led->red, PIN_RST);
        case LED_MODE_green:
            writepin(&led->green, PIN_SET);
            writepin(&led->red, PIN_RST);
        case LED_MODE_red:
            writepin(&led->green, PIN_RST);
            writepin(&led->red, PIN_SET);
        case LED_MODE_red_blink:
            writepin(&led->red, PIN_TOGGLE);
        case LED_MODE_green_blink:
            writepin(&led->green, PIN_TOGGLE);
        case LED_MODE_red_green_blink:
            writepin(&led->red, PIN_TOGGLE);
            writepin(&led->green, PIN_TOGGLE);
        default:
#if !defined(NDEBUG)
            while(1)
            {
                /* hang forever */
            }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}

#endif /* MCU APP */


