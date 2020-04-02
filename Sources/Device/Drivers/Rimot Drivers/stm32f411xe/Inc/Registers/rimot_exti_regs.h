#ifndef RIMOT_EXTERNAL_INTERRUPT
#define RIMOT_EXTERNAL_INTERRUPT
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

#define EXTI_BASE (APB2PERIPH_BASE + 0x3C00UL)

/* PAGE 208, REFERENCE MANUAL */
struct exti_regs
{
    hw_reg IMR;   /* EXTI Interrupt mask reg         | offset: 0x00    */
    hw_reg EMR;   /* EXTI Event mask reg             | offset: 0x04    */
    hw_reg RTSR;  /* EXTI Rising trig selection reg  | offset: 0x08    */ 
    hw_reg FTSR;  /* EXTI Falling trig selection reg | offset: 0x0C    */ 
    hw_reg SWIER; /* EXTI SW interrupt event reg     | offset: 0x10    */ 
    hw_reg PR;    /* EXTI Pending reg,               | offset: 0x14    */
};

#define EXTI ((struct exti_regs*) EXTI_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_EXTERNAL_INTERRUPT */