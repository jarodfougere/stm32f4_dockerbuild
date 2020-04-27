#ifndef RIMOT_CORTEX
#define RIMOT_CORTEX
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>


void cortexDisable_Fault_IRQ_Handling(void);
void cortexEnable_Fault_IRQ_Handling(void);
void cortexDisable_Exception_IRQ_Handling(void);
void cortexEnable_Exception_IRQ_Handling(void);
uint32_t cortexGetPriorityMask(void);
void cortexInitSysTick(void (*cbFunc)(void), uint32_t clocksPerSysTickISR);
void cortexSystemReset(void);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_CORTEX*/
