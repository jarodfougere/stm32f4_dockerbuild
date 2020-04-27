#ifndef RIMOT_LOW_POWER_SENSORCARD_SYSTEM_INTERFACE
#define RIMOT_LOW_POWER_SENSORCARD_SYSTEM_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* C LINKAGE */
#include <stdint.h>

#include "gpio_interface.h"
#include "rf_interface.h"
#include "humidity_interface.h"
#include "temperature_interface.h"

typedef struct system_config sysConfig_t;

extern const sysConfig_t system_config_defaults;


/**
 * @fn doesOutpostIDmatch
 * @brief Compare an outpost ID with the outpost ID stored in external eeprom.
 * @param char* id : the nul-terminated character array 
 * containing the outpost ID
 * @return int 0 if the IDs match, else 1. 
 */
int doesOutpostIDmatch(const char *id);

#ifdef __cplusplus
}
#endif /* C LINKAGE */
#endif /* RIMOT_LOW_POWER_SENSORCARD_SYSTEM_INTERFACE */


