#ifndef RIMOT_MCUPIN
#define RIMOT_MCUPIN

#if defined(MCU_APP)
#include <stdint.h>

#include "drivers.h"

/* THESE REQUIRE PROPER INCLUSION OF A DEVICE HAL LAYER */



enum pinstate
{   
    PIN_RST = GPIO_PIN_RESET,
    PIN_SET = GPIO_PIN_SET,
    PIN_TOGGLE,
};

#if (PIN_RST == PIN_SET == PIN_TOGGLE) 
#error ONE OF PIN_RST , PIN_SET, PIN_TOGGLE ARE NOT UNIQUE. PLEASE SEE mcupin.h
#endif

struct mcu_pin
{   
    GPIO_TypeDef   *port;
    uint32_t       bit;
};


void writepin(const struct mcu_pin *pin, enum pinstate state);

enum pinstate readpin(const struct mcu_pin *pin);


#endif

#endif