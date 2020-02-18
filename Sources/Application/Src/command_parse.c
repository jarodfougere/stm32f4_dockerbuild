#include <stdio.h>
#include <string.h>

/* driver headers do not get included in the application modules */

/* middleware headers */
#include "middleware.h"

/* other application headers */
#include "main.h"
#include "command_parse.h"
#include "rimot_device.h"
#include "gpio_interface.h"



/* DECLARATIONS */
static const struct json_attr_t base_attrs[];
static const struct json_attr_t write_attrs[];
static const struct json_attr_t pin_config_attrs[];
static const struct json_attr_t pin_cmd_attrs[];


static struct pinConfig     temp_pin_config;
static struct pinCommand    temp_pin_cmd;
static struct rimot_dev_cfg temp_device_cfg;

static const struct json_attr_t base_attrs[] = 
{   
    {
        "system", 
        t_string, 
        .addr.string = serial_cmds.systemCommand, 
        .len = sizeof(serial_cmds.systemCommand)
    },

    {
        "read",   
        t_string, 
        .addr.string = serial_cmds.readCommand, 
        .len = sizeof(serial_cmds.readCommand)
    },

    {
        "write",  
        t_object, 
        .addr.attrs = write_attrs,
    },

    {
        "GPIO_PIN_CONFIG",
        t_object,
        .addr.attrs = pin_config_attrs,
    },

    {
        "GPIO_PIN_UPDATE",
        t_check,
        .dflt.check = "true",
    },


    {
        "GPIO_DEVICE_INFO",
        t_ignore,
    },

    {
        "outpostID",
        t_string,
        .addr.string = temp_device_cfg.outpostID,
    },

    {
        "GPIO_PIN_CMD",
        t_object,
        .addr.attrs = pin_cmd_attrs,       
    },

    {NULL},
};


static const struct json_attr_t write_attrs[] = 
{
    {
        "hb_interval", 
        t_integer,
        .addr.integer = &temp_device_cfg.heartbeat_interval,
    },

    {
        "pin_info_interval",
        t_integer,
        .addr.integer = &temp_device_cfg.data_interval,
    },

    {
        "mode",
        t_integer,
        .addr.integer = &temp_device_cfg.mode,
    },

    {NULL},
};

static const struct json_attr_t pin_config_attrs[] = 
{
    {
        "id", 
        t_integer, 
        .addr.integer = &temp_pin_config.id
    },

    {
        "type", 
        t_integer, 
        .addr.integer = &temp_pin_config.type
    },

    {
        "active", 
        t_integer, 
        .addr.integer = &temp_pin_config.active
    },

    {
        "label", 
        t_integer,  
        .addr.integer = &temp_pin_config.label
    },

    {
        "priority", 
        t_integer, 
        .addr.integer = &temp_pin_config.priority
    },

    {
        "debounce", 
        t_integer, 
        .addr.integer = &temp_pin_config.period
    },

    {
        "redHigh",  
        t_real,    
        .addr.real = &temp_pin_config.setpoints.numerics.redHigh
    },

    {
        "yellowHigh", 
        t_real, 
        .addr.real = &temp_pin_config.setpoints.numerics.yellowHigh
    },

    {
        "yellowLow", 
        t_real, 
        .addr.real = &temp_pin_config.setpoints.numerics.yellowLow
    },
    {
        "redLow", 
        t_real, 
        .addr.real = &temp_pin_config.setpoints.numerics.redLow
    },

    {
        "state", 
        t_integer, 
        .addr.integer = &temp_pin_config.setpoints.digitals.default_state
    },

    {
        "trigger", 
        t_integer, 
        .addr.integer = &temp_pin_config.setpoints.digitals.trigger_state
    },
};


static const struct json_attr_t pin_cmd_attrs[] = 
{
    {
        "id", 
        t_integer, 
        .addr.integer = &temp_pin_cmd.id
    },

    {
        "type", 
        t_integer, 
        .addr.integer = &temp_pin_cmd.type
    },

    {
        "trigger", 
        t_integer, 
        .addr.integer = &temp_pin_cmd.trigger
    },
};



int parse_command(const char * command)
{   
#if defined(COMMAND_PARSE_DEBUG_ENABLE)
    transmit_serial("parsing command >%s<\n", command);
#endif

    const char *end_ptr = command;
    int status = json_read_object(command, base_attrs, &end_ptr);
    if (status != 0)
    {
        if('\0' != *end_ptr)
        {   
#if defined(COMMAND_PARSE_DEBUG_ENABLE)
            printf("PARSING FAILED. ENDPTR != \\0. *endptr == %c\n", *end_ptr);
#endif
        }
        puts(json_error_string(status));
    }

    transmit_serial( "status = %d\n"
            "id = %d\n"
            "type = %d\n"
            "active = %d\n"
            "label = %d\n"
            "priority = %d\n"
            "debounce = %d\n"
            "redHigh = %f\n"
            "yellowHigh = %f\n"
            "yellowLow = %f\n"
            "redLow = %f\n"
            "default_state = %d\n"
            "trigger_state = %d\n",
            status,
            temp_pin_config.id,
            temp_pin_config.type,
            temp_pin_config.active,
            temp_pin_config.label,
            temp_pin_config.priority,
            temp_pin_config.period,
            temp_pin_config.setpoints.numerics.redHigh,
            temp_pin_config.setpoints.numerics.yellowHigh,
            temp_pin_config.setpoints.numerics.yellowLow,
            temp_pin_config.setpoints.numerics.yellowLow,
            temp_pin_config.setpoints.digitals.default_state,
            temp_pin_config.setpoints.digitals.trigger_state
            );

    return status;
}


