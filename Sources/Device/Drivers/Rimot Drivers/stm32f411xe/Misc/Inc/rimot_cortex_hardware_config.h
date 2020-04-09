#ifndef RIMOT_CORTEX_HARDWARE_CONFIG
#define RIMOT_CORTEX_HARDWARE_CONFIG
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


#ifdef __cplusplus
}
#endif /* C LINKAGE */
#endif /* RIMOT_CORTEX_HARDWARE_CONFIG */