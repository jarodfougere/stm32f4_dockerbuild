#ifndef RIMOT_ADC
#define RIMOT_ADC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */ 

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

#define ADC1_BASE        (APB2PERIPH_BASE + 0x2000UL)
#define ADC1_COMMON_BASE (APB2PERIPH_BASE + 0x2300UL)

struct adc_common_regs
{
    hw_reg SR;   /* common status register                    */
    sw_reg CR;   /* common config register                    */
    hw_reg DR;   /* common data register.                     */
};                 /* only used in dual/triple/interleaved mode.*/

struct adc_regs
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

#define ADC1                ((struct adc_regs*) ADC1_BASE)
#define ADC1_COMMON         ((struct adc_common_regs*) ADC1_COMMON_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC */