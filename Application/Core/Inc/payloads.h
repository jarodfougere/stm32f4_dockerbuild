#ifndef LOWPOWER_PAYLOADS
#define LOWPOWER_PAYLOADS
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
    uint32_t        id;
    uint32_t        type;
    pin_config_t    cfg;
}   relay_payload_t;


typedef struct
{
    uint32_t        id;
    uint32_t        type;
    pin_config_t    cfg;
    uint32_t        level;
}   digital_input_payload_t;


typedef struct
{
    uint32_t        id;
    uint32_t        type;
    pin_config_t    cfg;
    uint32_t        voltage;
}   battery_payload_t;




typedef struct
{
    uint32_t humidity;
    uint32_t celsius;
    //TODO: MOTION?
}   moth_payload_t;



typedef struct
{   
    rf_config_t         cfg;
    rf_measurement_t    rf_max;
    rf_measurement_t    rf_min;
    rf_measurement_t    rf_avg;
}   rf_payload_t;

#endif