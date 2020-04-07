#ifndef RIMOT_ANALOG_MEASUREMENTS
#define RIMOT_ANALOG_MEASUREMENTS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

typedef int16_t adcVal; /* 12 bit adc means 16 bits can hold the value */
typedef float   voltVal; 

#define VALID_ANALOG_MEASUREMENT   (0)
#define INVALID_ANALOG_MEASUREMENT (1)


/* Voltage reference */
#define ADC_VREF_HI    ((voltVal)(3.000)) /* Positive reference voltage */
#define ADC_VREF_LO    ((voltVal)(0.000)) /* Negative reference voltage */
#define ADC_VOLT_RANGE ((voltVal)(ADC_VREF_HI - ADC_VREF_LO))

/* Bit scaling */
#define ADC_BIT_MIN    ((adcVal)(0x0000)) /* This should almost always be 0 */
#define ADC_BIT_MAX    ((adcVal)(0x0FFF)) /* 12-bits */
#define ADC_BIT_RANGE  ((adcVal)(ADC_BIT_MAX - ADC_BIT_MIN))

#define VOLTS_TO_ADC(val) ((adcVal)((val)*((ADC_BIT_RANGE)/(ADC_VOLT_RANGE))))
#define ADC_TO_VOLTS(adc) ((voltVal)((adc)*((ADC_VOLT_RANGE)/(ADC_BIT_RANGE))))


struct analog_measurement
{
    adcVal max;     /* maximum conversion value in the data window   */
    adcVal min;     /* minimum conversion value in the data window   */
    adcVal avg;     /* average conversion value in the data window   */
    adcVal median;  /* median conversion value in the data window    */
    adcVal Navg;    /* num samples evaluated in the data window      */
};


struct adc_stats_diffval
{
    int16_t max;    /* maximum return loss in data window, units ADC  */
    int16_t min;    /* minimum return loss in data window, units ADC  */
    int16_t avg;    /* average return loss in data window, units ADC  */
    int16_t median; /* median return loss in data window              */
    int16_t Navg;   /* number of samples evaluated in the data window */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ANALOG_MEASUREMENTS */