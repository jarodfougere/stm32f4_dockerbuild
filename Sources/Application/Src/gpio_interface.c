#include "gpio_interface.h"

#include "middleware.h"

/* DECLARATIONS */
static const char *PCFGERR_messages[];
static const int32_t max_pin_index[NUM_PIN_TYPES];
static const int32_t pin_index_base[NUM_PIN_TYPES];

static const int32_t max_pin_index[NUM_PIN_TYPES] = 
{   
    /* subtract 1 because arrays start at 0 */
    NUM_DIGITAL_INPUTS - 1,
    NUM_RELAYS - 1,
    NUM_BATTERIES - 1,
};

/* index offset for a given pin type */
static const int32_t pin_index_base[NUM_PIN_TYPES] = 
{
    0,                
    NUM_DIGITAL_INPUTS,
    NUM_RELAYS,
};


/* THIS CHECKS THE VALUES FOR GPIO PIN CONFIG ATTRIBUTES */
static int32_t validate_pin_command(struct pinCommand *cmd);
static PCFGERR_t validate_pin_config(const struct pinConfig *cfg);


int32_t update_pin_config(struct pinConfig *dst, struct pinConfig *src)
{
    PCFGERR_t status  = validate_pin_config(src);
    if(0 == status)
    {
        memcpy(&dst[GPIO_PIN(src->type, src->id)],src,sizeof(struct pinConfig));
    }
    else
    {
        transmit_serial("{\"pin config error\":\"%s\"}\r\n", PCFGERR_messages[status]);
    }
    return (int32_t)status; /* recast so compiler doesnt complain */
}


/* PUBLIC FUNCTIONS */
int32_t execute_pin_command(struct pinCommand *cmd)
{
    int32_t status = validate_pin_command(cmd);
    if(0 == status)
    {

    }
    else
    {
        
    }

    return status;
}


static PCFGERR_t validate_pin_config(const struct pinConfig *cfg)
{

    if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->id)
    {
        return PCFGERR_no_id;
    }   

    switch((PINTYPE_t)cfg->type)
    {
        case PINTYPE_relay_output:
            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->setpoints.relay.default_state)
            {
                return PCFGERR_no_state;
            }
            else
            {
                switch(cfg->setpoints.relay.default_state)
                {
                    case RELAYPOS_closed:
                    case RELAYPOS_open:
                        break;
                    default:
                        return PCFGERR_state_oob;
                        break;
                }
            }
            
            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->period)
            {
                return PCFGERR_no_debounce;
            }
            else
            {
                if(cfg->period < GPIO_PIN_CONFIG_MIN_RELAY_DEBOUNCE_S)
                {
                    return PCFGERR_debounce_oob;
                }
            }
            
        case PINTYPE_digital_input:
            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->setpoints.input.trigger)
            {
                return PCFGERR_no_trigger;
            }
            else
            {
                switch((TRIGGERMODE_t)cfg->setpoints.input.trigger)
                {
                    case TRIGGERMODE_high:
                    case TRIGGERMODE_low:
                        break;
                    default:
                        return PCFGERR_trigger_oob;
                    break;
                }
            }

            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->period)
            {
                return PCFGERR_no_debounce;
            }
            else
            {
                if(cfg->period < GPIO_PIN_CONFIG_MIN_INPUT_DEBOUNCE_S)
                {
                    return PCFGERR_debounce_oob;
                }
            }
        case PINTYPE_analog_input:

            /* VALIDATE EXISTENCE OF SETPOINTS */
            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->setpoints.battery.redHigh)
            {
                return PCFGERR_no_redhigh;
            }

            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->setpoints.battery.yellowHigh)
            {
                return PCFGERR_no_yellowhigh;
            }

            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->setpoints.battery.yellowLow)
            {
                return PCFGERR_no_yellowlow;
            }

            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->setpoints.battery.redLow)
            {
                return PCFGERR_no_redlow;
            }

            /* VALIDATE ORDERING OF SETPOINTS */
            if(!(cfg->setpoints.battery.redHigh > cfg->setpoints.battery.yellowHigh && cfg->setpoints.battery.yellowHigh > cfg->setpoints.battery.yellowLow && cfg->setpoints.battery.yellowLow > cfg->setpoints.battery.redLow && cfg->setpoints.battery.redLow > 0))
            {
                return PCFGERR_battery_sp_out_of_order;
            }

            if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->period)
            {
                return PCFGERR_no_debounce;
            }
            else
            {
                if(cfg->period < GPIO_PIN_CONFIG_MIN_RELAY_DEBOUNCE_S)
                {
                    return PCFGERR_debounce_oob;
                }
            }

            break;
        default:
            return PCFGERR_type_oob;
            break;
    }

    switch((PINMODE_t)cfg->active)
    {
        case PINMODE_active:
        case PINMODE_inactive:
            break;
        default:
            return PINCONIFGERR_active_oob;
            break;
    }

    if(GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL == cfg->active)
    {
        return PINCONIFGERR_active_oob;
    }

    return PCFGERR_ok;
}

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
    [PCFGERR_yellowhigh_oob] = "value of \"yellowHigh\" attribute out of bounds",
    [PCFGERR_yellowlow_oob] = "value of \"yellowLow\" attribute out of bounds",
    [PCFGERR_redlow_oob] = "value of \"redLow\" attribute out of bounds",
    [PCFGERR_state_oob] = "value of \"state\" attribute out of bounds",
    [PCFGERR_trigger_oob] = "value of \"trigger\" attribute out of bounds",
    [PCFGERR_battery_sp_out_of_order] = "battery setpoints are out of order."
};


static int32_t validate_pin_command(struct pinCommand *cmd)
{
    int32_t is_valid = 0;

    //TODO: DO STUFF TO VALIDATE THE PIN COMMAND

    return is_valid;
}
