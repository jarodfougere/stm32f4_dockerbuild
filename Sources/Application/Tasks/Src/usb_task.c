/**
 * @file usb_task.c
 * @author Carl Mattatall
 * @brief This module is responsible for serial communications, JSON parsing
 * JSON creation, and usb data transmissions (via functionality from the comms
 * interface module) for the low power sensor card firmware application.
 * 
 * @version 0.3
 * @date 2020-03-25
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "usb_task.h"
#include "task.h"
#include "middleware_core.h"
#include "gpio_interface.h"
#include "comms_interface.h"
#include "system_interface.h"
#include "mjson.h"

#include "rimot_LL_debug.h"


static const struct json_attr base_keys[];
static const struct json_attr write_keys[];
static const struct json_attr pin_config_keys[];
static const struct json_attr pin_cmd_keys[];


/* Contains data parsed from receive JSONS */
struct temp_fields_struct
{
    pin_cfg_t pin_cfg;
    pin_command_t pin_cmd;
    struct outpost_config outpost_cfg;
    char sys_string[JSON_VAL_MAXLEN];
    char read_string[JSON_VAL_MAXLEN];
    int outpost_status;
}   temp;


static unsigned int data_interval;
static unsigned int heartbeat_interval;
static int device_mode;

typedef enum
{
    JSON_IDX_system,        /* system JSON commands                         */
    JSON_IDX_read,          /* read  JSON commands                          */
    JSON_IDX_write,         /* write JSON commands                          */
    JSON_IDX_pinconfig,     /* gpio pin config JSON commands                */  
    JSON_IDX_pinupdate,     /* gpio pin update JSON commands                */
    JSON_IDX_pincommand,    /* gpio pin command JSON commands               */
    JSON_IDX_gpiodevinfo,   /* gpio device info JSON commands               */
    JSON_IDX_outpostID,     /* outpost ID JSON commands                     */
    JSON_IDX_status,        /* outpost status (power mode) JSON commands    */
    JSON_IDX_transmitter,   /* transmitter ID config (RF) JSON command      */
}   JSON_IDX_t;


typedef enum
{
    JSON_SYS_IDX_info,  /* system info request  */
    JSON_SYS_IDX_main,  /* reset to main        */
    JSON_SYS_IDX_boot,  /* reset to bootloader  */
}   JSON_SYS_IDX_t;

typedef enum
{
    JSON_READ_IDX_hb,   /* heartbeat interval read request  */
    JSON_READ_IDX_tx,   /* transmit interval read request   */
    JSON_READ_IDX_fw,   /* firmware version read request    */
    JSON_READ_IDX_hw,   /* hardware version read request    */
}   JSON_READ_IDX_t;


typedef enum
{
    JSON_WRITE_IDX_hb,  /* heartbeat interval write request */
    JSON_WRITE_IDX_tx,  /* transmit interval write request  */
}   JSON_WRITE_IDX_t;


typedef enum
{
    SYS_CMD_info,
    SYS_CMD_main,
    SYS_CMD_boot
}   SYS_CMD_t;


static const struct json_attr base_keys[] =
{
    [JSON_IDX_system] = 
    {
        .attribute = "system",
        .type = t_string,
        .addr.string = temp.sys_string,
        .len = sizeof(temp.sys_string),
        .nodefault = true,
    },

    [JSON_IDX_read] = 
    {
        .attribute = "read",
        .type = t_string,
        .addr.string = temp.read_string,
        .len = sizeof(temp.read_string),
        .nodefault = true,
    },

    [JSON_IDX_write] = 
    {
        .attribute = "write",
        .type = t_object,
        .addr.attrs = write_keys,
        .nodefault = true,
    },

    [JSON_IDX_pinconfig] = 
    {
        .attribute = "GPIO_PIN_CONFIG",
        .type = t_object,
        .addr.attrs = pin_config_keys,
        .nodefault = true,
    },

    [JSON_IDX_pinupdate] = 
    {
        .attribute = "GPIO_PIN_UPDATE",
        .type = t_boolean,
        .addr.boolean = NULL,
        .nodefault = true,
    },

    [JSON_IDX_gpiodevinfo] = 
    {
        .attribute = "GPIO_DEVICE_INFO",
        .type = t_integer,
        .addr.integer = NULL,
        .nodefault = true,
    },

    [JSON_IDX_outpostID] = 
    {
        .attribute = "outpostID",
        .type = t_string,
        .addr.string = temp.outpost_cfg.outpostID,
        .len = sizeof(temp.outpost_cfg.outpostID),
        .nodefault = true,
    },

    [JSON_IDX_pincommand] = 
    {
        .attribute = "GPIO_PIN_CMD",
        .type = t_object,
        .addr.attrs = pin_cmd_keys,
        .nodefault = true,
    },

    [JSON_IDX_status] = 
    {
        .attribute = "status",
        .type = t_integer,
        .addr.integer = &temp.outpost_status,
        .nodefault = false,
        .dflt.integer = 0, /* default is low power mode */
    },

    {NULL},
};


