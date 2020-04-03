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


/* 
 * FOR NOTES ON INJECTED VS REGULAR CONVERSION GROUPS,
 * SEE https://embedds.com/introducing-to-stm32-adc-programming-part1/
 */


typedef enum
{
    ADC_RES_12,
    ADC_RES_10,
    ADC_RES_8,
    ADC_RES_6,
}   ADC_RES_t;


typedef enum
{
    ADC_SAMPLE_3,
    ADC_SAMPLE_15,
    ADC_SAMPLE_28,
    ADC_SAMPLE_56,
    ADC_SAMPLE_84,
    ADC_SAMPLE_112,
    ADC_SAMPLE_144,
    ADC_SAMPLE_480,
}   ADC_SAMPLE_t;


/* The ADC Channel */
typedef enum
{
    ADC_CHANNEL0,
    ADC_CHANNEL1,
    ADC_CHANNEL2,
    ADC_CHANNEL3,
    ADC_CHANNEL4,
    ADC_CHANNEL5,
    ADC_CHANNEL6,
    ADC_CHANNEL7,
    ADC_CHANNEL8,
    ADC_CHANNEL9,
    ADC_CHANNEL10,
    ADC_CHANNEL11,
    ADC_CHANNEL12,
    ADC_CHANNEL13,
    ADC_CHANNEL14,
    ADC_CHANNEL15,
    ADC_CHANNEL16,
    ADC_CHANNEL17,
    ADC_CHANNEL18,
}   ADC_CHANNEL_t;

/**
 * @fn adcSetRes 
 * @brief set the resolution of the adc peripheral.
 * 
 * @param res one of ADC_RES_t
 * @return mcu_word if success, returns 0, else, res is defaulted
 * to 12 bits and !0 is returned.
 */
mcu_word adcSetRes(ADC_RES_t res);



/**
 * @fn adcSetSampleTime
 * @brief configure the sampling cycles for a given adc channel
 * 
 * @param smp one of ADC_SAMPLE_t
 * @param channel one of ADC_CHANNEL_t
 * @return mcu_word 
 */
mcu_word adcSetSampleTime(ADC_SAMPLE_t smp, ADC_CHANNEL_t channel);



/**
 * @fn adcGetConvData
 * @brief returns the data in the ADC DR
 * @return mcu_short the value from the ADC :: DR
 */
mcu_short adcGetConvData(void);
















/**
 * @fn adc_LL_init
 * @brief Calibrates the ADC peripheral
 */
void adc_LL_init(void);


/**
 * @fn adcCheckOverrun
 * @brief  returns the value of the ADC overrun bit
 * @return int : value of ADC_SR::overrun bit
 */
mcu_word adcCheckOverrun(void);

/**
 * @fn adcCheckStart
 * @brief returns the value of the ADC regular channel start bit
 * @return int : value of the bit
 */
mcu_word adcCheckStart(void);


mcu_word adcCheckJstart(void);

mcu_word adcCheckJEOC(void);

mcu_word adcCheckAwd(void);

mcu_word adcCheckEOC(void);









#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC */