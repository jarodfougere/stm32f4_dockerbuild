#ifndef LOWPOWER_RF_INTERFACES
#define LOWPOWER_RF_INTERFACES
#include <stdint.h>

#include "setpoints.h"

/* an "rf input" is a PAIR of the N type connectors going to a coupler */
#define NUM_RF_INPUTS 2



typedef struct
{
    float forward_power;
    float reflected_power;
    float vswr;                 /* technically vswr must be computed */
}   rf_measurement_t;


typedef struct
{
    rf_setpt_t fowrward_power;
    rf_setpt_t reflected_power;
    rf_setpt_t vswr;
}   rf_setpoints_t;




#endif