#ifndef RIMOT_GPIO_INTERFACES
#define RIMOT_GPIO_INTERFACES
#include <stdint.h>

#include "setpoints.h"

/* active/inactive pins */
#define INTERFACE_PIN_INACTIVE  0
#define INTERFACE_PIN_ACTIVE    1

#define NUM_PIN_TYPES           3 /* input, relay, analog */
#define NUM_DIGITAL_INPUTS      8
#define NUM_RELAYS              4
#define NUM_BATTERIES           4
#define NUM_IO_PINS             NUM_DIGITAL_INPUTS + NUM_RELAYS + NUM_BATTERIES

/* interface array indexing for relay types */
#define hold_time_index         0
#define default_state_index     1
#define current_state_index     2

/* interface array indexing for digital input types */
#define debounce_time_index     0
#define trigger_level_index     1


typedef enum
{
    PINTYPE_digital_input,
    PINTYPE_relay_output,
    PINTYPE_analog_input,
}   PINTYPE_t;


struct float_setpoints
{
    float redHigh;
    float yellowHigh;
    float yellowLow;
    float redLow;
};

struct digital_setpoints
{
    int trigger_state;      //state for async alert (input-stype pins)
    int default_state;      //default control state (output-style pins)
};



struct pinConfig
{
    int id;         // pin ID
    int type;       // pin type
    int active;     // if pin is registerd on site page
    int label;      // normalized device type for analytics 
    int priority;   // device priority (note yet implemented)
    int period;     // pin data period (debounce/holdtime/sample period etc...)
    union
    {   
        struct digital_setpoints digitals;
        struct float_setpoints   numerics;
    }   setpoints;  //pin "setpoints"

    int reserved;   //packing alignment
};


struct pinCommand
{
    int id;
    int type;
    int trigger;
};




extern const uint8_t max_pin_index[NUM_PIN_TYPES];
extern const uint8_t pin_index_base[NUM_PIN_TYPES];

#define GPIO_PIN(type, idx) (pin_index_base[type] + idx)




int update_pin_config(struct pinConfig *cfg);
int update_pin_command(struct pinCommand *cmd);


int update_gpio_interfaces(void);

#endif