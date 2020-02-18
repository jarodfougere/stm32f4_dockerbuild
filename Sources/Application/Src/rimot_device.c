#include "rimot_device.h"


static struct rimot_dev_cfg device_config = 
{
    .outpostID          = "00000000",
    .firmware_version   = "0.1.0",
    .hardware_version   = "UNDEFINED",
    .heartbeat_interval = DEFAULT_DEVICE_HEARTBEAT_INTERVAL_MS,
    .data_interval      = DEFAULT_DEVICE_DATA_INTERVAL_MS,
    .mode               = DEFAULT_DEVICE_MODE,
};

static int validate_device_config(struct rimot_dev_cfg *cfg);


/* PUBLIC FUNCTIONS */
int update_device_config(struct rimot_dev_cfg *cfg)
{
    int status = validate_device_config(cfg);
    if(0 == status)
    {

    }

    return status;
}

/* PRIVATE WORKER FUNCTIONS */
static int validate_device_config(struct rimot_dev_cfg *cfg)
{
    int status = 0;





    return status;
}
