#ifndef RIMOT_SYSTEM_CONFIG
#define RIMOT_SYSTEM_CONFIG
#include <stdint.h>

#include "gpio_interface.h"
#include "rf_interface.h"
#include "humidity_interface.h"
#include "temperature_interface.h"


#define SYS_CFG_DFLT_INITIALIZER {            \
    .gpio_cfg =                               \
    {                                         \
        [0] = PIN_CFG_DFLT_INITIALIZER,       \
        [1] = PIN_CFG_DFLT_INITIALIZER,       \
        [2] = PIN_CFG_DFLT_INITIALIZER,       \
        [3] = PIN_CFG_DFLT_INITIALIZER,       \
        [4] = PIN_CFG_DFLT_INITIALIZER,       \
        [5] = PIN_CFG_DFLT_INITIALIZER,       \
        [6] = PIN_CFG_DFLT_INITIALIZER,       \
        [7] = PIN_CFG_DFLT_INITIALIZER,       \
        [8] = PIN_CFG_DFLT_INITIALIZER,       \
        [9] = PIN_CFG_DFLT_INITIALIZER,       \
        [10] = PIN_CFG_DFLT_INITIALIZER,      \
        [11] = PIN_CFG_DFLT_INITIALIZER,      \
        [12] = PIN_CFG_DFLT_INITIALIZER,      \
        [13] = PIN_CFG_DFLT_INITIALIZER,      \
        [14] = PIN_CFG_DFLT_INITIALIZER,      \
        [15] = PIN_CFG_DFLT_INITIALIZER,      \
    },                                        \
    .rf_config =                              \
    {                                         \
        [0] = RF_CFG_DFLT_INITIALIZER,        \
        [1] = RF_CFG_DFLT_INITIALIZER,        \
    }                                         \
}


/* this is the system configuration that is stored in non-volatile memory */
struct system_config
{
    struct pin_cfg    gpio_cfg[NUM_IO_PINS];
    struct rf_config    rf_config[NUM_RF_INPUTS];
};

extern const struct system_config system_config_defaults;

/* overwrite system config (running), and copy it into nvmem */
void reset_sysconfig(struct system_config *cfg);

/* this copies the running system config into nvmem */
void store_sysconfig(const struct system_config *cfg);

/* this copies the nvmem config into the running sysconfig */
void load_sysconfig(struct system_config *cfg);

#endif