#ifndef RIMOT_BATTERY_INTERFACE
#define RIMOT_BATTERY_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "pin_config_interface.h"

#define NUM_BATTERY_PINS 4

#define BATTERY_SETPOINT_UNSET_VAL 0


typedef struct 
{
    /* units in millivolts */
    uint32_t redHigh;
    uint32_t yellowHigh;
    uint32_t yellowLow;
    uint32_t redLow;
}   batterySetpoints;


typedef struct gpio_bat_config batConfig_t;
batConfig_t* newBatteryConfig(GPIO_PIN_ID_t id);
batterySetpoints* batGetSetpoints(const batConfig_t* bat);
pinCfgCore_t* batGetPinConfig(const batConfig_t* bat);
int batValidateSetpoints(const batterySetpoints *setpoints);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_BATTERY_INTERFACE */