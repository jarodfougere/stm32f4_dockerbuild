#include "gpio_interface.h"

const uint8_t max_pin_index[NUM_PIN_TYPES] = 
{   
    /* subtract 1 because arrays start at 0 */
    NUM_DIGITAL_INPUTS - 1,
    NUM_RELAYS - 1,
    NUM_BATTERIES - 1,
};


/* index offset for a given pin type */
const uint8_t pin_index_base[NUM_PIN_TYPES] = 
{
    0,                
    NUM_DIGITAL_INPUTS,
    NUM_RELAYS,
};








