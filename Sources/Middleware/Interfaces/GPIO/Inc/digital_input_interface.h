#ifndef RIMOT_DIGITAL_INPUT_INTERFACE
#define RIMOT_DIGITAL_INPUT_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "pin_config_interface.h"

#define NUM_DIGITAL_INPUT_PINS 8
#define DIGITAL_INPUT_DEFAULT_DEBOUNCE 10 /* 10*100ms = 1second default */

typedef enum
{
    INPUT_TRIGGERMODE_high = 1,
    INPUT_TRIGGERMODE_low  = 0,
}   INPUT_TRIGGERMODE_t;

typedef struct gpio_input_config inputConfig_t;

inputConfig_t* newInputConfig(GPIO_PIN_ID_t id);
INPUT_TRIGGERMODE_t inputGetTriggerMode(const inputConfig_t *input);
uint32_t inputGetDebounceTime(const inputConfig_t *input);
pinCfgCore_t* inputGetPinConfig(const inputConfig_t *input);
void inputSetTriggerMode(inputConfig_t *input, INPUT_TRIGGERMODE_t mode);
void inputSetDebounceTime(inputConfig_t *input, uint32_t debounceTime);


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DIGITAL_INPUT_INTERFACE */
