#ifndef LOWPOWER_MCUPIN
#define LOWPOWER_MCUPIN

#if defined(MCU_APP)
#include <stdint.h>
#include "device.h"


    typedef enum
    {
        OUTPUT_LEVEL_high,
        OUTPUT_LEVEL_low,
    }   OUTPUT_LEVEL_t;


    typedef enum
    {
        PIN_TYPE_output,
        PIN_TYPE_input,
        PIN_TYPE_adc,
        PIN_TYPE_dac,
        PIN_TYPE_data,
        PIN_TYPE_reserved, /* non sw configurable functions */
    }   PIN_TYPE_t;

    typedef enum
    {
        PIN_DATA_TYPE_serial,
        PIN_DATA_TYPE_i2c,
        PIN_DATA_TYPE_usb,     
    }   PIN_DATA_TYPE_t;

    typedef struct
    {   
        GPIO_TypeDef   *port;
        uint32_t       bit;
    }   mcu_pin_t;

#endif

#endif