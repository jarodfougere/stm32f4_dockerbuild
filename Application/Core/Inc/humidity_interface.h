#ifndef LOWPOWER_HUMIDITY
#define LOWPOWER_HUMIDITY
#include <stdint.h>

#include "setpoints.h"




typedef struct
{
    uint32_t vals[NUM_SETPOINT_THRESHHOLDS];
}   hum_setpoints_t;



#endif