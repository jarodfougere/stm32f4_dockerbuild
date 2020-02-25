#ifndef RIMOT_MCUPIN
#define RIMOT_MCUPIN

#if defined(MCU_APP)
#include <stdint.h>

#include "drivers.h"

/* THESE REQUIRE PROPER INCLUSION OF A DEVICE HAL LAYER */
#define PIN_HIGH GPIO_PIN_SET
#define PIN_LOW  GPIO_PIN_RESET

typedef enum
{
    PIN_TYPE_output,
    PIN_TYPE_input,
    PIN_TYPE_adc,
    PIN_TYPE_dac,
    PIN_TYPE_data,
    PIN_TYPE_reserved, /* non sw configurable functions */
}   PIN_TYPE_t;

typedef struct
{   
    GPIO_TypeDef   *port;
    uint32_t       bit;
}   mcu_pin_t;

#endif

#endif