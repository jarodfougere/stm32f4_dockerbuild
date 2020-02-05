#ifndef LOWPOWER_GPIO_INTERFACES
#define LOWPOWER_GPIO_INTERFACES
#include <stdint.h>

#include "setpoints.h"

/* gpio interface "pin" type */
typedef enum
{
    PINTYPE_digital_input,
    PINTYPE_relay_output,
    PINTYPE_analog_input,
}   PINTYPE_t;

/* active/inactive pins */
#define INTERFACE_PIN_INACTIVE 0
#define INTERFACE_PIN_ACTIVE 1

#define NUM_PIN_TYPES      3 /* input, relay, analog */
#define NUM_DIGITAL_INPUTS 8
#define NUM_RELAYS         4
#define NUM_BATTERIES      4

/* interface array indexing for relay types */
#define hold_time_index     0
#define default_state_index 1
#define current_state_index 2

/* interface array indexing for digital input types */
#define debounce_time_index 0
#define trigger_level_index 1

/* battery interface (setpoint) array indexing is provided in setpoints.h */
/* this is because RF, temp, hum, AND gpio use setpoints */


/* this is a single pin configuration to be stored in non-volatile memory   */
typedef struct
{
    uint8_t         active;         /* if the "pin" is being used or not    */
    uint8_t         label;          /* normalized device type for analytics */
    uint8_t         priority;       /* pin priority (not implemented )      */
    uint8_t         reserved;       /* packing alignment                    */
    uint32_t        interface[NUM_SETPOINT_THRESHHOLDS];   /* type-specific */
}   pin_config_t;

extern const uint8_t max_pin_index[NUM_PIN_TYPES];
extern const uint8_t pin_index_base[NUM_PIN_TYPES];

#define GPIO_PIN(type, idx) (pin_index_base[type] + idx)


#endif