#ifndef RIMOT_RF_INTERFACES
#define RIMOT_RF_INTERFACES
#include <stdint.h>
#include <float.h>


/* an "rf input" is a PAIR of the N type connectors going to a coupler */
#define NUM_RF_INPUTS 2
#define UNASSIGNED_TRANSMITTER_ID "0000000000000000000000"
#define UNUSED_SETPOINT_VALUE 0.0

#define MIN_VSWR_POSSIBLE 0
#define MAX_VSWR FLT_MAX

#define RF_CFG_DFLT_INITIALIZER {                   \
    .transmitter_id = UNASSIGNED_TRANSMITTER_ID,    \
    .setpoints =                                    \
    {                                               \
        .forward_pwr =                              \
        {                                           \
            .redHigh = UNUSED_SETPOINT_VALUE,       \
            .yellowHigh = UNUSED_SETPOINT_VALUE,    \
        },                                          \
                                                    \
        .reflected_pwr =                            \
        {                                           \
            .redHigh = UNUSED_SETPOINT_VALUE,       \
            .yellowHigh = UNUSED_SETPOINT_VALUE,    \
        },                                          \
                                                    \
        .vswr =                                     \
        {                                           \
            .redHigh = UNUSED_SETPOINT_VALUE,       \
            .yellowHigh = UNUSED_SETPOINT_VALUE,    \
        },                                          \
    }                                               \
}                                                   \


struct rf_measurement
{
    float forward_power;
    float reflected_power;
    float vswr;                 /* technically vswr must be computed */
};


struct rf_setpoints
{   
    float redHigh;
    float yellowHigh;  
};


struct rf_config
{   
    char transmitter_id[sizeof(UNASSIGNED_TRANSMITTER_ID)];
    struct
    {
        struct rf_setpoints forward_pwr;
        struct rf_setpoints reflected_pwr;
        struct rf_setpoints vswr;
    } setpoints;
};


/**
 * @brief computes vswr from forward power and reflected power
 * 
 * @param measurement
 * @return void
 */
void compute_vswr(struct rf_measurement * const measurement);


#endif