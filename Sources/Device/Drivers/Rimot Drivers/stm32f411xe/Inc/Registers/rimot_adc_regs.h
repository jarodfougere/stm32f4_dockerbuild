#ifndef RIMOT_ADC
#define RIMOT_ADC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */ 

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define ADC1_BASE        (APB2PERIPH_BASE + 0x2000UL)
#define ADC1_COMMON_BASE (APB2PERIPH_BASE + 0x2300UL)

struct adc_common_regs
{
    hw_reg SR;   /* common status register                    */
    sw_reg CR;   /* common config register                    */
    hw_reg DR;   /* common data register.                     */
};               /* only used in dual/triple/interleaved mode.*/

struct adc_regs
{
    hw_reg SR;           /* Status register                       */
    hw_reg CR1;          /* Control register1                     */
    hw_reg CR2;          /* Control register2                     */
    hw_reg SMPR1;        /* Sample time reigster 1                */
    hw_reg SMPR2;        /* Sample time register 2                */
    hw_reg JOFR[4];      /* Injected channel offset registers     */
    hw_reg HTR;          /* Watchdog high threshhold register     */
    hw_reg LTR;          /* Watchdog low threshhold register      */
    hw_reg SQR[3];       /* Regular conversion sequence registers */
    hw_reg JSQR;         /* Injected conversion sequence register */
    hw_reg JDR[4];       /* Injected conversion data registers    */
    hw_reg DR;           /* Conversion data register              */
};

#define _ADC1                ((struct adc_regs*) ADC1_BASE)
#define _ADC1_COMMON         ((struct adc_common_regs*) ADC1_COMMON_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC */