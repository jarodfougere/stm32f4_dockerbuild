#ifndef LOWPOWER_RIMOT_DEVICE
#define LOWPOWER_RIMOT_DEVICE
#include <stdint.h>

#include "middleware.h"

#define DEFAULT_DEVICE_HEARTBEAT_INTERVAL_MS 60 //once a minute
#define DEFAULT_DEVICE_DATA_INTERVAL_MS      60 //once a minute
#define DEFAULT_DEVICE_MODE                  0  //0 indicates the device mode

struct rimot_dev_cfg
{   
    char outpostID[16];          //outpost ID assigned to the device
    char firmware_version[16];   //device firmware version
    char hardware_version[16];   //device hardware version
    int  heartbeat_interval;    // device systick interval
    int  data_interval;         // data transmission interval
    int  mode;                  // the device mode
};


int update_device_config(struct rimot_dev_cfg *cfg);




#endif