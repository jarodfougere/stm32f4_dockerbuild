#ifndef RIMOT_ADC
#define RIMOT_ADC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */ 

#include "rimot_peripheral_regs.h"

/* On this microcontroller there is only a single adc peripheral instance */
#define NUM_ADC_INSTANCES 1


struct adc_common
{
    mcu_word SR;   /* common status register                    */
    mcu_word CR;   /* common config register                    */
    mcu_word DR;   /* common data register.                     */
};                 /* only used in dual/triple/interleaved mode.*/

struct adc_periph
{
    hw_reg SR;           /* status register                       */
    hw_reg CR1;          /* control register1                     */
    hw_reg CR2;          /* control register2                     */
    hw_reg SMPR1;        /* sample time reigster 1                */
    hw_reg SMPR2;        /* sample time register 2                */
    hw_reg JOFR[4];      /* injected channel offset registers     */
    hw_reg HTR;          /* watchdog high threshhold register     */
    hw_reg LTR;          /* watchdog low threshhold register      */
    hw_reg SQR[3];       /* regular conversion sequence registers */
    hw_reg JSQR;         /* injected conversion sequence register */
    hw_reg JDR[4];       /* injected conversion data registers    */
    hw_reg DR;           /* conversion data register              */
};




#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC */