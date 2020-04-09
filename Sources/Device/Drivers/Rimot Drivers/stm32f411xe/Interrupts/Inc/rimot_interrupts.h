#ifndef RIMOT_INTERRUPTS
#define RIMOT_INTERRUPTS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/* IF YOU MOVE THIS I WILL FIND YOU AND MAKE YOU SUFFER -CARL */
#include "rimot_cortex_hardware_config.h"

#include "rimot_cortex_header.h"


typedef enum
{
    NVIC_PRIO_GROUP_0 = 0x00000007U,    /* 0 bits for preEmption prio */
    NVIC_PRIO_GROUP_1 = 0x00000006U,    /* 1 bit for preEmption prio */
    NVIC_PRIO_GROUP_2 = 0x00000005U,    /* 2 bits for premption prio  */
    NVIC_PRIO_GROUP_3 = 0x00000004U,    /* 3 bits for preemption prio */
    NVIC_PRIO_GROUP_4 = 0x00000003U,    /* 4 bits for preemption prio */
}   NVIC_PRIO_GROUP_t;

typedef enum
{
    NVIC_SUBPRIO_0,
    NVIC_SUBPRIO_1,
    NVIC_SUBPRIO_2,
    NVIC_SUBPRIO_3,
    NVIC_SUBPRIO_4,
    NVIC_SUBPRIO_5,
    NVIC_SUBPRIO_6,
    NVIC_SUBPRIO_7,
    NVIC_SUBPRIO_8,
    NVIC_SUBPRIO_9,
    NVIC_SUBPRIO_10,
    NVIC_SUBPRIO_11,
    NVIC_SUBPRIO_12,
    NVIC_SUBPRIO_13,
    NVIC_SUBPRIO_14,
    NVIC_SUBPRIO_15,
}   NVIC_SUBPRIO_t;


typedef enum
{
    NVIC_PREEMPTION_PRIO_0,
    NVIC_PREEMPTION_PRIO_1,
    NVIC_PREEMPTION_PRIO_2,
    NVIC_PREEMPTION_PRIO_3,
    NVIC_PREEMPTION_PRIO_4,
    NVIC_PREEMPTION_PRIO_5,
    NVIC_PREEMPTION_PRIO_6,
    NVIC_PREEMPTION_PRIO_7,
    NVIC_PREEMPTION_PRIO_8,
    NVIC_PREEMPTION_PRIO_9,
    NVIC_PREEMPTION_PRIO_10,
    NVIC_PREEMPTION_PRIO_11,
    NVIC_PREEMPTION_PRIO_12,
    NVIC_PREEMPTION_PRIO_13,
    NVIC_PREEMPTION_PRIO_14,
    NVIC_PREEMPTION_PRIO_15,
}   NVIC_PREEMPTION_PRIO_t;


typedef enum
{
    INTERRUPT_STATE_enabled,
    INTERRUPT_STATE_disabled,
}   INTERRUPT_STATE_t;



typedef enum
{
    RCC_HCLK_DIVIDER
}   RCC_HCLK_DIVIDER_t;


void interruptSetPriority(  IRQn_Type interrupt_code, 
                            NVIC_PREEMPTION_PRIO_t preEmption, 
                            NVIC_SUBPRIO_t subprio);

void interruptSetPrioGroup(NVIC_PRIO_GROUP_t priorityGroup);


void interruptSetState(IRQn_Type code, INTERRUPT_STATE_t state);


uint32_t interruptGetTickCount(void);


void interruptsInitSystickFreq(uint32_t clocksPerSysTickISR);


#ifdef __cplusplus
}
#endif /* Clinkage */
#endif /* RIMOT_INTERRUPTS */