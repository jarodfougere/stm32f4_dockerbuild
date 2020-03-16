/**
 * @file serial_task.c
 * @author Carl Mattatall
 * @brief This module is responsible for serial communications, JSON parsing
 * JSON creation, and serial/usb/uart data transmissions for the application.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "serial_task.h"

#include "middleware_core.h"

#include "payloads.h"
#include "gpio_interface.h"
#include "comms_interface.h"

#include "system_config.h"
#include "mjson.h"

#define SYSTEM_KEY_MAX_LEN 50

/* expected json parse tree. laid-out in command_structure.c */
static const struct json_attr_t base_attrs[];
static const struct json_attr_t write_attrs[];
static const struct json_attr_t pin_config_attrs[];
static const struct json_attr_t pin_cmd_attrs[];

/* contains data parsed from the incoming command */
struct temp_fields_struct
{
    struct pin_cfg pin_cfg;
    struct pin_command pin_cmd;
    struct rimot_dev_cfg device_cfg;
    struct outpost_config outpost_cfg;
    char sys_string[SYSTEM_KEY_MAX_LEN];
    int outpost_status;
};
static struct temp_fields_struct temp;

static int32_t parse_command(const char *command, struct rimot_device *dev);

static const struct json_attr_t base_attrs[] =
{
    {
        .attribute = "system",
        .type = t_string,
        .addr.string = temp.sys_string,
        .len = SYSTEM_KEY_MAX_LEN,
        .nodefault = true,
    },

    {
        .attribute = "write",
        .type = t_object,
        .addr.attrs = write_attrs,
        .nodefault = true,
    },

    {
        .attribute = "GPIO_PIN_CONFIG",
        .type = t_object,
        .addr.attrs = pin_config_attrs,
        .nodefault = true,
    },

    {
        .attribute = "GPIO_PIN_UPDATE",
        .type = t_boolean,
        .addr.boolean = NULL,
        .nodefault = true,
    },

    {
        .attribute = "GPIO_DEVICE_INFO",
        .type = t_integer,
        .addr.integer = NULL,
        .nodefault = true,
    },

    {
        .attribute = "outpostID",
        .type = t_string,
        .addr.string = temp.outpost_cfg.outpostID,
        .len = sizeof(UNASSIGNED_OUTPOST_ID),
        .nodefault = true,
    },

    {
        .attribute = "GPIO_PIN_CMD",
        .type = t_object,
        .addr.attrs = pin_cmd_attrs,
        .nodefault = true,
    },

    {
        .attribute = "status",
        .type = t_integer,
        .addr.integer = &temp.outpost_status,
        .nodefault = false,
        .dflt.integer = 0, /* default is low power mode */
    },

    {NULL},
};

static const struct json_attr_t write_attrs[] =
{
    {
        .attribute = "hb_interval",
        .type = t_integer,
        .addr.integer = &temp.device_cfg.heartbeat_interval,
        .dflt.integer = INT_MAX,
        .nodefault = false,
    },

    {
        .attribute = "pin_info_interval",
        .type = t_integer,
        .addr.integer = &temp.device_cfg.data_interval,
        .dflt.integer = INT_MAX,
        .nodefault = false,
    },

    {
        .attribute = "mode",
        .type = t_integer,
        .addr.integer = &temp.device_cfg.mode,
        .dflt.integer = INT_MAX,
        .nodefault = false,
    },
    {NULL},
};

static const struct json_attr_t pin_config_attrs[] =
{
    {
        .attribute = "id",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.id,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "type",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.type,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "active",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.active,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "label",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.label,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "priority",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.priority,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "debounce",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.period,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "redHigh",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.setpoints.battery.redHigh,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "yellowHigh",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.setpoints.battery.yellowHigh,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "yellowLow",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.setpoints.battery.yellowLow,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "redLow",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.setpoints.battery.redLow,
        .dflt.integer = PIN_CONFIG_UNSET_VAL,
        .nodefault = false,
    },

    {
        .attribute = "state",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.setpoints.relay.default_state,
        .nodefault = true, //THIS VALUE IS OVERLAYED WITH BATTERY SP.
    },

    {
        .attribute = "trigger",
        .type = t_integer,
        .addr.integer = &temp.pin_cfg.setpoints.input.trigger,
        .nodefault = true, //THIS VALUE IS OVERLAYED WITH BATTERY SP.
    },

    {NULL}
};

static const struct json_attr_t pin_cmd_attrs[] =
{
    {
        .attribute = "id",
        .type = t_integer,
        .addr.integer = &temp.pin_cmd.id},

    {
        .attribute = "type",
        .type = t_integer,
        .addr.integer = &temp.pin_cmd.type},

    {
        .attribute = "trigger",
        .type = t_integer,
        .addr.integer = &temp.pin_cmd.trigger},

    {NULL}
};


/**
 * @brief This parses an incoming JSON to a command execution structure
 * 
 * @param command the input json string
 * @param dev ptr to the rimot device structure
 * @return int32_t 
 */
static int32_t parse_command(const char *command, struct rimot_device *dev)
{
    comms_printf(COMMS_usb, "parsing command >%s<\n", command);

    const char *end_ptr = command;
    int32_t key_idx = UNMATCHED_TOPLEVEL_KEY_IDX;
    int32_t status = json_read_object(command, base_attrs, &end_ptr, &key_idx);

    if (status != 0)
    {
        comms_printf(COMMS_usb, "ERROR:  ");
        comms_printf(COMMS_usb, "%s", json_error_string(status));
    }
    else
    {
        /* execute based on the key matched in top level json */
        comms_printf(COMMS_usb, "###\nKEY MATCHED IN JSON >%s< is %d\n###\n", key_idx);

        /* wipe the data holder */
        memset(&temp, 0, sizeof(struct temp_fields_struct));
    }
    return status;
}



/**
 * @brief This is the task handler for the serial events in the application
 *  task loop
 * 
 * @param dev 
 * @param state 
 */
void serial_task(struct rimot_device *dev, enum task_state *state)
{   
    switch(*state)
    {
        case TASK_STATE_init:
            comms_init();
            /* transition to ready after initialization */
            *state = TASK_STATE_ready; 
            break;
        case TASK_STATE_ready:
            /*
            TODO:
                check if data has been received

                if data recieved:
                    attempt to parse json.

                    if parse successful:
                        modify device state and execute accordingly
                    else:
                        do nothing
                else: (no data received)
                    ## IN THIS IMPLEMENTATION, NOTHING HAPPENS. 
                    ## OUTPOST MUST REQUEST DATA FROM THE SENSOR CARD.
                    
                endif (data received check)
            */

             /* block until USB serial RX buffer gets data again */
            *state = TASK_STATE_blocked; 
            break;
        case TASK_STATE_asleep:

        break;
        case TASK_STATE_blocked:
            /* TODO : check if USB serial buffer has become available */
            break;
    }
}
