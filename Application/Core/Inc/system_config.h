#ifndef LOWPOWER_SYSTEM_CONFIG
#define LOWPOWER_SYSTEM_CONFIG
#include <stdint.h>
#include <time.h>

#include "gpio_interface.h"
#include "rf_interface.h"
#include "humidity_interface.h"
#include "temperature_interface.h"



/* this is the system configuration that is stored in non-volatile memory */
typedef struct
{
    int8_t          outpost_id[8];       /* outpost ID              */
    struct tm       timestamp;           /* nvmem write timestamp   */
    pin_config_t    gpio_cfg[ NUM_BATTERIES + NUM_DIGITAL_INPUTS + NUM_RELAYS];
    rf_setpoints_t  rf_setpoints[NUM_RF_INPUTS];
    hum_setpoints_t hum_setpoints;
    temperature_setpt_t temp_setpoints;
}   system_config_t;













#endif