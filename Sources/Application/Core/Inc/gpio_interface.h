#ifndef RIMOT_GPIO_INTERFACES
#define RIMOT_GPIO_INTERFACES
#include <stdint.h>
#include <limits.h>

#include "setpoints.h"

/* active/inactive pins */
#define INTERFACE_PIN_INACTIVE  0
#define INTERFACE_PIN_ACTIVE    1

#define NUM_PIN_TYPES           3 /* input, relay, analog */
#define NUM_DIGITAL_INPUTS      8
#define NUM_RELAYS              4
#define NUM_BATTERIES           4
#define NUM_IO_PINS             (NUM_DIGITAL_INPUTS +NUM_RELAYS + NUM_BATTERIES)
#define GPIO_PIN(type, idx)     (pin_index_base[type] + idx)


/* interface array indexing for relay types */
#define hold_time_index         0
#define default_state_index     1
#define current_state_index     2

/* interface array indexing for digital input types */
#define debounce_time_index     0
#define trigger_level_index     1


/* this assumes that all elements in the gpio pin config are type INT32 */
#define GPIO_PIN_CONFIG_NOT_EXIST_ATTR_VAL INT32_MAX

#define GPIO_PIN_CONFIG_MIN_RELAY_DEBOUNCE_S      (int32_t)(-1) /* -1==toggle */
#define GPIO_PIN_CONFIG_MIN_INPUT_DEBOUNCE_S      (int32_t)(0)
#define GPIO_PIN_CONFIG_MIN_BATTERY_DEBOUNCE_S      (int32_t)(0)




typedef enum
{
    RELAYPOS_closed = 1,
    RELAYPOS_open = 0,
}   RELAYPOS_t;


typedef enum
{
    TRIGGERMODE_high = 1,
    TRIGGERMODE_low  = 0,
}   TRIGGERMODE_t;


typedef enum
{
    PINTYPE_digital_input,
    PINTYPE_relay_output,
    PINTYPE_analog_input,
}   PINTYPE_t;


typedef enum
{
    PINMODE_active,
    PINMODE_inactive
}   PINMODE_t;


typedef enum 
{   
    PINCMD_stop  = 0,
    PINCMD_start = 1,
}   PINCMD_t;


typedef enum
{
    PCFGERR_ok,
    PCFGERR_no_id,
    PCFGERR_no_type,
    PCFGERR_no_active,
    PCFGERR_no_debounce,
    PCFGERR_no_state,
    PCFGERR_no_trigger,
    PCFGERR_no_redhigh,
    PCFGERR_no_yellowhigh,
    PCFGERR_no_yellowlow,
    PCFGERR_no_redlow,
    PCFGERR_wrong_type,
    PCFGERR_id_oob,
    PCFGERR_type_oob,
    PINCONIFGERR_active_oob,
    PCFGERR_debounce_oob, 
    PCFGERR_redhigh_oob,
    PCFGERR_yellowhigh_oob,
    PCFGERR_yellowlow_oob,
    PCFGERR_redlow_oob,
    PCFGERR_state_oob,
    PCFGERR_trigger_oob,
    PCFGERR_battery_sp_out_of_order,
}   PCFGERR_t;


struct pinConfig
{
    int32_t id;         // pin ID
    int32_t type;       // pin type
    int32_t active;     // if pin is registerd on site page
    int32_t label;      // normalized device type for analytics 
    int32_t priority;   // device priority (note yet implemented)
    int32_t period;     // data period (debounce/holdtime/sample interval etc..)
    union
    {
        struct
        {   
            //UNITS IN MILLIVOLTS
            int32_t redHigh;
            int32_t yellowHigh;  
            int32_t yellowLow;
            int32_t redLow;
        }   battery;

        struct
        {
            int32_t default_state;
            int32_t current_state;
        }   relay;

        struct 
        {
            int32_t trigger;
        }   input;
    } setpoints;
    int32_t reserved;   //packing alignment
};


struct pinCommand
{
    int32_t id;
    int32_t type;
    int32_t trigger;
};


int32_t update_pin_config(struct pinConfig *dst, const struct pinConfig *src);
int32_t execute_pin_command(const struct pinCommand *cmd);


int32_t update_gpio_interfaces(void);

#endif