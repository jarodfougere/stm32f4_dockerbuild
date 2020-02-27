#ifndef RIMOT_DEVICE_CONFIG
#define RIMOT_DEVICE_CONFIG
#include <stdint.h>

//BOUNDARIES FOR HOW FREQUENTLY THE DEVICE SENDS SYSTICK
#define DEFAULT_DEVICE_HEARTBEAT_INTERVAL_S 60  //once a minute
#define MAX_DEVICE_HEARTBEAT_INTERVAL_S     300 //once every 5 minutes
#define MIN_DEVICE_HEARTBEAT_INTERVAL_S     30  //once every 30 seconds

//BOUNDARIES FOR HOW FREQUENTLY THE DEVICE SENDS ITS DATA PAYLOAD
#define DEFAULT_DEVICE_DATA_INTERVAL_S      60  //once a minute
#define MAX_DEVICE_DATA_INTERVAL_S          150 //once every 2.5minutes
#define MIN_DEVICE_DATA_INTERVAL_S          10  //once every 10 seconds


#define UNNAMED_RIMOT_DEVICE "UNNAMED RIMOT DEVICE"
#define RIMOT_DEV_NAME_LEN       50

typedef enum
{
    DEVICE_MODE_standard,
    DEVICE_MODE_lowpower,
    DEVICE_MODE_diagnostic,
}   DEVICE_MODE_t;
#define DEFAULT_DEVICE_MODE DEVICE_MODE_standard


#define RIMOT_DEV_CFG_DFLT_INITIALIZER {                        \
    .device_name = UNNAMED_RIMOT_DEVICE,                        \
    .heartbeat_interval = DEFAULT_DEVICE_HEARTBEAT_INTERVAL_S,  \
    .data_interval = DEFAULT_DEVICE_DATA_INTERVAL_S,            \
    .mode = DEFAULT_DEVICE_MODE,                                \
}

struct rimot_dev_cfg
{   
    char      device_name[RIMOT_DEV_NAME_LEN];    /* name assigned to this device */
    int32_t       heartbeat_interval;         /* device systick interval      */
    int32_t       data_interval;              /* data transmission interval   */
    int32_t       mode;                       /* the device's operation mode  */
};

#endif