static const struct json_attr write_keys[] =
{
    {
        .attribute = "hb_interval",
        .type = t_integer,
        .addr.uinteger = &heartbeat_interval,
        .dflt.uinteger = INT_MAX,
        .nodefault = false,
    },

    {
        .attribute = "pin_info_interval",
        .type = t_integer,
        .addr.uinteger = &data_interval,
        .dflt.uinteger = INT_MAX,
        .nodefault = false,
    },

    {
        .attribute = "mode",
        .type = t_integer,
        .addr.integer = &device_mode,
        .dflt.integer = INT_MAX,
        .nodefault = false,
    },

    {NULL},
};


static const struct json_attr pin_config_keys[] =
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


static const struct json_attr pin_cmd_keys[] =
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
 * @brief This is called as a callback from a comleted receive
 * 
 * @param param the registered callback param
 */
static void usb_task_receive_callback(cdcUserCbParam_t param);




/**
 * @brief This parses a nul-terminated char array received from the 
 * USB CDC interface using the static JSON parse tree and executes
 * the command using values parsed from the JSON.
 * 
 * @param command the nul-terminated character array (the JSON)
 */
static void parseReceivedCmd(virtualDev *dev, const char *command);


static void parseReceivedCmd(virtualDev *dev, const char *command)
{
    const char *end_ptr = command;
    int key_idx = UNMATCHED_PARENT_JSON_KEY_IDX;
    if(0 == json_read_object(command, base_keys, &end_ptr, &key_idx))
    {   
        switch(key_idx)
        {   
            case UNMATCHED_PARENT_JSON_KEY_IDX:
            {
                /* Do nothing, JSON was not parsed correctly */
            }
            break;
            case JSON_IDX_outpostID:
            {
                comms_printf("Parsed outpostID : >%s< from JSON\n", temp.outpost_cfg.outpostID);

                /* 
                * On boot / power up, 
                * validate outpost ID registration and load syscfg 
                */
                if(DEVICE_STATE_boot == devGetState(dev))
                {
                    if(0 == isOutpostIDnew(temp.outpost_cfg.outpostID))
                    {
                        /* 
                        * TODO:
                        * Load stored system configuration from EEPROM and
                        * apply it to the application state 
                        */
                    }
                    else
                    {
                        /* 
                        * TODO: 
                        * Reset the system configuration in external eeprom
                        * to the default values 
                        */
                    }
                    devSetState(dev, DEVICE_STATE_active);
                }
                else
                {
                    /* We only handle outpost ID command when we're booting */
                }
            }
            break;
            case JSON_IDX_gpiodevinfo:
            {
                comms_printf("Parsed GPIO device info req from JSON%c", '\n');
            }
            break;
            case JSON_IDX_pinupdate:
            {
                comms_printf("Parsed GPIO pin update command!%c", '\n');
            }
            break;
            case JSON_IDX_pinconfig:
            {
                comms_printf(   "Parsed GPIO pin config command from JSON:\n"
                                "type = %d\n"
                                "id = %d\n"
                                "active = %d\n"
                                "label = %d\n"
                                "priority = %d\n"
                                "period = %d\n"
                                "setpoints[0] = %d\n"
                                "setpoints[1] = %d\n"
                                "setpoints[2] = %d\n"
                                "setpoints[3] = %d\n",
                                temp.pin_cfg.type,
                                temp.pin_cfg.id,
                                temp.pin_cfg.active,
                                temp.pin_cfg.label,
                                temp.pin_cfg.priority,
                                temp.pin_cfg.period,
                                temp.pin_cfg.setpoints.battery.redHigh,
                                temp.pin_cfg.setpoints.battery.yellowHigh,
                                temp.pin_cfg.setpoints.battery.yellowLow,
                                temp.pin_cfg.setpoints.battery.redLow);
            }
            break;
            case JSON_IDX_pincommand:
            {
                comms_printf(   "Parsed GPIO PIN COMMAND WITH PARAMS : \n "
                                "trigger : %d\n"
                                "id : %d\n"
                                "type : %d\n",
                                temp.pin_cmd.trigger,
                                temp.pin_cmd.id,
                                temp.pin_cmd.type);
            }
            break;
            case JSON_IDX_read:
            {
                comms_printf("Parsed read command : >%s< from jSON\n", 
                temp.read_string);
            }
            break;
            case JSON_IDX_status:
            {
                comms_printf("Parse status command : >%s< from JSON\n", 
                temp.outpost_status);
            }
            break;
            case JSON_IDX_transmitter:
            {

            }
            break;
            case JSON_IDX_system:
            {
                comms_printf("received system command key : >%s<\n", 
                temp.sys_string);
            }
            break;
            default:
                LL_ASSERT(0);
            break;
        }

        /* wipe the data holder */
        memset(&temp, 0, sizeof(struct temp_fields_struct));
    }
    else
    {
        char msg[] = "{\"error\" : \"json format\"}\r\n";
        comms_tx(msg, sizeof(msg)); 
    }
}


