#ifndef RIMOT_PIN_ALIASES
#define RIMOT_PIN_ALIASES
#ifdef __cplusplus
extern "C" {
#endif /* C LINKAGE */

#include <stdint.h>

#if defined(STM32F411RE)    /* Production mcu. LQFP64 */
#define PACKAGE_PIN_COUNT 64

#error PLEASE DEFINE THE MCU_PIN_#->PORT MAP IN rimot_gpio.h FOR STM32F411RE

#elif defined(STM32F411VE) /* Eval board MCU, LQFP100 */
#define PACKAGE_PIN_COUNT 100

typedef enum
{
    MCUPIN_PE2  = 0,
    MCUPIN_PE3  = 1,
    MCUPIN_PE4  = 2,
    MCUPIN_PE5  = 3,
    MCUPIN_PE6  = 4,
    MCUPIN_PC13 = 6,
    MCUPIN_PC14 = 7,
    MCUPIN_PC15 = 8,
    MCUPIN_PH0  = 11,
    MCUPIN_PH1  = 12,
    MCUPIN_PC0  = 14,
    MCUPIN_PC1  = 15,
    MCUPIN_PC2  = 16,
    MCUPIN_PC3  = 17,
    MCUPIN_PA0  = 22,
    MCUPIN_PA1  = 23,
    MCUPIN_PA2  = 24,
    MCUPIN_PA3  = 25,
    MCUPIN_PA4  = 28,
    MCUPIN_PA5  = 29,
    MCUPIN_PA6  = 30,
    MCUPIN_PA7  = 31,
    MCUPIN_PC4  = 32,
    MCUPIN_PC5  = 33,
    MCUPIN_PB0  = 34,
    MCUPIN_PB1  = 35,
    MCUPIN_PB2  = 36,
    MCUPIN_PE7  = 37,
    MCUPIN_PE8  = 38,
    MCUPIN_PE9  = 39,
    MCUPIN_PE10 = 40,
    MCUPIN_PE11 = 41,
    MCUPIN_PE12 = 42,
    MCUPIN_PE13 = 43,
    MCUPIN_PE14 = 44,
    MCUPIN_PE15 = 45,
    MCUPIN_PB10 = 46,
    MCUPIN_PB12 = 50,
    MCUPIN_PB13 = 51,
    MCUPIN_PB14 = 52,
    MCUPIN_PB15 = 53,
    MCUPIN_PD8  = 54,
    MCUPIN_PD9  = 55,
    MCUPIN_PD10 = 56,
    MCUPIN_PD11 = 57,
    MCUPIN_PD12 = 58,
    MCUPIN_PD13 = 59,
    MCUPIN_PD14 = 60,
    MCUPIN_PD15 = 61,
    MCUPIN_PC6  = 62,
    MCUPIN_PC7  = 63,
    MCUPIN_PC8  = 64,
    MCUPIN_PC9  = 65,
    MCUPIN_PA8  = 66,
    MCUPIN_PA9  = 67,
    MCUPIN_PA10 = 68,
    MCUPIN_PA11 = 69,
    MCUPIN_PA12 = 70,
    MCUPIN_PA13 = 71,
    MCUPIN_PA14 = 75,
    MCUPIN_PA15 = 76,
    MCUPIN_PC10 = 77,
    MCUPIN_PC11 = 78,
    MCUPIN_PC12 = 79,
    MCUPIN_PD0  = 80,
    MCUPIN_PD1  = 81,
    MCUPIN_PD2  = 82,
    MCUPIN_PD3  = 83,
    MCUPIN_PD4  = 84,
    MCUPIN_PD5  = 85,
    MCUPIN_PD6  = 86,
    MCUPIN_PD7  = 87,
    MCUPIN_PB3  = 88,
    MCUPIN_PB4  = 89,
    MCUPIN_PB5  = 90,
    MCUPIN_PB6  = 91,
    MCUPIN_PB7  = 92,
    MCUPIN_PB8  = 94,
    MCUPIN_PB9  = 95,
    MCUPIN_PE0  = 96,
    MCUPIN_PE1  = 97,
}   MCUPIN_t;


typedef enum
{
    GPIO_PORT_IDX_A         = 0U,
    GPIO_PORT_IDX_B         = 1U,
    GPIO_PORT_IDX_C         = 2U,
    GPIO_PORT_IDX_D         = 3U,
    GPIO_PORT_IDX_E         = 4U,
    UNUSED_GPIO_PORT_IDX_F  = 5U,
    UNUSED_GPIO_PORT_IDX_G  = 6U,
    GPIO_PORT_IDX_H         = 7U,
}   GPIO_PORT_IDX_t;

struct pin_map
{   
    GPIO_PORT_IDX_t port_idx;
    uint32_t        bit; 
};   

#else
#error NEITHER STM32F411RE NOR STM32F411VE IS DEFINED. PLEASE SEE rimot_gpio.c
#endif /* PACKAGE BASED PIN ALIASES */


/**
 * @fn pin_aliasLookup
 * @brief get the gpio port index and gpio port bit that maps to a given pin
 * "name" on the microcontroller package.
 * 
 * @param mcu_pin_number : one of enum MCUPIN_ALIAS. this is the "name" of the 
 * pin on the microcontroller package 
 * @return struct pin_map : a structure that maps the pin name (enumerated type)
 * on the mcu package to its gpio port index and the bit of that pin for its
 * mapped port.
 */
struct pin_map pin_aliasLookup(uint32_t mcu_pin_number);


#ifdef __cplusplus
}
#endif /* C LINKAGE */
#endif /* RIMOT_PIN_ALIASES */
