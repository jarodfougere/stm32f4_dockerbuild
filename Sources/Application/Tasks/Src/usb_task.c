/**
 * @file serial_task.c
 * @author Carl Mattatall
 * @brief This module is responsible for serial communications, JSON parsing
 * JSON creation, and usb data transmissions for the low power sensor card
 * firmware application.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "usb_task.h"
#include "task_core.h"
#include "middleware_core.h"
#include "payloads.h"
#include "gpio_interface.h"
#include "comms_interface.h"
#include "system_interface.h"
#include "mjson.h"

#define SYSTEM_KEY_MAX_LEN 50

/* Parse tree of expected payload. Statically allocated (laid out beforehand) */
static const struct json_attr_t base_attrs[];
static const struct json_attr_t write_attrs[];
static const struct json_attr_t pin_config_attrs[];
static const struct json_attr_t pin_cmd_attrs[];

/* Contains data parsed from receive JSONS */
struct temp_fields_struct
{
    struct pin_cfg pin_cfg;
    struct pin_command pin_cmd;
    struct rimot_dev_cfg device_cfg;
    struct outpost_config outpost_cfg;
    char sys_string[SYSTEM_KEY_MAX_LEN];
    int outpost_status;
}   temp;


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

    {
        .attribute = "Hello",
        .type = t_integer,
        .addr.integer = NULL,
        .nodefault = true,
    },

    {
        .attribute = "Done",
        .type = t_integer,
        .addr.integer = NULL,
        .nodefault = true,
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


static void doCDC_command(const char *command)
{
    const char *end_ptr = command;
    int32_t key_idx = UNMATCHED_PARENT_JSON_KEY_IDX;
    if(0 == json_read_object(command, base_attrs, &end_ptr, &key_idx))
    {
        /* execute based on the key matched in top level json */
        comms_printf( "###\nKEY MATCHED IN JSON >%s< is %d\n###\n", key_idx);

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
void serial_task(struct rimot_device *dev, struct task *task)
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
            case USB_CTX_motion:    /* motion task signaled usb task */
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
            {
    #ifndef NDEBUG
                while(1)
                {
                    /*
                    * Hang forever.
                    * Task context should only be NONE when task is blocked.
                    */
                    
                }
    #endif /* DEBUG BUILD */
            }
            break;
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
        struct task *task = (struct task*)param;
        task->state = TASK_STATE_ready;

        /* Payload received from the CDC interface */
        task->exec.evt = TASK_EVT_rx;
        task->exec.ctx = USB_CTX_cdc; 
    }
}


static void usb_task_transmit_callback(cdcUserCbParam_t param)
{   
    if(NULL != param)
    {
        struct task *task = (struct task*)param;
        task->state = TASK_STATE_ready;

        /* Payload transmitted from CDC interface */
        task->exec.evt = TASK_EVT_tx;
        task->exec.ctx = USB_CTX_cdc; 
    }
}

