#include "usb_middleware.h"
#include "rimot_device_config.h"

/* declaration */
static const char *dev_cfg_error_messages[];

static const char *dev_cfg_error_messages[] = 
{   
    "configuration is valid",
    "configured data interval less than min",
    "configured data interval is more than max",
    "configured heartbeat interval is less than min",
    "configured heartbeat interval is more than max",
    "configured device name is too long"
    "configured device mode is invalid",
};



static int validate_device_config(const struct rimot_dev_cfg *cfg);


/* PUBLIC FUNCTIONS */
int update_device_config(   struct rimot_dev_cfg *dest_cfg, 
                            const struct rimot_dev_cfg *src_cfg)
{
    int status = validate_device_config(src_cfg);
    if(0 == status)
    {
        memcpy(dest_cfg, src_cfg, sizeof(struct rimot_dev_cfg));
    }
    else
    {
        usb_printf("%s", dev_cfg_error_messages[status]);
    }
    return status;
}

static int validate_device_config(const struct rimot_dev_cfg *cfg)
{
    //yeah there are some magic numbers in here but as long as they're different its ok.

    if(cfg->data_interval < MIN_DEVICE_DATA_INTERVAL_S)
    {
        return 1;
    }

    if(cfg->data_interval > MAX_DEVICE_DATA_INTERVAL_S)
    {
        return 2;
    }

    if(cfg->heartbeat_interval < MIN_DEVICE_HEARTBEAT_INTERVAL_S)
    {
        return 3;
    }
    
    if(cfg->heartbeat_interval > MAX_DEVICE_HEARTBEAT_INTERVAL_S)
    {
        return 4;
    }

    if(strlen(cfg->device_name) > RIMOT_DEV_NAME_LEN)
    {
        return 5;
    }

    switch(cfg->mode)
    {
        case DEVICE_MODE_lowpower:
        case DEVICE_MODE_diagnostic:
        case DEVICE_MODE_standard:
            break;
        
        //invalid device mode
        default:
            return 6;
            break;
    }
    return 0;
}