#ifndef RIMOT_INTERRUPTS
#define RIMOT_INTERRUPTS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/* IF YOU MOVE THIS I WILL FIND YOU AND MAKE YOU SUFFER -CARL */
#include "rimot_cortex_hardware_config.h"

/** TODO: FORMAT THIS LATER */
typedef enum
{
/******  Cortex-M4 Processor Exceptions ****/

    /* 2 Non Maskable Interrupt              */
    NonMaskableInt_IRQn = -14, 

    /* 4 Cortex-M4 Memory Management Interrupt */
    MemoryManagement_IRQn = -12, 

    /* 5 Cortex-M4 Bus Fault Interrupt       */
    BusFault_IRQn = -11, 

     /* 6 Cortex-M4 Usage Fault Interrupt     */
    UsageFault_IRQn = -10,

    /* 11 Cortex-M4 SV Call Interrupt        */
    SVCall_IRQn = -5, 

    /* 12 Cortex-M4 Debug Monitor Interrupt  */
    DebugMonitor_IRQn = -4, 

    /* 14 Cortex-M4 Pend SV Interrupt        */
    PendSV_IRQn = -2, 

    /* 15 Cortex-M4 System Tick Interrupt    */
    SysTick_IRQn = -1, 

/******  Peripheral-specific ***************************/

    /* Window WatchDog Interrupt             */
    WWDG_IRQn = 0, 

    /* PVD through EXTI Line detection Interrupt */
    PVD_IRQn = 1, 

    /* Tamper and TimeStamp interrupts through the EXTI line */
    TAMP_STAMP_IRQn = 2, 
    RTC_WKUP_IRQn = 3, /* RTC Wakeup interrupt through the EXTI line */
    FLASH_IRQn = 4, /* FLASH global Interrupt                */
    RCC_IRQn = 5, /* RCC global Interrupt                  */
    EXTI0_IRQn = 6, /* EXTI Line0 Interrupt                  */
    EXTI1_IRQn = 7, /* EXTI Line1 Interrupt                  */
    EXTI2_IRQn = 8, /* EXTI Line2 Interrupt                  */
    EXTI3_IRQn = 9, /* EXTI Line3 Interrupt                  */
    EXTI4_IRQn = 10, /* EXTI Line4 Interrupt                  */
    DMA1_Stream0_IRQn = 11, /* DMA1 Stream 0 global Interrupt        */
    DMA1_Stream1_IRQn = 12, /* DMA1 Stream 1 global Interrupt        */
    DMA1_Stream2_IRQn = 13, /* DMA1 Stream 2 global Interrupt        */
    DMA1_Stream3_IRQn = 14, /* DMA1 Stream 3 global Interrupt        */
    DMA1_Stream4_IRQn = 15, /* DMA1 Stream 4 global Interrupt        */
    DMA1_Stream5_IRQn = 16, /* DMA1 Stream 5 global Interrupt        */
    DMA1_Stream6_IRQn = 17, /* DMA1 Stream 6 global Interrupt        */
    ADC_IRQn = 18, /* ADC1, ADC2 and ADC3 global Interrupts */
    EXTI9_5_IRQn = 23, /* External Line[9:5] Interrupts         */
    TIM1_BRK_TIM9_IRQn = 24, /* TIM1 Break interrupt and TIM9 global interrupt */
    TIM1_UP_TIM10_IRQn = 25, /* TIM1 Update Interrupt and TIM10 global interrupt */
    TIM1_TRG_COM_TIM11_IRQn = 26, /* TIM1 Trig & Commutation ISR + TIM11 global ISR */
    TIM1_CC_IRQn = 27, /* TIM1 Capture Compare Interrupt        */
    TIM2_IRQn = 28, /* TIM2 global Interrupt                 */
    TIM3_IRQn = 29, /* TIM3 global Interrupt                 */
    TIM4_IRQn = 30, /* TIM4 global Interrupt                 */
    I2C1_EV_IRQn = 31, /* I2C1 Event Interrupt                  */
    I2C1_ER_IRQn = 32, /* I2C1 Error Interrupt                  */
    I2C2_EV_IRQn = 33, /* I2C2 Event Interrupt                  */
    I2C2_ER_IRQn = 34, /* I2C2 Error Interrupt                  */
    SPI1_IRQn = 35, /* SPI1 global Interrupt                 */
    SPI2_IRQn = 36, /* SPI2 global Interrupt                 */
    USART1_IRQn = 37, /* USART1 global Interrupt               */
    USART2_IRQn = 38, /* USART2 global Interrupt               */
    EXTI15_10_IRQn = 40, /* External Line[15:10] Interrupts       */
    RTC_Alarm_IRQn = 41, /* RTC Alarm (A and B) through EXTI Line Interrupt */
    OTG_FS_WKUP_IRQn = 42, /* USB OTG FS Wakeup through EXTI line interrupt */
    DMA1_Stream7_IRQn = 47, /* DMA1 Stream7 Interrupt                */
    SDIO_IRQn = 49, /* SDIO global Interrupt                 */
    TIM5_IRQn = 50, /* TIM5 global Interrupt                 */
    SPI3_IRQn = 51, /* SPI3 global Interrupt                 */
    DMA2_Stream0_IRQn = 56, /* DMA2 Stream 0 global Interrupt        */
    DMA2_Stream1_IRQn = 57, /* DMA2 Stream 1 global Interrupt        */
    DMA2_Stream2_IRQn = 58, /* DMA2 Stream 2 global Interrupt        */
    DMA2_Stream3_IRQn = 59, /* DMA2 Stream 3 global Interrupt        */
    DMA2_Stream4_IRQn = 60, /* DMA2 Stream 4 global Interrupt        */
    OTG_FS_IRQn = 67, /* USB OTG FS global Interrupt           */
    DMA2_Stream5_IRQn = 68, /* DMA2 Stream 5 global interrupt        */
    DMA2_Stream6_IRQn = 69, /* DMA2 Stream 6 global interrupt        */
    DMA2_Stream7_IRQn = 70, /* DMA2 Stream 7 global interrupt        */
    USART6_IRQn = 71, /* USART6 global interrupt               */
    I2C3_EV_IRQn = 72, /* I2C3 event interrupt                  */
    I2C3_ER_IRQn = 73, /* I2C3 error interrupt                  */
    FPU_IRQn = 81, /* FPU global interrupt                  */
    SPI4_IRQn = 84, /* SPI4 global Interrupt                 */
    SPI5_IRQn = 85 /* SPI5 global Interrupt                  */
}   IRQn_Type;


/** TODO: FIX THE ENUM NAMES OF THE IRQn enums to actual match what's 
 *  prescribed by CMSIS standard 
 */
#include "core_cm4.h"


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

#ifdef __cplusplus
}
#endif /* Clinkage */
#endif /* RIMOT_INTERRUPTS */