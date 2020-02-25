#include "command_parse.h"
#include "debug.h"
#include "payloads.h"

#include "gpio_interface.h"
#include "system_config.h"

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
    char                     cmd_string[SYSTEM_KEY_MAX_LEN];
};
static struct temp_fields_struct temp;


static const struct json_attr_t base_attrs[] = 
{   
    {
        .attribute = "system", 
        .type = t_string, 
        .addr.string = temp.cmd_string,
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
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,
        .nodefault = false,
    },

    {
        .attribute = "type", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.type,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,
        .nodefault = false,
    },

    {
        .attribute = "active", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.active,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,
        .nodefault = false,
    },

    {
        .attribute = "label", 
        .type = t_integer,  
        .addr.integer = &temp.pin_cfg.label,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,
        .nodefault = false,
    },

    {
        .attribute = "priority", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.priority,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,
        .nodefault = false,
    },

    {
        .attribute = "debounce", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.period,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,  
        .nodefault = false,
    },

    {
        .attribute = "redHigh",  
        .type = t_integer,    
        .addr.integer = &temp.pin_cfg.setpoints.battery.redHigh,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,  
        .nodefault = false,
    },

    {
        .attribute = "yellowHigh", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.battery.yellowHigh,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,  
        .nodefault = false,
    },

    {
        .attribute = "yellowLow", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.battery.yellowLow,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,    
        .nodefault = false,
    },

    {
        .attribute = "redLow", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.battery.redLow,
        .dflt.integer = GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL,  
        .nodefault = false,
    },

    {
        .attribute = "state", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.relay.default_state,
        .nodefault = true,  //THIS VALUE IS OVERLAYED WITH BATTERY SP. 
    },

    {
        .attribute = "trigger", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cfg.setpoints.input.trigger,
        .nodefault = true,  //THIS VALUE IS OVERLAYED WITH BATTERY SP. 
    },

    {NULL}
};


static const struct json_attr_t pin_cmd_attrs[] = 
{
    {
        .attribute = "id", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cmd.id
    },

    {
        .attribute = "type", 
        .type = t_integer, 
        .addr.integer = &temp.pin_cmd.type
    },

    {
        .attribute = "trigger", 
        .type = t_integer, 
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
    transmit_serial("executing system command with command string = >%s<\n", temp.cmd_string);
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
    "redHigh = %d\n"
    "yellowHigh = %d\n"
    "yellowLow = %d\n"
    "redLow = %d\n"
    "default_state = %d\n"
    "trigger = %d\n",
    temp.pin_cfg.id,
    temp.pin_cfg.type,
    temp.pin_cfg.active,
    temp.pin_cfg.label,
    temp.pin_cfg.priority,
    temp.pin_cfg.period,
    temp.pin_cfg.setpoints.battery.redHigh,
    temp.pin_cfg.setpoints.battery.yellowHigh,
    temp.pin_cfg.setpoints.battery.yellowLow,
    temp.pin_cfg.setpoints.battery.yellowLow,
    temp.pin_cfg.setpoints.relay.default_state,
    temp.pin_cfg.setpoints.input.trigger
    );
}

static void do_pin_update(struct rimot_device *dev)
{
    update_pin_config(dev->system_config.gpio_cfg, &temp.pin_cfg);
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
    execute_pin_command(&temp.pin_cmd);
}


int32_t parse_command(const char * command, struct rimot_device *dev)
{   
    transmit_serial("parsing command >%s<\n", command);
#ifdef MJSON_DEBUG_ENABLE
    json_enable_debug(2, NULL);
#endif

    const char *end_ptr = command;
    int32_t key_idx = UNMATCHED_TOPLEVEL_KEY_IDX;
    int32_t status = json_read_object(command, base_attrs, &end_ptr, &key_idx);

    if (status != 0)
    {   
        transmit_serial("ERROR:  ");
        transmit_serial("%s", json_error_string(status));
    }
    else
    {   
        /* execute based on the key matched in top level json */

        transmit_serial("\n");

        key_funcs[key_idx](dev);

        /* wipe the data holder */
        memset(&temp, 0, sizeof(struct temp_fields_struct));

        transmit_serial("\n");
    }
    
    return status;
}
