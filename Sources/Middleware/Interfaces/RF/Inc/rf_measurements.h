#ifndef RIMOT_RF_MEASUREMENTS
#define RIMOT_RF_MEASUREMENTS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "rf_status.h"
#include "rimot_adc.h"

struct RF_measurement
{
    struct analog_measurement OUTA;   /*  FWD coupled power           */
    struct analog_measurement OUTB;   /*  REV coupled power           */
    struct analog_measurement OUTP;   /*  Power difference positive   */
    struct analog_measurement OUTN;   /*  Power difference negative   */
    struct analog_measurement DIFF;   /*  Power difference            */
    struct analog_measurement TEMP;   /*  Temperature                 */
};


RF_interface_status RF_process(uint16_t *buf, int len);
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
#endif /* RIMOT_RF_MEASUREMENTS */