#ifndef RIMOT_GPIO_PIN_CONFIG_INTERFACE
#define RIMOT_GPIO_PIN_CONFIG_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>


/* 
 * Unfortunately there is a giant messy history why this has to be here that 
 * involves database acknowledgement flags and default values for JSON fields 
 * that did not make it across the LTE cloud uplink. 
 * 
 * PLEASE JUST DON'T TOUCH THIS
 */
#define PIN_CONFIG_UNSET_VAL -3 

/* Default value to set the pin period when we reset a core config */
#define PINCONFIG_PERIOD_FIELD_RESET_VAL 0


typedef enum
{   
    GPIO_PIN_REGISTERED_inactive = PIN_CONFIG_UNSET_VAL,
    GPIO_PIN_REGISTERED_active = 0,
}   GPIO_PIN_REGISTERED_t;


typedef enum
{
    GPIO_PIN_ID1,
    GPIO_PIN_ID2,
    GPIO_PIN_ID3,
    GPIO_PIN_ID4,
    GPIO_PIN_ID5,
    GPIO_PIN_ID6,
    GPIO_PIN_ID7,
    GPIO_PIN_ID8,
}   GPIO_PIN_ID_t;


typedef enum
{   
    GPIO_PINTYPE_unused = PIN_CONFIG_UNSET_VAL,
    GPIO_PINTYPE_digital_input = 0U,
    GPIO_PINTYPE_relay_output  = 1U,
    GPIO_PINTYPE_analog_input  = 2U,
}   GPIO_PINTYPE_t;


typedef enum 
{   
    GPIO_PINCMD_stop  = 0U,
    GPIO_PINCMD_start = 1U,
}   GPIO_PINCMD_t;


typedef enum
{
    GPIO_PIN_LABEL_unused = PIN_CONFIG_UNSET_VAL,
}   GPIO_PIN_LABEL_t;


typedef enum
{
    GPIO_PIN_PRIORITY_unused = PIN_CONFIG_UNSET_VAL,
}   GPIO_PIN_PRIORITY_t;



typedef struct
{
    GPIO_PIN_ID_t  id;
    GPIO_PINTYPE_t type;
    GPIO_PINCMD_t  cmd;
}   pin_command_t;


typedef struct
{
    GPIO_PIN_ID_t         id;
    GPIO_PINTYPE_t        type;
    GPIO_PIN_REGISTERED_t active;
    GPIO_PIN_LABEL_t      label;
    GPIO_PIN_PRIORITY_t   priority;
    int32_t               period;   /* units in multiples of 100 ms */
}   pinCfgCore_t;


void pinCfg_resetToDefault(pinCfgCore_t *cfg, 
                            GPIO_PIN_ID_t id, 
                            GPIO_PINTYPE_t type);


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_GPIO_PIN_CONFIG_INTERFACE */