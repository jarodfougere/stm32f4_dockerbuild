#ifndef RIMOT_GPIO_INTERFACES
#define RIMOT_GPIO_INTERFACES
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include <limits.h>

#include "pin_config_interface.h"
#include "battery_interface.h"
#include "relay_interface.h"
#include "digital_input_interface.h"

#if defined(STM32F411VE)
#define BAT_PIN1 MCUPIN_PA7
#define BAT_PIN2 MCUPIN_PB8
#define BAT_PIN3 MCUPIN_PB0
#define BAT_PIN4 MCUPIN_PB1
#elif defined(STM32F411RE)
#error BAT_PINx must be defined for STM32F411RE in gpio_interface.c
#else
#error NO DEFINITION FOR STM32F411xE package
#endif /* PACKAGE SELECTION */

/* Error codes */
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
    PCFGERR_unknown,
}   PCFGERR_t;

typedef struct gpio_interface_config_structure gpioConfig_t;
gpioConfig_t* gpioConfigInit(void);
relayConfig_t* gpioGetRelay(const gpioConfig_t *cfg, GPIO_PIN_ID_t pin);
inputConfig_t* gpioGetInput(const gpioConfig_t* cfg, GPIO_PIN_ID_t pin);
batConfig_t* gpioGetBattery(const gpioConfig_t *cfg, GPIO_PIN_ID_t pin);


void gpioIF_initBattery(void);
void gpioIF_measureBattery(void);

void gpioIF_initInputs(void);

void gpioIF_initRelays(void);


const char* gpioGetPinConfigStatusMsg(PCFGERR_t code);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif