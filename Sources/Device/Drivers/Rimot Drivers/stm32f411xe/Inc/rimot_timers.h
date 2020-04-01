
#ifndef RIMOT_MCU_TIMERS
#define RIMOT_MCU_TIMERS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

/* TIMER PERIPHERAL REGISTER OVERLAY */
struct timer_reg
{
  hw_reg CR1;   /* timer control register 1              */
  hw_reg CR2;   /* timer control register 2              */
  hw_reg SMCR;  /* timer slave mode control register     */
  hw_reg DIER;  /* timer DMA/interrupt enable register   */
  hw_reg SR;    /* timer status register                 */
  hw_reg EGR;   /* timer event generation register       */
  hw_reg CCMR1; /* timer capture/compare mode register 1 */
  hw_reg CCMR2; /* timer capture/compare mode register 2 */
  hw_reg CCER;  /* timer capture/compare enable register */
  hw_reg CNT;   /* timer counter register                */
  hw_reg PSC;   /* timer prescaler                       */
  hw_reg ARR;   /* timer auto-reload register            */
  hw_reg RCR;   /* timer repetition counter register     */
  hw_reg CCR1;  /* timer capture/compare register 1      */
  hw_reg CCR2;  /* timer capture/compare register 2      */
  hw_reg CCR3;  /* timer capture/compare register 3      */
  hw_reg CCR4;  /* timer capture/compare register 4      */
  hw_reg BDTR;  /* timer break and dead-time register    */
  hw_reg DCR;   /* timer DMA control register            */
  hw_reg DMAR;  /* timer DMA address for full transfer   */
  hw_reg OR;    /* timer option register                 */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_TIMERS */