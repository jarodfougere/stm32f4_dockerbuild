#include "system_config.h"

/* this is used at runtime */
system_config_t system_config_heap; 

const system_config_t system_config_defaults =
{
    .outpost_id = "0000000",
    .timestamp = 
    {   
        .tm_sec   =  0,
        .tm_min   =  0,
        .tm_hour  =  0,
        .tm_mday  =  0,
        .tm_year  =  0,
        .tm_wday  =  0,
        .tm_yday  =  0,
        .tm_isdst =  0,
    },

    /* gpio config */
    .gpio_cfg[0] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[1] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[2] =
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[3] =
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[4] =
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[5] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[6] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[7] =
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[8] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[9] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[10] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[11] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[12] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[13] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[14] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .gpio_cfg[15] = 
    {
        .active       = 0, 
        .label        = 0, 
        .priority     = 0, 
        .reserved     = 0, 
        .interface[0] = 0, 
        .interface[1] = 0, 
        .interface[2] = 0, 
        .interface[3] = 0
    },
    .rf_setpoints[0] = 
    {
        0.0,
        0.0,
        0.0,
        0.0,
    },
    .rf_setpoints[1] =
    {
        0.0,
        0.0,
        0.0,
        0.0
    },
    .hum_setpoints = 
    {
        0,
        0,
        0,
        0,
    },
    .temp_setpoints = 
    {
        0,
        0,
        0,
        0,
    }
};


void reset_sysconfig(void)
{


}

void store_sysconfig(void)
{


}

void load_sysconfig(void)
{

}