#ifndef RIMOT_PIN_ALIASES
#define RIMOT_PIN_ALIASES
#ifdef __cplusplus
extern "C" {
#endif /* C LINKAGE */

#include "rimot_register_field_sizes.h"

#if defined(STM32F411RE)    /* Production mcu. LQFP64 */
#define PACKAGE_PIN_COUNT 64



#error PLEASE DEFINE THE MCU_PIN_#->PORT MAP IN rimot_gpio.c FOR STM32F411RE

#elif defined(STM32F411VE) /* Eval board MCU, LQFP100 */
#define PACKAGE_PIN_COUNT 100
#define PE2  0
#define PE3  1
#define PE4  2
#define PE5  3
#define PE6  4

/* pin 5 (indexed starting from 1) is VBAT */

#define PC13 6
#define PC14 7
#define PC15 8
#define PH0  11
#define PH1  12

/* VSS */
/* VDD */

#define PC0  14
#define PC1  15
#define PC2  16
#define PC3  17

/* VDD 
 * VSSA
 * VREF+
 * VDDA
 */

#define PA0  ((mcu_word)22)
#define PA1  ((mcu_word)23)
#define PA2  ((mcu_word)24)
#define PA3  ((mcu_word)25)

/* VSS */
/* VDD */

#define PA4  28
#define PA5  29
#define PA6  30
#define PA7  31
#define PC4  32
#define PC5  33
#define PB0  34

/* AND SO ON... */

#else
#error NEITHER STM32F411RE NOR STM32F411VE IS DEFINED. PLEASE SEE rimot_gpio.c
#endif /* PACKAGE BASED PIN ALIASES */
#ifdef __cplusplus
}
#endif /* C LINKAGE */
#endif /* RIMOT_PIN_ALIASES */