#ifndef RIMOT_RF_INTERFACES
#define RIMOT_RF_INTERFACES
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>
#include <float.h>

#include "analog_measurements.h"

enum RF_interface_status
{
    RF_VALID,
    RF_INVALID,
};

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


typedef float rf_powerVal;

struct rf_setpoints
{   
    rf_powerVal redHigh;
    rf_powerVal yellowHigh;  
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

void rfIF_init(void);


enum RF_interface_status RF_process(uint16_t *buf, int len);
float RF_getFWDMinVoltage();
float RF_getREVMinVoltage();
float RF_getDIFMinVoltage();
float RF_getTEMPMinVoltage();
float RF_getFWDMaxVoltage();
float RF_getREVMaxVoltage();
float RF_getDIFMaxVoltage();
float RF_getTEMPMaxVoltage();
float RF_getFWDAvgVoltage();
float RF_getREVAvgVoltage();
float RF_getDIFAvgVoltage();
float RF_getTEMPAvgVoltage();
float RF_getFWDMedVoltage();
float RF_getREVMedVoltage();
float RF_getDIFMedVoltage();
float RF_getTEMPMedVoltage();
uint16_t RF_getFWDNAvg();
uint16_t RF_getREVNAvg();
uint16_t RF_getDIFNAvg();
uint16_t RF_getVSWRMin(float *value);
uint16_t RF_getVSWRMax(float *value);
uint16_t RF_getVSWRAvg(float *value);
uint16_t RF_getVSWRMedian(float *value);
uint16_t RF_getRLAvg(float *value);
uint16_t RF_getFWDMinPower(float *value);
uint16_t RF_getFWDMaxPower(float *value);
uint16_t RF_getFWDAvgPower(float *value);
uint16_t RF_getFWDMedianPower(float *value);
uint16_t RF_getREVMinPower(float *value);
uint16_t RF_getREVMaxPower(float *value);
uint16_t RF_getREVAvgPower(float *value);
uint16_t RF_getREVMedianPower(float *value);
uint16_t RF_getTemperature(float *value);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RF_INTERFACE */