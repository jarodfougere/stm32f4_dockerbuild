#include "system_config.h"

#include "middleware.h" 

/* this is used at runtime */
const struct system_config system_config_defaults = 
{
    //TODO: POPULATE WITH DEFAULT FIELDS
};






void reset_sysconfig(struct system_config *cfg)

{
    /* copy from default configuration into eeprom */

    
    /* load the system configuration from eeprom into runtime */
    load_sysconfig(cfg);
}

void store_sysconfig(const struct system_config *cfg)

{
    /* copy from device's running system config to non-volatile memory */
}

void load_sysconfig(struct system_config *cfg)
{
    /* copy from non-volatile mem to device's system config */
}