
#ifndef RIMOT_MCU_TIMERS
#define RIMOT_MCU_TIMERS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

/*
 *******************************************************************************
 *
 * TIM1 features:
 *     • 16-bit up, down, up/down auto-reload counter.
 *     • 16-bit programmable prescaler allowing dividing (also “on the fly”) 
 *     the counter clock frequency either by any factor between 1 and 65536.
 *     • Up to 4 independent channels for:
 *         – Input Capture
 *         – Output Compare
 *         – PWM generation (Edge and Center-aligned Mode)
 *         – One-pulse mode output
 *     • Complementary outputs with programmable dead-time
 *     • Synchronization circuit to control the timer with external signals and
 *       to interconnect several timers together.
 *     • Repetition counter to update the timer registers only after a given
 *     number of cycles of the counter.
 *     • Break input to put the timer’s output signals in reset state or 
 *     in a known state.
 *     • Interrupt/DMA generation on the following events:
 *         – Update: counter overflow/underflow, counter initialization (by
 *         software or internal/external trigger)
 *         – Trigger event (counter start, stop, initialization or count by
 *         internal/external trigger)
 *         – Input capture
 *         – Output compare
 *         – Break input
 *     • Supports incremental (quadrature) encoder and hall-sensor circuitry 
 *     for positioning purposes
 *     • Trigger input for external clock or cycle-by-cycle current management
 *
 *******************************************************************************
 *
 * TIM9 features:
 *     • 16-bit auto-reload upcounter
 *     • 16-bit programmable prescaler used to divide the counter clock
 *       frequency by any factor between 1 and 65536 (can be changed “on 
 *       the fly”)
 *     • Up to 2 independent channels for:
 *         – Input capture
 *         – Output compare
 *         – PWM generation (edge-aligned mode)
 *         – One-pulse mode output
 *     • Synchronization circuit to control the timer with external signals and
 *       to interconnect several timers together
 *     • Interrupt generation on the following events:
 *         – Update: counter overflow, counter initialization (by software or 
 *         internal trigger)
 *         – Trigger event (counter start, stop, initialization or count by
 *         internal trigger)
 *         – Input capture
 *         – Output compare
 *
 *******************************************************************************
 *
 * TIM10/TIM11 features
 *     • 16-bit auto-reload upcounter
 *     • 16-bit programmable prescaler used to divide the counter clock
 *       frequency by any factor between 1 and 65536 (can be changed “on the
 *       fly”)
 *     • independent channel for:
 *         – Input capture
 *         – Output compare
 *         – PWM generation (edge-aligned mode)
 *         – One-pulse mode output
 *         • Interrupt generation on the following events:
 *         – Update: counter overflow, counter initialization (by software)
 *         – Input capture
 *         – Output compare
 *
 ********************************************************************************
 * TIM2 to TIM5 features:
 *     • 16-bit (TIM3 and TIM4) or 32-bit (TIM2 and TIM5) up, down, up/down
 *     auto-reload counter.
 *     • 16-bit programmable prescaler used to divide (also “on the fly”) the
 *     counter clock frequency by any factor between 1 and 65536.
 *     • Up to 4 independent channels for:
 *         – Input capture
 *         – Output compare
 *         – PWM generation (Edge- and Center-aligned modes)
 *         – One-pulse mode output
 *     • Synchronization circuit to control the timer with external signals and
 *       to interconnect several timers.
 *     • Interrupt/DMA generation on the following events:
 *         – Update: counter overflow/underflow, counter initialization (by
 *         software or internal/external trigger)
 *         – Trigger event (counter start, stop, initialization or count by
 *         internal/external trigger)
 *         – Input capture
 *         – Output compare
 *     • Supports incremental (quadrature) encoder and hall-sensor circuitry for
 *     positioning purposes
 *     • Trigger input for external clock or cycle-by-cycle current management
 *
 *******************************************************************************
 */

#define TIM1_BASE  (APB2PERIPH_BASE + 0x0000UL)

#define TIM3_BASE  (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE  (APB1PERIPH_BASE + 0x0800UL)

#define TIM2_BASE  (APB1PERIPH_BASE + 0x0000UL)     
#define TIM5_BASE  (APB1PERIPH_BASE + 0x0C00UL)

#define TIM9_BASE  (APB2PERIPH_BASE + 0x4000UL)
#define TIM10_BASE (APB2PERIPH_BASE + 0x4400UL)
#define TIM11_BASE (APB2PERIPH_BASE + 0x4800UL)


/*
 * REFERENCE MANUAL PAGE 287:
 *  - TIM1
 * 
 * REFERENCE MANUAL PAGE 352:
 *  - TIM2 -> TIM5

 * REFERENCE MANUAL PAGE 397:
 *  - TIM9 -> TIM11
 */ 
struct timer_regs
{
  hw_reg CR1;   /* Timer control register 1              */
  hw_reg CR2;   /* Timer control register 2              */
  hw_reg SMCR;  /* Timer slave mode control register     */
  hw_reg DIER;  /* Timer DMA/interrupt enable register   */
  hw_reg SR;    /* Timer status register                 */
  hw_reg EGR;   /* Timer event generation register       */
  hw_reg CCMR1; /* Timer capture/compare mode register 1 */
  hw_reg CCMR2; /* Timer capture/compare mode register 2 */
  hw_reg CCER;  /* Timer capture/compare enable register */
  hw_reg CNT;   /* Timer counter register                */
  hw_reg PSC;   /* Timer prescaler                       */
  hw_reg ARR;   /* Timer auto-reload register            */
  hw_reg RCR;   /* Timer repetition counter register     */
  hw_reg CCR1;  /* Timer capture/compare register 1      */
  hw_reg CCR2;  /* Timer capture/compare register 2      */
  hw_reg CCR3;  /* Timer capture/compare register 3      */
  hw_reg CCR4;  /* Timer capture/compare register 4      */
  hw_reg BDTR;  /* Timer break and dead-time register    */
  hw_reg DCR;   /* Timer DMA control register            */
  hw_reg DMAR;  /* Timer DMA address for full transfer   */
  hw_reg OR;    /* Timer option register                 */
};


#define _TIM1  ((struct timer_regs*) TIM1_BASE)
#define _TIM3  ((struct timer_regs*) TIM3_BASE)
#define _TIM4  ((struct timer_regs*) TIM4_BASE)
#define _TIM2  ((struct timer_regs*) TIM2_BASE)
#define _TIM5  ((struct timer_regs*) TIM5_BASE)
#define _TIM9  ((struct timer_regs*) TIM9_BASE)
#define _TIM10 ((struct timer_regs*) TIM10_BASE)
#define _TIM11 ((struct timer_regs*) TIM11_BASE)

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_TIMERS */