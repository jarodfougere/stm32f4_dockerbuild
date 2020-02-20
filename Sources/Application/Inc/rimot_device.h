#ifndef RIMOT_RIMOT_DEVICE
#define RIMOT_RIMOT_DEVICE
#include <stdint.h>

#include "middleware.h"
#include "rimot_device_config.h"
#include "system_config.h"
#include "outpost_config.h"

//USER CONFIGURES THESE BASED ON THE RELEASE
#define FIRMWARE_VERSION_STRING             "0.1.0"
#define HARDWARE_VERSION_STRING             "1.0.0"
#define DEVICE_UNIQUE_ID_STRING             "CARL HASNT UPDATED UID MACRO IN rimot_device.h yet"


#define RIMOT_DEVICE_DEFAULTS {                                             \
        .outpost_config =                                                   \
        {                                                                   \
            .outpostID = UNASSIGNED_OUTPOST_ID                              \
        },                                                                  \
                                                                            \
        .device_config =                                                    \
        {                                                                   \
            .device_name = UNNAMED_RIMOT_DEVICE,                            \
            .heartbeat_interval = DEFAULT_DEVICE_HEARTBEAT_INTERVAL_S,      \
            .data_interval = DEFAULT_DEVICE_DATA_INTERVAL_S,                \
            .mode = DEVICE_MODE_standard,                                   \
        },                                                                  \
                                                                            \
        .system_config =                                                    \
        {                                                                   \
                                                                            \
        },                                                                  \
    }                                                                       \


struct rimot_device 
{
    struct rimot_dev_cfg  device_config;   /* device configuration         */
    struct system_config  system_config;   /* interface configurations     */
    struct outpost_config outpost_config;  /* config of assigned outpost   */
};


int update_device_config(   struct rimot_dev_cfg *dest_cfg, 
                            const struct rimot_dev_cfg *src_cfg);

#endif