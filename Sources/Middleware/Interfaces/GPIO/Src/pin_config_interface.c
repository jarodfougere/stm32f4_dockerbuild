#include <stdlib.h>
#include <stdint.h>

#include "pin_config_interface.h"
#include "rimot_LL_debug.h"


void pinCfg_resetToDefault( pinCfgCore_t *cfg, 
                            GPIO_PIN_ID_t id, 
                            GPIO_PINTYPE_t type)
{
    cfg->id       = id;
    cfg->type     = type;
    cfg->active   = GPIO_PIN_REGISTERED_inactive;
    cfg->label    = GPIO_PIN_LABEL_unused;
    cfg->priority = GPIO_PIN_PRIORITY_unused;
    cfg->period   = PINCONFIG_PERIOD_FIELD_RESET_VAL;
}
