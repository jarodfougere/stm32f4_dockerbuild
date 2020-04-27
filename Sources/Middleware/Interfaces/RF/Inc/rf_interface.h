#ifndef RIMOT_RF_INTERFACES
#define RIMOT_RF_INTERFACES
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>
#include <float.h>
#include <limits.h>

#include "rf_status.h"



typedef float rf_powerVal;

typedef struct rf_config_struct rfConfig_t;


void rfIF_init(void);

rfConfig_t* rfCfgInit(void);




#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RF_INTERFACE */

