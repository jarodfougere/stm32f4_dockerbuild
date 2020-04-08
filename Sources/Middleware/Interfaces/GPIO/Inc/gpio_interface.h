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

typedef struct gpio_interface_config_structure gpioConfig_t;
gpioConfig_t* gpioConfigInit(void);
relayConfig_t* gpioGetRelay(const gpioConfig_t *cfg, GPIO_PIN_ID_t pin);
inputConfig_t* gpioGetInput(const gpioConfig_t* cfg, GPIO_PIN_ID_t pin);
batConfig_t* gpioGetBattery(const gpioConfig_t *cfg, GPIO_PIN_ID_t pin);


void gpioIF_initBattery(void);
void gpioIF_measureBattery(void);

void gpioIF_initInputs(void);

void gpioIF_initRelays(void);



#ifdef __cplusplus
}
#endif /* C linkage */
#endif