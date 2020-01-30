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


extern system_config_t system_config_heap;


/* overwrite system config (running), and copy it into nvmem */
void reset_sysconfig(void);

/* this copies the running system config into nvmem */
void store_sysconfig(void);

/* this copies the nvmem config into the running sysconfig */
void load_sysconfig(void);



#endif