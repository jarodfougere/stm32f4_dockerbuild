#include <stdint.h>

#include "gpio_interface.h"
#include "comms_interface.h"



const struct pin_cfg pin_config_defaults = PIN_CFG_DFLT_INITIALIZER;

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
static PCFGERR_t validate_pin_command(const struct pin_command *cmd);
static PCFGERR_t validate_pin_config(const struct pin_cfg *cfg);


int32_t store_pin_config(struct pin_cfg *dst, const struct pin_cfg *src)
{
    PCFGERR_t status  = validate_pin_config(src);
    if(0 == status)
    {
        memcpy(&dst[GPIO_PIN(src->type, src->id)],src, sizeof(struct pin_cfg));
    }
    else
    {
        comms_printf(COMMS_usb, "{\"pin config error\":\"%s\"}\r\n", PCFGERR_messages[status]);
    }
    return (int32_t)status; /* recast so compiler doesnt complain */
}

int32_t reset_pin_config(struct pin_cfg *dst)
{   
    if(NULL != dst)
    {
        memcpy(dst, &pin_config_defaults, sizeof(struct pin_cfg));
    }
    else
    {
        return 1;
    }
    return 0;
}

/* PUBLIC FUNCTIONS */
int32_t execute_pin_command(const struct pin_command *cmd)
{
    PCFGERR_t status = validate_pin_command(cmd);
    if(PCFGERR_ok == status)
    {
        comms_printf(COMMS_usb, "validated pin command! Executing cmd : id == %d, id == %d, trigger == %d\n", cmd->id, cmd->type, cmd->trigger);
    }
    else
    {
        comms_printf(COMMS_usb, "{\"pin config error\":\"%s\"}\r\n", PCFGERR_messages[status]);
    }
    return status;
}


static PCFGERR_t validate_pin_config(const struct pin_cfg *cfg)
{   
    /* validate existence of type attribute */
    if(PIN_CONFIG_UNSET_VAL == cfg->type)
    {
        return PCFGERR_no_type;
    }
    else /* validate value of type attribute */
    {
        switch((PINTYPE_t)cfg->type)
        {
            case PINTYPE_relay_output:
                if(PIN_CONFIG_UNSET_VAL == cfg->setpoints.relay.default_state)
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
                
                if(PIN_CONFIG_UNSET_VAL == cfg->period)
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
                if(PIN_CONFIG_UNSET_VAL == cfg->setpoints.input.trigger)
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

                if(PIN_CONFIG_UNSET_VAL == cfg->period)
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
                if(PIN_CONFIG_UNSET_VAL == cfg->setpoints.battery.redHigh)
                {
                    return PCFGERR_no_redhigh;
                }

                if(PIN_CONFIG_UNSET_VAL == cfg->setpoints.battery.yellowHigh)
                {
                    return PCFGERR_no_yellowhigh;
                }

                if(PIN_CONFIG_UNSET_VAL == cfg->setpoints.battery.yellowLow)
                {
                    return PCFGERR_no_yellowlow;
                }

                if(PIN_CONFIG_UNSET_VAL == cfg->setpoints.battery.redLow)
                {
                    return PCFGERR_no_redlow;
                }

                /* VALIDATE ORDERING OF SETPOINTS */
                if(!(cfg->setpoints.battery.redHigh > cfg->setpoints.battery.yellowHigh && cfg->setpoints.battery.yellowHigh > cfg->setpoints.battery.yellowLow && cfg->setpoints.battery.yellowLow > cfg->setpoints.battery.redLow && cfg->setpoints.battery.redLow > 0))
                {
                    return PCFGERR_battery_sp_out_of_order;
                }

                if(PIN_CONFIG_UNSET_VAL == cfg->period)
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
    }
    

    /* validate id attribute */
    if(PIN_CONFIG_UNSET_VAL == cfg->id)
    {
        return PCFGERR_no_id;
    }
    else if(cfg->id < 0 || cfg->id > max_pin_index[cfg->type])
    {
        return PCFGERR_id_oob;
    }        

    /* validate active attribute */
    if(PIN_CONFIG_UNSET_VAL == cfg->active)
    {
        return PINCONIFGERR_active_oob;
    }
    else
    {
        switch((PINMODE_t)cfg->active)
        {
            case PINMODE_active:
            case PINMODE_inactive:
                break;
            default:
                return PINCONIFGERR_active_oob;
                break;
        }
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


static PCFGERR_t validate_pin_command(const struct pin_command *cmd)
{
    /* validate type attribute */
    if(PIN_CONFIG_UNSET_VAL == cmd->type)
    {
        return PCFGERR_no_type;
    }
    else
    {
        switch(cmd->type)
        {
            case PINTYPE_analog_input:
            case PINTYPE_digital_input:
            case PINTYPE_relay_output:
                break;
            default:
            return PCFGERR_type_oob;
            break;
        }
    }

    /* validate id attribute */
    if(PIN_CONFIG_UNSET_VAL == cmd->id)
    {
        return PCFGERR_no_id;
    }
    else if(cmd->id < 0 || cmd->id > max_pin_index[cmd->type])
    {
        return PCFGERR_id_oob;
    }   
    
    /* validate trigger attribute */
    if(PIN_CONFIG_UNSET_VAL == cmd->trigger)
    {
        return PCFGERR_no_trigger;
    }
    else
    {
        switch((PINCMD_t)cmd->trigger)
        {
            case PINCMD_start:
            case PINCMD_stop:
                break;
            default:
                return PCFGERR_trigger_oob;
                break;
        }
    }

    return PCFGERR_ok;
}
