/**
 * @file battery_interface.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides an interface for the battery
 * monitoring pins on the integrated sensor module by bundling
 * low level drivers
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include <stdlib.h>
#include <stdint.h>

#include "pin_config_interface.h"
#include "battery_interface.h"
#include "rimot_LL_debug.h"


struct gpio_bat_config
{
    pinCfgCore_t pin;
    batterySetpoints  setpoints;
};



batConfig_t* newBatteryConfig(GPIO_PIN_ID_t id)
{
    batConfig_t *cfg = (batConfig_t*)malloc(sizeof(batConfig_t));
    LL_ASSERT(NULL != cfg);
    LL_ASSERT(id > 0);
    LL_ASSERT(id <= NUM_BATTERY_PINS);
    pinCfg_resetToDefault(&cfg->pin, id, GPIO_PINTYPE_analog_input);
    memset((void*)&cfg->setpoints, 
            BATTERY_SETPOINT_UNSET_VAL, 
            sizeof(cfg->setpoints));
    return cfg;
}



batterySetpoints* batGetSetpoints(const batConfig_t* bat)
{
    return (batterySetpoints*)&bat->setpoints;
}


pinCfgCore_t* batGetPinConfig(const batConfig_t* bat)
{
    return (pinCfgCore_t*)&bat->pin;
}


int batValidateSetpoints(const batterySetpoints *setpoints)
{
    if(setpoints->redHigh <= setpoints->yellowHigh)
    {
        return 1;
    }

    if(setpoints->yellowHigh <= setpoints->yellowLow)
    {
        return 1;
    }

    if(setpoints->yellowLow <= setpoints->redLow)
    {
        return 1;
    }

    if(setpoints->redLow <= 0)
    {
        return 1;
    }

    return 0;
}





