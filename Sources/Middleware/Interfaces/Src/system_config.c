#include <string.h>
#include "system_config.h"


/* this is used at runtime */
const struct system_config system_config_defaults = SYS_CFG_DFLT_INITIALIZER;


void reset_sysconfig(struct system_config *cfg)
{
    /* reset running configuration */
    memcpy(cfg, &system_config_defaults, sizeof(system_config_defaults));
    
    /* store the running configuration into non-volatile memory */
    store_sysconfig(cfg);
}


void store_sysconfig(const struct system_config *cfg)

{
    /* copy from device's running system config to non-volatile memory */
}

void load_sysconfig(struct system_config *cfg)
{
    /* copy from non-volatile mem to device's system config */
}




