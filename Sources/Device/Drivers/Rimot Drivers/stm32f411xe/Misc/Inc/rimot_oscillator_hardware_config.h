#ifndef RIMOT_CORTEX_OSCILLATOR_CONFIG
#define RIMOT_CORTEX_OSCILLATOR_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C LINKAGE */

#include <stdint.h>

/* Core revision r0p1 */
/* USED MOSTLY FOR CMSIS RELEASE SELECTION */
#define __CM4_REV                 0x0001U  

/* STM32F411 provides an MPU */
#define __MPU_PRESENT             1U       

/* STM32F411 uses 4 Bits for the isr preemption Priority Levels */
#define __NVIC_PRIO_BITS          4U       

/* Set to 1 if different SysTick Config is used */
#define __Vendor_SysTickConfig    0U  

/* STM32F411 has a hardware floating point unit (single precision) */
#define __FPU_PRESENT             1U       


#if defined(STM32F411RE)    /* Production mcu. LQFP64 */
#define HIGH_SPEED_EXTERNAL_XTAL_FREQ 8000000U /* 8MHz */

#elif defined(STM32F411VE) /* Eval board MCU, LQFP100 */
#define HIGH_SPEED_EXTERNAL_XTAL_FREQ 20000000U /* 20MHz */


#endif /* MCU PACKAGE SELECTION */

#define HSI_RC_OSC_FREQ ((uint32_t)16000000U) /* 16 MHz */
#define LSI_RC_OSC_FREQ ((uint32_t)32000U)    /* 32 KHz */   

#define HSE_STARTUP_TIMEOUT_MS 100U

#ifdef __cplusplus
}
#endif /* C LINKAGE */
#endif /* RIMOT_CORTEX_OSCILLATOR_CONFIG */