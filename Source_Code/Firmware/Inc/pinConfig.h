#ifndef GPIO_PINCFG
#define GPIO_PINCFG
#include <stdint.h>

#include "cmsis_compiler.h"

#define INVALID_PIN_CONFIG_VAL -1
#define INVALID_PIN_ID INVALID_PIN_CONFIG_VAL
#define INVALID_PIN_LABEL INVALID_PIN_CONFIG_VAL
#define INVALID_PIN_PRIO INVALID_PIN_CONFIG_VAL


// make sure these values are different
#define DIGITAL_INPUT_TYPEVAL 0
#define LATCHING_RELAY_TYPEVAL 1
#define ANALOG_INPUT_TYPEVAL 2
typedef enum
{
    INVALID_PIN_TYPE = INVALID_PIN_CONFIG_VAL,
    DIGITAL_INPUT    = DIGITAL_INPUT_TYPEVAL,
    LATCHING_RELAY   = LATCHING_RELAY_TYPEVAL,
    ANALOG_INPUT     = ANALOG_INPUT_TYPEVAL,
} pinType_t;

typedef enum
{
    INVALID_TRIGGER_LEVEL = INVALID_PIN_CONFIG_VAL,
    FALLING               = 0,
    RISING                = 1,
} triggerType_t;


typedef enum
{
    INVALID_ACTIVE_STATE = INVALID_PIN_CONFIG_VAL,
    INACTIVE             = 0,
    ACTIVE               = 1,
} activeType_t;

// type, id, active, label, (priority not used yet)
#define NUM_COMMON_PIN_CFG_KEYS 4


// Common fields for all interface "pins"
typedef struct
{
    pinType_t type;
    // the type of "pin" (input, output, analog input, etc...)

    activeType_t active;
    // whether or not the pin is registered on site page

    int16_t id;
    // the "pin" number on the decal

    int16_t label;
    // Normalized "type" of the device being controlled/monitored. ADDED AS
    // FUTUREPROOFING

    int8_t priority;
    // device priority as assigned on site page. ADDED AS FUTUREPROOFING

    uint32_t reserved; // used for word alignment.
} __PACKED pinConfig_t;

#endif