/**
 * @brief This task is responsible for handling serial communications,
 * payload creation, systick, and the JSON request / response structure
 * 
 * @param dev  pointer to virtual device structure
 * @param task pointer to the serial task structure.
 */
void usb_task(virtualDev *dev, task_t *task)
{   
    switch(taskGetState(task))
    {
        case TASK_STATE_ready:
        {   
            switch(taskGetEvent(task))
            {   
                /* First time the task is executing */
                case TASK_EVT_init:
                {
                    struct cdc_user_if usbRxInterface = 
                    {
                        .delim    = RIMOT_USB_STRING_DELIM,
                        .callback = &usb_task_receive_callback,
                        .cbParam  = (cdcUserCbParam_t)(task), 
                    };

                    struct cdc_user_if usbTxInterface = 
                    {
                        .delim    = RIMOT_USB_STRING_DELIM,
                        .callback = NULL,
                        .cbParam  = NULL,
                    };
                    comms_init(&usbRxInterface, &usbTxInterface);
                }
                break;

                /* Task is running in its timeslice */
                case TASK_EVT_run:  
                {   
                    char *cmd = comms_get_command_string();
                    if(NULL != cmd)
                    {
                        switch(taskGetContext(task))
                        {   
                            /* CDC interface received from outpost */
                            case USB_CTX_receive:   
                            {   
                                parseReceivedCmd(dev, cmd);
                            }
                            break;
                            case USB_CTX_transmit:
                            {

                            }
                            break;
                            default:
                                LL_ASSERT(0);
                        }
                    }
                }
                break;

                /* Task is running because a timer cb occurred */
                case TASK_EVT_timer:    
                {
                    switch(taskGetContext(task))
                    {
                        case USB_CTX_receive:
                        {
                            /* 
                             * This should never occur. 
                             * All receives should occur asynchronously
                             */
                            LL_ASSERT(0);
                        }
                        break;
                        case USB_CTX_transmit:
                        {

                        }
                        break;
                        case USB_CTX_none:
                        default:
                            LL_ASSERT(0);
                    }
                }
                break;

                /* Something bad happened. handle faults here */
                case TASK_EVT_err: 
                {

                }
                break;

                /* 
                 * Ideally this should never occur. 
                 * probably an omission error in application logic
                 */
                case TASK_EVT_none: /* FALLTHROUGH TO DEFAULT */
                default:
                    LL_ASSERT(0);
            }
        }
        break;

        break;
        case TASK_STATE_blocked: /* Do nothing. We are waiting on a resource */
        {

        }
        break;
    }
}




/*****************************************************/
/*****            EVENT CALLBACKS                *****/
/*****************************************************/

static void usb_task_receive_callback(cdcUserCbParam_t param)
{   
    if(NULL != param)
    {
        /* Unblock task and set event + context */
        task_t *task = (task_t*)param;
        taskSetState(task, TASK_STATE_ready);
        taskSetEvent(task, TASK_EVT_run);
        taskSetContext(task, USB_CTX_receive);
    }
}
