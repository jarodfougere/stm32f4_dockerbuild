#ifndef RIMOT_INTERRUPTS
#define RIMOT_INTERRUPTS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/** TODO: FORMAT THIS LATER */

typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/

    /* 2 Non Maskable Interrupt              */
    ISRCODE_NonMaskableInt   = -14, 

    /* 4 Cortex-M4 Memory Management Interrupt */
    ISRCODE_MemoryManagement = -12, 

    /* 5 Cortex-M4 Bus Fault Interrupt       */
    ISRCODE_BusFault         = -11, 

     /* 6 Cortex-M4 Usage Fault Interrupt     */
    ISRCODE_UsageFault       = -10,

    /* 11 Cortex-M4 SV Call Interrupt        */
    ISRCODE_SVCall           = -5, 

    /* 12 Cortex-M4 Debug Monitor Interrupt  */
    ISRCODE_DebugMonitor     = -4, 

    /* 14 Cortex-M4 Pend SV Interrupt        */
    ISRCODE_PendSV           = -2, 

    /* 15 Cortex-M4 System Tick Interrupt    */
    ISRCODE_SysTick          = -1, 

/******  STM32 specific Interrupt Numbers ***************************/

    /* Window WatchDog Interrupt             */
    ISRCODE_WWDG             = 0, 

    /* PVD through EXTI Line detection Interrupt */
    ISRCODE_PVD              = 1, 

    /* Tamper and TimeStamp interrupts through the EXTI line */
    ISRCODE_TAMP_STAMP       = 2, 
    ISRCODE_RTC_WKUP       = 3, /* RTC Wakeup interrupt through the EXTI line */
    ISRCODE_FLASH          = 4, /* FLASH global Interrupt                */
    ISRCODE_RCC            = 5, /* RCC global Interrupt                  */
    ISRCODE_EXTI0          = 6, /* EXTI Line0 Interrupt                  */
    ISRCODE_EXTI1          = 7, /* EXTI Line1 Interrupt                  */
    ISRCODE_EXTI2          = 8, /* EXTI Line2 Interrupt                  */
    ISRCODE_EXTI3          = 9, /* EXTI Line3 Interrupt                  */
    ISRCODE_EXTI4          = 10, /* EXTI Line4 Interrupt                  */
    ISRCODE_DMA1_Stream0   = 11, /* DMA1 Stream 0 global Interrupt        */
    ISRCODE_DMA1_Stream1   = 12, /* DMA1 Stream 1 global Interrupt        */
    ISRCODE_DMA1_Stream2   = 13, /* DMA1 Stream 2 global Interrupt        */
    ISRCODE_DMA1_Stream3   = 14, /* DMA1 Stream 3 global Interrupt        */
    ISRCODE_DMA1_Stream4   = 15, /* DMA1 Stream 4 global Interrupt        */
    ISRCODE_DMA1_Stream5   = 16, /* DMA1 Stream 5 global Interrupt        */
    ISRCODE_DMA1_Stream6   = 17, /* DMA1 Stream 6 global Interrupt        */
    ISRCODE_ADC            = 18, /* ADC1, ADC2 and ADC3 global Interrupts */
    ISRCODE_EXTI9_5        = 23, /* External Line[9:5] Interrupts         */
    ISRCODE_TIM1_BRK_TIM9  = 24, /* TIM1 Break interrupt and TIM9 global interrupt */
    ISRCODE_TIM1_UP_TIM10  = 25, /* TIM1 Update Interrupt and TIM10 global interrupt */
    ISRCODE_TIM1_TRG_COM_TIM11 = 26, /* TIM1 Trig & Commutation ISR + TIM11 global ISR */
    ISRCODE_TIM1_CC        = 27, /* TIM1 Capture Compare Interrupt        */
    ISRCODE_TIM2           = 28, /* TIM2 global Interrupt                 */
    ISRCODE_TIM3           = 29, /* TIM3 global Interrupt                 */
    ISRCODE_TIM4           = 30, /* TIM4 global Interrupt                 */
    ISRCODE_I2C1_EV        = 31, /* I2C1 Event Interrupt                  */
    ISRCODE_I2C1_ER        = 32, /* I2C1 Error Interrupt                  */
    ISRCODE_I2C2_EV        = 33, /* I2C2 Event Interrupt                  */
    ISRCODE_I2C2_ER        = 34, /* I2C2 Error Interrupt                  */
    ISRCODE_SPI1           = 35, /* SPI1 global Interrupt                 */
    ISRCODE_SPI2           = 36, /* SPI2 global Interrupt                 */
    ISRCODE_USART1         = 37, /* USART1 global Interrupt               */
    ISRCODE_USART2         = 38, /* USART2 global Interrupt               */
    ISRCODE_EXTI15_10      = 40, /* External Line[15:10] Interrupts       */
    ISRCODE_RTC_Alarm      = 41, /* RTC Alarm (A and B) through EXTI Line Interrupt */
    ISRCODE_OTG_FS_WKUP    = 42, /* USB OTG FS Wakeup through EXTI line interrupt */
    ISRCODE_DMA1_Stream7   = 47, /* DMA1 Stream7 Interrupt                */
    ISRCODE_SDIO           = 49, /* SDIO global Interrupt                 */
    ISRCODE_TIM5           = 50, /* TIM5 global Interrupt                 */
    ISRCODE_SPI3           = 51, /* SPI3 global Interrupt                 */
    ISRCODE_DMA2_Stream0   = 56, /* DMA2 Stream 0 global Interrupt        */
    ISRCODE_DMA2_Stream1   = 57, /* DMA2 Stream 1 global Interrupt        */
    ISRCODE_DMA2_Stream2   = 58, /* DMA2 Stream 2 global Interrupt        */
    ISRCODE_DMA2_Stream3   = 59, /* DMA2 Stream 3 global Interrupt        */
    ISRCODE_DMA2_Stream4   = 60, /* DMA2 Stream 4 global Interrupt        */
    ISRCODE_OTG_FS         = 67, /* USB OTG FS global Interrupt           */
    ISRCODE_DMA2_Stream5   = 68, /* DMA2 Stream 5 global interrupt        */
    ISRCODE_DMA2_Stream6   = 69, /* DMA2 Stream 6 global interrupt        */
    ISRCODE_DMA2_Stream7   = 70, /* DMA2 Stream 7 global interrupt        */
    ISRCODE_USART6         = 71, /* USART6 global interrupt               */
    ISRCODE_I2C3_EV        = 72, /* I2C3 event interrupt                  */
    ISRCODE_I2C3_ER        = 73, /* I2C3 error interrupt                  */
    ISRCODE_FPU            = 81, /* FPU global interrupt                  */
    ISRCODE_SPI4           = 84, /* SPI4 global Interrupt                 */
    ISRCODE_SPI5           = 85 /* SPI5 global Interrupt                  */
}   ISRCODE_t;


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
};


void interruptSetPriority(  ISRCODE_t interrupt_code, 
                            NVIC_PREEMPTION_PRIO_t preEmption, 
                            NVIC_SUBPRIO_t subprio);

void interruptSetPrioGroup(NVIC_PRIO_GROUP_t priorityGroup);


void interruptSetState(ISRCODE_t code, INTERRUPT_STATE_t state);

#ifdef __cplusplus
}
#endif /* Clinkage */
#endif /* RIMOT_INTERRUPTS */