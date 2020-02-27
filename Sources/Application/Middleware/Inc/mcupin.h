#ifndef RIMOT_MCUPIN
#define RIMOT_MCUPIN

#if defined(MCU_APP)
#include <stdint.h>
#include "stm32f411xe.h" /* provide declaration of GPIO_Typedef */

enum pinstate
{   
    PIN_RST,
    PIN_SET,
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

/**
 * @brief sets the output state of the given mcu_pin 
 * 
 * @param pin 
 * @param state 
 */
void writepin(const struct mcu_pin *pin, enum pinstate state);


/**
 * @brief Gets the state of the given mcu_pin
 * 
 * @param pin 
 * @return enum pinstate 
 */
enum pinstate readpin(const struct mcu_pin *pin);


#endif

#endif