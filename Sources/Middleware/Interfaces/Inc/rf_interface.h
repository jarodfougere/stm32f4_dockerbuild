#ifndef RIMOT_RF_INTERFACES
#define RIMOT_RF_INTERFACES
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>
#include <float.h>

/* Retval definitions */
#define RF_VALID (0)
#define RF_INVALID (1)

/* an "rf input" is a PAIR of the N type connectors going to a coupler */
#define NUM_RF_INPUTS 2
#define UNASSIGNED_TRANSMITTER_ID "0000000000000000000000"
#define UNUSED_SETPOINT_VALUE 0.0


/* 
 * Coupler IC leaks 1% of fwd power 
 * to reflected so 300W transmitter 
 * with perfect  antenna will still
 * couple 3W reflected. Giving best 
 * case scenario VSWR of 1.22 
 */
#define MIN_VSWR (1.22) 

/*
 * No theoretical upper limit for VSWR
 */
#define MAX_VSWR FLT_MAX /* Most a float can hold */


/* Setpoints default initializer */
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


struct MEASUREMENT_CHVAL
{
    uint16_t max; /*< maximum return loss in data window, units ADC */
    uint16_t min; /*< minimum return loss in data window, units ADC */
    uint16_t avg; /*< average return loss in data window, units ADC */
    uint16_t median;
    uint16_t Navg; /*< number of samples evaluate in this data window */
};


struct MEASUREMENT_DIFFVAL
{
    int16_t max; /*< maximum return loss in data window, units ADC */
    int16_t min; /*< minimum return loss in data window, units ADC */
    int16_t avg; /*< average return loss in data window, units ADC */
    int16_t median;
    int16_t Navg; /*< number of samples evaluate in this data window */
};


typedef struct
{
    struct MEASUREMENT_CHVAL OUTA;   /*< FWD coupled power           */
    struct MEASUREMENT_CHVAL OUTB;   /*< REV coupled power           */
    struct MEASUREMENT_CHVAL OUTP;   /*< Power difference positive   */
    struct MEASUREMENT_CHVAL OUTN;   /*< Power difference negative   */
    struct MEASUREMENT_DIFFVAL DIFF; /*< Power difference            */
    struct MEASUREMENT_CHVAL TEMP;   /*< Temperature                 */
}   MEASUREMENTS_t;


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RF_INTERFACE */