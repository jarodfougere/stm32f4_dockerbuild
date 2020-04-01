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
#include "task_core.h"
#include "middleware_core.h"
#include "gpio_interface.h"
#include "comms_interface.h"
#include "system_interface.h"
#include "mjson.h"


static const struct json_attr base_keys[];
static const struct json_attr write_keys[];
static const struct json_attr pin_config_keys[];
static const struct json_attr pin_cmd_keys[];


/* Contains data parsed from receive JSONS */
struct temp_fields_struct
{
    struct pin_cfg pin_cfg;
    struct pin_command pin_cmd;
    struct rimot_dev_cfg device_cfg;
    struct outpost_config outpost_cfg;
    char sys_string[JSON_VAL_MAXLEN];
    char read_string[JSON_VAL_MAXLEN];
    int outpost_status;
}   temp;


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
 * @brief This is called as a callback from a completed transmit
 * 
 * @param param the registered callback param
 */
static void usb_task_transmit_callback(cdcUserCbParam_t param);


/**
 * @brief This is called as a callback from a comleted receive
 * 
 * @param param the registered callback param
 */
static void usb_task_receive_callback(cdcUserCbParam_t param);


/**
 * @brief This parses an incoming JSON to a command execution structure
 * and executes the command based on the values parsed into the command
 * structure.
 * 
 * @param command the input command string (must be nul-terminted)
 */
static void doReceiveEvent(struct rimot_device *dev, int rx_ctx);


/**
 * @brief This parses a nul-terminated char array received from the 
 * USB CDC interface using the static JSON parse tree and executes
 * the command using values parsed from the JSON.
 * 
 * @param command the nul-terminated character array (the JSON)
 */
static void doCDC_command(const char *command);


static void doCDC_command(const char *command)
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
                comms_printf("Parsed GPIO pin config command from JSON:\n"
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
                comms_printf("Parsed read command : >%s< from jSON\n", temp.read_string);
            }
            break;
            case JSON_IDX_status:
            {
                comms_printf("Parse status command : >%s< from JSON\n", temp.outpost_status);
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
#if !defined(NDEBUG)
            {
                while(1)
                {
                    /* 
                     * Programmer may have forgotten to put something logic in 
                     * switchcase or key_idx returned as garbage
                     * (indeterminate) 
                     * 
                     * Programmer to find and fix issue with firmware logic.
                     */
                }
            }
#else
            break; /* just don't do anything in release build */
#endif /* DEBUG BUILD */
            
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
void usb_task(struct rimot_device *dev, struct task *task)
{   
    switch(task->state)
    {
        case TASK_STATE_ready:
        {   
            switch(task->exec.evt)
            {   
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
                        .callback = &usb_task_transmit_callback,
                        .cbParam  = (cdcUserCbParam_t)(task),
                    };
                    comms_init(&usbRxInterface, &usbTxInterface);
                }
                break;
                case TASK_EVT_rx: /* usb task was signaled by another task */
                {   
                    doReceiveEvent(dev, task->exec.ctx);
                }
                break;
                case TASK_EVT_tx: /* usb task will signal another task */
                {
                    

                }
                break;
                case TASK_EVT_err: /* handle faults here */
                {

                }
                break;
                case TASK_EVT_none: /* FALLTHROUGH TO DEFAULT */
                default:
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* 
                         * 2 cases:
                         * 
                         *  - Programmer forgot to add an event to switch,
                         *    thus triggering the default case.
                         *
                         *  - Task is being signaled but its evt not being 
                         *    updated by the signalling task. 
                         * 
                         * Both scenarios mean a bug in software. Hang forever 
                         * in debug build.
                         */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }

            /* After execution, block and clear exec event and context */
            task_block_self(task);  
        }
        break;
        case TASK_STATE_asleep:
        {
            /* sleep until ticks expire or task is woken up */
            task_sleep(task, 0); 
        }
        break;
        case TASK_STATE_blocked: /* Do nothing. We are waiting on a resource */
        {

        }
        break;
    }
}


static void doReceiveEvent(struct rimot_device *dev, int rx_ctx)
{   
    /* retrieve the payload */
    char *cmd = comms_get_command_string(); 
    if(NULL != cmd)
    {   
        /* handle the received data based on the receive context */
        switch(rx_ctx)
        {   
            case USB_CTX_cdc:   /* CDC interface received from outpost */
            {   
                doCDC_command(cmd);
            }
            break;
            case USB_CTX_dfu:   /* DFU interface received from outpost */
            {

            }
            break;
            case USB_CTX_ins:   /* digital input task signaled usb task */
            {

            }
            break;
            case USB_CTX_outs:  /* relay task signaled usb task */
            {

            }
            break;
            case USB_CTX_bats:  /* battery task signaled usb task */
            {

            }
            break;
            case USB_CTX_rf:    /* rf task signaled usb task */
            {

            }
            break;
            case USB_CTX_hum:   /* humidity task signaled usb task */
            {

            }
            break;
            case USB_CTX_temp:  /* temperature task signaled usb task */
            {

            }
            break;
            case USB_CTX_motion: /* motion task signaled usb task */
            {

            }
            break;
            case USB_CTX_sys:   /* system task signaled usb task */
            {

            }
            break;
            case USB_CTX_stats: /* analytics task signaled usb task */
            {

            }
            break;
            case USB_CTX_timing: /* timing task signaled usb task */
            {

            }
            break;
            case USB_CTX_none: /* FALL THROUGH TO DEFAULT */
            default: 
#if !defined(NDEBUG)
            {
                while(1)
                {
                    /*
                    * Task context should only be NONE when task is blocked.
                    * 
                    * Alternatively, programmer forgot to add context case
                    * to the switch.
                    * 
                    * Hang here. Programmer to find issue in debug build.
                    */
                }
            }
#else
            break;
#endif /* DEBUG BUILD */
        }
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
        struct task *task = (struct task*)param;
        task->state = TASK_STATE_ready;
        task->exec.evt = TASK_EVT_rx;
        task->exec.ctx = USB_CTX_cdc; 
    }
}


static void usb_task_transmit_callback(cdcUserCbParam_t param)
{   
    if(NULL != param)
    {   
        /* Unblock task and set event + context */
        struct task *task = (struct task*)param;
        task->state = TASK_STATE_ready;
        task->exec.evt = TASK_EVT_tx;
        task->exec.ctx = USB_CTX_cdc; 
    }
}

