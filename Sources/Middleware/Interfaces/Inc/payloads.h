#ifndef RIMOT_PAYLOADS
#define RIMOT_PAYLOADS
#ifdef __cplusplus
extern "C" {
#endif /* C Linkage */

#include <stdint.h>
#include <time.h>

#include "gpio_interface.h"
#include "rf_interface.h"
#include "humidity_interface.h"
#include "temperature_interface.h"


typedef struct
{
    int8_t  firmware_id[8];
    int8_t  hardware_id[8];
    int8_t  device_uid[13];
    uint8_t num_inputs;
    uint8_t num_relays;
    uint8_t num_batteries;
}   device_payload_t;

typedef struct
{
    struct pin_cfg    cfg;
}   relay_payload_t;


typedef struct
{
    struct pin_cfg    cfg;
    uint32_t            level;
}   digital_input_payload_t;


typedef struct
{
    struct pin_cfg    cfg;
    uint32_t            voltage;
}   battery_payload_t;


typedef struct
{
    uint32_t humidity;
    uint32_t celsius;
    //TODO: MOTION?
}   moth_payload_t;



struct rf_payload
{   
    struct rf_config        cfg;
    struct rf_measurement   rf_max;
    struct rf_measurement   rf_min;
    struct rf_measurement   rf_avg;
};   


void doDoSysCommand(const char* cmd_string);

void transmitAllPayloads(void);


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_PAYLOADS */