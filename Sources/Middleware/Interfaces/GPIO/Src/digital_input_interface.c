#include <stdint.h>
#include <stdlib.h>

#include "pin_config_interface.h"
#include "digital_input_interface.h"
#include "rimot_LL_debug.h"



struct gpio_input_config
{
    pinCfgCore_t pin;
    struct
    {   
        INPUT_TRIGGERMODE_t triggerMode;
        uint32_t debounceTime;  /* units in multiples of 100 ms */
    }   input;
};


inputConfig_t* newInputConfig(GPIO_PIN_ID_t id)
{
    inputConfig_t *cfg = (inputConfig_t*)malloc(sizeof(inputConfig_t));
    LL_ASSERT(NULL != cfg);
    LL_ASSERT(id > 0);
    LL_ASSERT(id <= NUM_DIGITAL_INPUT_PINS);
    pinCfg_resetToDefault(&cfg->pin, id, GPIO_PINTYPE_digital_input);
    cfg->input.debounceTime = DIGITAL_INPUT_DEFAULT_DEBOUNCE;  
    cfg->input.triggerMode  = INPUT_TRIGGERMODE_high; /* Default trigger mode */
    return cfg;
}


INPUT_TRIGGERMODE_t inputGetTriggerMode(const inputConfig_t *input)
{   
    LL_ASSERT(NULL != input);
    return (INPUT_TRIGGERMODE_t)input->input.triggerMode;
}

uint32_t inputGetDebounceTime(const inputConfig_t *input)
{
    LL_ASSERT(NULL != input);
    return (uint32_t)input->input.debounceTime;
}


pinCfgCore_t* inputGetPinConfig(const inputConfig_t *input)
{
    LL_ASSERT(NULL != input);
    return (pinCfgCore_t*)&input->pin;
}


void inputSetTriggerMode(inputConfig_t *input, INPUT_TRIGGERMODE_t mode)
{
    LL_ASSERT(NULL != input);
    input->input.triggerMode = mode;
}

void inputSetDebounceTime(inputConfig_t *input, uint32_t debounceTime)
{
    LL_ASSERT(NULL != input);
    input->input.debounceTime = debounceTime;
}
