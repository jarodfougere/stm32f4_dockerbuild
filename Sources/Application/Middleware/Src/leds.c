#if defined(MCU_APP)
#include "drivers.h" 
#include "leds.h"


void set_led(rg_led_t *led, LED_MODE_t mode)
{
    switch(mode)
    {
        case LED_MODE_off:
            writepin(led->green, PIN_RST);
            writepin(led->red, PIN_RST);
        case LED_MODE_green:
            writepin(led->green, PIN_SET);
            writepin(led->red, PIN_RST);
        case LED_MODE_red:
            writepin(led->green, PIN_RST);
            writepin(led->red, PIN_SET);
        case LED_MODE_red_blink:
            writepin(led->red, PIN_TOGGLE);
        case LED_MODE_green_blink:
            writepin(led->green, PIN_TOGGLE);
        case LED_MODE_red_green_blink:
            writepin(led->red, PIN_TOGGLE);
            writepin(led->green, PIN_TOGGLE);
        default:
            #if !defined(NDEBUG)
            FORCE_ASSERT
            #endif
        break;
    }
}

#endif


//todo: led lookup table 

