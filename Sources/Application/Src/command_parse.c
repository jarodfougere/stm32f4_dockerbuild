#include <stdio.h>
#include <string.h>

#include "command_parse.h"
#include "middleware.h"
#include "debug.h"
#include "payloads.h"

#define SYSTEM_KEY_MAX_LEN 50

/* expected json parse tree. laid-out in command_structure.c */
static const struct json_attr_t base_attrs[];
static const struct json_attr_t write_attrs[];
static const struct json_attr_t pin_config_attrs[];
static const struct json_attr_t pin_cmd_attrs[];

/* contains data parsed from the incoming command */
struct temp_fields_struct
{
    struct pinConfig         pin_cfg;
    struct pinCommand        pin_cmd;
    struct rimot_dev_cfg     device_cfg;
    struct outpost_config    outpost_cfg;
    char                     cmd_string[20];
};
struct temp_fields_struct temp;


static const struct json_attr_t base_attrs[] = 
{   
    {
        "system", 
        t_string, 
        .addr.string = temp.cmd_string,
        .len = SYSTEM_KEY_MAX_LEN,
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
        t_boolean,
        .addr.boolean = NULL,
    },

    {
        "GPIO_DEVICE_INFO",
        t_integer,
        .addr.integer = NULL,
    },

    {
        "outpostID",
        t_string,
        .addr.string = temp.outpost_cfg.outpostID,
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
        .addr.integer = &temp.device_cfg.heartbeat_interval,
        .dflt.integer = UNUSED_RIMOT_DEV_CONFIG_FIELD_VAL,
    },

    {
        "pin_info_interval",
        t_integer,
        .addr.integer = &temp.device_cfg.data_interval,
        .dflt.integer = UNUSED_RIMOT_DEV_CONFIG_FIELD_VAL,
    },

    {
        "mode",
        t_integer,
        .addr.integer = &temp.device_cfg.mode,
        .dflt.integer = UNUSED_RIMOT_DEV_CONFIG_FIELD_VAL,
    },

    {NULL},
};

static const struct json_attr_t pin_config_attrs[] = 
{
    {
        "id", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.id
    },

    {
        "type", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.type
    },

    {
        "active", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.active
    },

    {
        "label", 
        t_integer,  
        .addr.integer = &temp.pin_cfg.label
    },

    {
        "priority", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.priority
    },

    {
        "debounce", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.period
    },

    {
        "redHigh",  
        t_real,    
        .addr.real = &temp.pin_cfg.setpoints.numerics.redHigh
    },

    {
        "yellowHigh", 
        t_real, 
        .addr.real = &temp.pin_cfg.setpoints.numerics.yellowHigh
    },

    {
        "yellowLow", 
        t_real, 
        .addr.real = &temp.pin_cfg.setpoints.numerics.yellowLow
    },
    {
        "redLow", 
        t_real, 
        .addr.real = &temp.pin_cfg.setpoints.numerics.redLow
    },

    {
        "state", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.digitals.default_state
    },

    {
        "trigger", 
        t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.digitals.trigger_state
    },

    {NULL}
};


static const struct json_attr_t pin_cmd_attrs[] = 
{
    {
        "id", 
        t_integer, 
        .addr.integer = &temp.pin_cmd.id
    },

    {
        "type", 
        t_integer, 
        .addr.integer = &temp.pin_cmd.type
    },

    {
        "trigger", 
        t_integer, 
        .addr.integer = &temp.pin_cmd.trigger
    },

    {NULL}
};

/* execution wrappers for interface/task provided function calls */
static void do_system(struct rimot_device *dev);
static void do_write(struct rimot_device *dev);
static void do_pin_config(struct rimot_device *dev);
static void do_pin_update(struct rimot_device *dev);
static void do_device_info(struct rimot_device *dev);
static void do_outpost_id(struct rimot_device *dev);
static void do_pin_command(struct rimot_device *dev);

/* function pointer array based on index of top-level matched key */
void (*key_funcs[])(struct rimot_device*) = 
{
    do_system,
    do_write,
    do_pin_config,
    do_pin_update,
    do_device_info,
    do_outpost_id,
    do_pin_command,
};

static void do_system(struct rimot_device *dev)
{   
    doDoSysCommand(temp.cmd_string);
}


static void do_write(struct rimot_device *dev)
{
    transmit_serial("executing write command for the following device config:\n"
    "heartbeat_interval = %d\n"
    "pin_info_interval = %d\n"
    "mode = %d\n"
    "name = %s\n",
    temp.device_cfg.heartbeat_interval,
    temp.device_cfg.data_interval,
    temp.device_cfg.mode,
    temp.device_cfg.device_name
    );
}

static void do_pin_config(struct rimot_device *dev)
{
    transmit_serial(
        "EXUCUTING PIN CONFIG WITH THE FOLLOWING PAYLOAD:\n"
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
        temp.pin_cfg.id,
        temp.pin_cfg.type,
        temp.pin_cfg.active,
        temp.pin_cfg.label,
        temp.pin_cfg.priority,
        temp.pin_cfg.period,
        temp.pin_cfg.setpoints.numerics.redHigh,
        temp.pin_cfg.setpoints.numerics.yellowHigh,
        temp.pin_cfg.setpoints.numerics.yellowLow,
        temp.pin_cfg.setpoints.numerics.yellowLow,
        temp.pin_cfg.setpoints.digitals.default_state,
        temp.pin_cfg.setpoints.digitals.trigger_state
        );
}

static void do_pin_update(struct rimot_device *dev)
{
    transmit_serial("EXECUTING GPIO PIN UPDATE\n");
}

static void do_device_info(struct rimot_device *dev)
{
    transmit_serial("EXECUTING GPIO DEVICE INFO\n");
}

static void do_outpost_id(struct rimot_device *dev)
{
    transmit_serial("executing outpostID command with payload:\n"
    "outpostID = %s\n",
    temp.outpost_cfg.outpostID);
}

static void do_pin_command(struct rimot_device *dev)
{
    transmit_serial("exeucting gpio pin command with following payload:\n"
    "id : %d\n"
    "type: %d\n"
    "trigger: %d\n",
    temp.pin_cmd.id,
    temp.pin_cmd.type,
    temp.pin_cmd.trigger);
}


int parse_command(const char * command, struct rimot_device *dev)
{   
    transmit_serial("parsing command >%s<\n", command);
#ifdef MJSON_DEBUG_ENABLE
    json_enable_debug(2, NULL);
#endif

    const char *end_ptr = command;
    int32_t key_idx = UNMATCHED_TOPLEVEL_KEY_IDX;
    int status = json_read_object(command, base_attrs, &end_ptr, &key_idx);

    transmit_serial("index of first key in the JSON is %d\n", key_idx);
    if (status != 0)
    {   
        transmit_serial("ERROR:  ");
        transmit_serial("%s", json_error_string(status));
    }
    else
    {   
        /* execute based on the key matched in top level json */
        key_funcs[key_idx](dev);

        /* wipe the data holder */
        memset(&temp, 0, sizeof(struct temp_fields_struct));

        transmit_serial("\n");
    }
    
    return status;
}





