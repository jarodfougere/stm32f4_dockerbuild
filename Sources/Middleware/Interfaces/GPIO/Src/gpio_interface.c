#warning NO DOXYGEN HEADER IN GPIO INTERFACE.C

#include <stdint.h>
#include <stdlib.h>

#include "gpio_interface.h"

/* Sub-interfaces */


#include "comms_interface.h"

/* Drivers */
#include "rimot_adc.h"
#include "rimot_dma.h"
#include "rimot_pin_aliases.h"

/* Misc */
#include "rimot_LL_debug.h"

struct gpio_interface_config_structure
{
    relayConfig_t *output[NUM_RELAY_PINS];
    inputConfig_t *inputs[NUM_DIGITAL_INPUT_PINS];
    batConfig_t   *battery[NUM_BATTERY_PINS];
};


gpioConfig_t* gpioConfigInit(void)
{   
    gpioConfig_t* cfg = (gpioConfig_t*)malloc(sizeof(gpioConfig_t));
    LL_ASSERT(NULL != cfg);

    int i;
    for(i = GPIO_PIN_ID1; i < NUM_RELAY_PINS; i++)
    {
        cfg->output[i] = newRelayConfig((GPIO_PIN_ID_t)(i + 1));
    }

    for(i = GPIO_PIN_ID1; i < NUM_BATTERY_PINS; i++)
    {
        cfg->battery[i] = newBatteryConfig((GPIO_PIN_ID_t)(i + 1));
    }

    for(i = GPIO_PIN_ID1; i < NUM_DIGITAL_INPUT_PINS; i++)
    {
        cfg->inputs[i] = newInputConfig((GPIO_PIN_ID_t)(i + 1));
    }

    return cfg;
}


relayConfig_t* gpioGetRelay(const gpioConfig_t *cfg, GPIO_PIN_ID_t pin)
{   
    switch(pin)
    {
        case GPIO_PIN_ID1:
        case GPIO_PIN_ID2:
        case GPIO_PIN_ID3:
        case GPIO_PIN_ID4:
            return (relayConfig_t*)&cfg->output[pin];
        break;
        default:
            return NULL;
        break;
    }
}


inputConfig_t* gpioGetInput(const gpioConfig_t* cfg, GPIO_PIN_ID_t pin)
{
    switch(pin)
    {
        case GPIO_PIN_ID1:
        case GPIO_PIN_ID2:
        case GPIO_PIN_ID3:
        case GPIO_PIN_ID4:
        case GPIO_PIN_ID5:
        case GPIO_PIN_ID6:
        case GPIO_PIN_ID7:
        case GPIO_PIN_ID8:
            return (inputConfig_t*)&cfg->inputs[pin];
        break;
        default:
            return NULL;
        break;
    }
}


batConfig_t* gpioGetBattery(const gpioConfig_t *cfg, GPIO_PIN_ID_t pin)
{   
    switch(pin)
    {
        case GPIO_PIN_ID1:
        case GPIO_PIN_ID2:
        case GPIO_PIN_ID3:
        case GPIO_PIN_ID4:
            return (batConfig_t*)&cfg->battery[pin];
        break;
        default:
            return NULL;
        break;
    }
}


/* Error codes */
typedef enum
{
    PCFGERR_ok,
    PCFGERR_no_id,
    PCFGERR_no_type,
    PCFGERR_no_active,
    PCFGERR_no_debounce,
    PCFGERR_no_state,
    PCFGERR_no_trigger,
    PCFGERR_no_redhigh,
    PCFGERR_no_yellowhigh,
    PCFGERR_no_yellowlow,
    PCFGERR_no_redlow,
    PCFGERR_wrong_type,
    PCFGERR_id_oob,
    PCFGERR_type_oob,
    PINCONIFGERR_active_oob,
    PCFGERR_debounce_oob, 
    PCFGERR_redhigh_oob,
    PCFGERR_yellowhigh_oob,
    PCFGERR_yellowlow_oob,
    PCFGERR_redlow_oob,
    PCFGERR_state_oob,
    PCFGERR_trigger_oob,
    PCFGERR_battery_sp_out_of_order,
}   PCFGERR_t;


static const char *PCFGERR_messages[] = 
{
    [PCFGERR_ok] = "",
    [PCFGERR_no_id] = "missing \"id\" attribute",
    [PCFGERR_no_type] = "missing \"type\" attribute",
    [PCFGERR_no_active] = "missing \"active\" attribute",
    [PCFGERR_no_debounce] = "missing \"debounce\" attribute",
    [PCFGERR_no_state] = "missing \"state\" attribute",
    [PCFGERR_no_trigger] = "missing \"trigger\" attribute",
    [PCFGERR_no_redhigh] = "missing \"redHigh\" attribute",
    [PCFGERR_no_yellowhigh] = "missing \"yellowHigh\" attribute",
    [PCFGERR_no_yellowlow] = "missing \"yellowLow\" attribute",
    [PCFGERR_no_redlow] = "missing \"redLow\" attribute",
    [PCFGERR_wrong_type] = "attribute fields invalid for given type",
    [PCFGERR_id_oob] = "value of attribute \"id\" out of bounds",
    [PCFGERR_type_oob] = "value of attribute \"type\" out of bounds",
    [PINCONIFGERR_active_oob] = "value of attribute \"active\" out of bounds",
    [PCFGERR_debounce_oob] = "value of attribute \"debounce\" out of bounds",
    [PCFGERR_redhigh_oob ] = "value of \"redHigh\" attribute out of bounds",
    [PCFGERR_yellowhigh_oob] = "value of \"yellowHigh\" attribute out of \
                                bounds",
    [PCFGERR_yellowlow_oob] = "value of \"yellowLow\" attribute out of bounds",
    [PCFGERR_redlow_oob] = "value of \"redLow\" attribute out of bounds",
    [PCFGERR_state_oob] = "value of \"state\" attribute out of bounds",
    [PCFGERR_trigger_oob] = "value of \"trigger\" attribute out of bounds",
    [PCFGERR_battery_sp_out_of_order] = "battery setpoints are out of order."
};




void gpioIF_initBattery(void)
{
#if defined(MCU_APP)
    adcEnable();
    adcSetRes(ADC_RES_12);
    adcSetPrescaler(ADC_PRESCALER_2);
    adcEnableInterrupt(ADC_ISR_overrun);
    adcEnableInterrupt(ADC_ISR_regular_end_of_conversion);
    adcSetConvSeqPin(BAT_PIN1, ADC_GROUPTYPE_regular, ADC_SEQ_POS_1);
    adcSetConvSeqPin(BAT_PIN2, ADC_GROUPTYPE_regular, ADC_SEQ_POS_2);
    adcSetConvSeqPin(BAT_PIN3, ADC_GROUPTYPE_regular, ADC_SEQ_POS_3);
    adcSetConvSeqPin(BAT_PIN4, ADC_GROUPTYPE_regular, ADC_SEQ_POS_4);
#else
    comms_printf("Executed initBattery%c", '\n');
#endif /* MCU_APP */
}


void gpioIF_measureBattery(void)
{
    adcStartConversion(ADC_GROUPTYPE_regular);
}


void gpioIF_initInputs(void)
{
    /* Set input pins to digital input mode */


}


void gpioIF_initRelays(void)
{
    /* Set state pins to output mode */
    
    /* Set pulse pins to output mode */


}
