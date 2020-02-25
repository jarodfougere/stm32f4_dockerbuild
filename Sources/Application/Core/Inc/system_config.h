#ifndef RIMOT_SYSTEM_CONFIG
#define RIMOT_SYSTEM_CONFIG
#include <stdint.h>

#include "gpio_interface.h"
#include "rf_interface.h"
#include "humidity_interface.h"
#include "temperature_interface.h"

/* this is the system configuration that is stored in non-volatile memory */
struct system_config
{
    struct pinConfig    gpio_cfg[NUM_IO_PINS];
    rf_config_t         rf_config[NUM_RF_INPUTS];
};

extern const struct system_config system_config_defaults;

/* overwrite system config (running), and copy it into nvmem */
void reset_sysconfig(struct system_config *cfg);

/* this copies the running system config into nvmem */
void store_sysconfig(const struct system_config *cfg);

/* this copies the nvmem config into the running sysconfig */
void load_sysconfig(struct system_config *cfg);


#endif