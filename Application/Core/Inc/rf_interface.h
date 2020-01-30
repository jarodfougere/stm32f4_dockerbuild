#ifndef LOWPOWER_RF_INTERFACES
#define LOWPOWER_RF_INTERFACES
#include <stdint.h>

#include "setpoints.h"

/* an "rf input" is a PAIR of the N type connectors going to a coupler */
#define NUM_RF_INPUTS 2
#define TRANSMITTER_ID_STRING_LENGTH 50


typedef struct
{
    float forward_power;
    float reflected_power;
    float vswr;                 /* technically vswr must be computed */
}   rf_measurement_t;


typedef struct
{   
    int8_t transmitter_id[TRANSMITTER_ID_STRING_LENGTH + 1];
}   rf_config_t;



#endif