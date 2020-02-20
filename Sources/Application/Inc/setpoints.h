#ifndef RIMOT_SETPOINTS
#define RIMOT_SETPOINTS
#include <stdint.h>


#define NUM_SETPOINT_THRESHHOLDS 4

/* 
interface array indexing for setpoints
used by :
    - gpio analog inputs
    - rf inputs
    - temperature
    - humidity
*/
#define red_high_index      0
#define yellow_high_index   1
#define yellow_low_index    2
#define red_low_index       3

typedef float rf_setpt_t[NUM_SETPOINT_THRESHHOLDS];
typedef uint32_t hum_setpt_t[NUM_SETPOINT_THRESHHOLDS];
typedef uint32_t temperature_setpt_t[NUM_SETPOINT_THRESHHOLDS];

#endif