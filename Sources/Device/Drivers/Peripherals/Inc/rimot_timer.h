
#ifndef RIMOT_MCU_TIMERS
#define RIMOT_MCU_TIMERS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */


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



#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_TIMERS */
