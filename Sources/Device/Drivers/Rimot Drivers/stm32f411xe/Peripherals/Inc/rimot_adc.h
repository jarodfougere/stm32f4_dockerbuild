#ifndef RIMOT_ADC
#define RIMOT_ADC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */ 

#include "rimot_register_field_sizes.h"

/* 
 * FOR NOTES ON INJECTED VS REGUAR CONVERSION GROUPS,
 * SEE https://embedds.com/introducing-to-stm32-adc-programming-part1/
 */

/* The ADC resolution */
typedef enum
{   
    ADC_RES_12 = 0U,
    ADC_RES_10 = 1U,
    ADC_RES_8  = 2U,
    ADC_RES_6  = 3U,
}   ADC_RES_t;


/* The number of cycles to sample a given channel for */
typedef enum
{   
    ADC_SAMPLE_3   = 0U,
    ADC_SAMPLE_15  = 1U,
    ADC_SAMPLE_28  = 2U,
    ADC_SAMPLE_56  = 3U,
    ADC_SAMPLE_84  = 4U,
    ADC_SAMPLE_112 = 5U,
    ADC_SAMPLE_144 = 6U,
    ADC_SAMPLE_480 = 7U,
}   ADC_SAMPLE_t;


typedef enum
{
    ADC_ISR_overrun,
    ADC_ISR_analog_watchdog,
    ADC_ISR_injected_end_of_conversion,
    ADC_ISR_regular_end_of_conversion,
}   ADC_ISR_t;


typedef enum
{
    ADC_TRIG_none    = 0U,
    ADC_TRIG_rising  = 1U,
    ADC_TRIG_falling = 2U,
    ADC_TRIG_edge    = 3U,
}   ADC_TRIG_t;


typedef enum
{
    ADC_CHANNEL_GROUPTYPE_regular,
    ADC_CHANNEL_GROUPTYPE_injected,
}   ADC_CHANNEL_GROUPTYPE_t;


typedef enum
{
    ADC_END_OF_SEQUENCE_TRIGGER_TYPE_each_conversion,
    ADC_END_OF_SEQUENCE_TRIGGER_TYPE_each_sequence,
}   ADC_END_OF_SEQUENCE_TRIGGER_TYPE_t;


typedef enum
{
    ADC_PRESCALER_2 = 0U,
    ADC_PRESCALER_4 = 1U,
    ADC_PRESCALER_6 = 2U,
    ADC_PRESCALER_8 = 3U
}   ADC_PRESCALER_t;


typedef enum
{
    ADC_SEQ_CONV_1,
    ADC_SEQ_CONV_2,
    ADC_SEQ_CONV_3,
    ADC_SEQ_CONV_4,
    ADC_SEQ_CONV_5,
    ADC_SEQ_CONV_6,
    ADC_SEQ_CONV_7,
    ADC_SEQ_CONV_8,
    ADC_SEQ_CONV_9,
    ADC_SEQ_CONV_10,
    ADC_SEQ_CONV_11,
    ADC_SEQ_CONV_12,
    ADC_SEQ_CONV_13,
    ADC_SEQ_CONV_14,
    ADC_SEQ_CONV_15,
    ADC_SEQ_CONV_16,
}   ADC_SEQ_CONV_t;

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
mcu_word adcSetSampleTime(ADC_SAMPLE_t smp, MCUPIN_t pin);


/**
 * @fn adcGetConvData
 * @brief returns the data in the ADC DR
 * @return mcu_word the value from the ADC :: DR
 */
mcu_word adcGetConvData(void);


/**
 * @fn adcPinConfig
 * @brief Attempts to configure an ADC channel
 * @param pin the pin alias to configure
 * @return mcu_word 0 on success, 1 on failure
 */
mcu_word adcChannelConfig(MCUPIN_t pin, ADC_SAMPLE_t smp);


/**
 * @fn adcDisable
 * @brief cuts power to the adc peripheral
 */
void adcDisable(void);


/**
 * @fn adcEnable
 * @brief Provides power to the adc peripheral
 */
void adcEnable(void);


/**
 * @fn adcCheckOverrun
 * @brief  checks the value of the conversion overrun flag in the ADC
 * status register
 * @return mcu_word : value of ADC_SR::overrun bit
 */
mcu_word adcCheckOverrun(void);

/**
 * @fn adcCheckStart
 * @brief checks the status of ADC ongoing regular conversion flag in the
 * status register
 * @return mcu_word : value of ADC::SR::STRT bit
 */
mcu_word adcCheckStart(void);


/**
 * @fn adcCheckJstart
 * @brief Checks the status of the ADC ongoing injected conversion flag in 
 * the status register
 * 
 * @return mcu_word : value of ADC::SR::JSTRT bit
 */
mcu_word adcCheckJstart(void);


/**
 * @fn adcCheckJEOC
 * @brief Checks the value of ADC injected end of sequence flag in status
 * register
 * 
 * @return mcu_word : value of ADC::SR::JEOC bit
 */
mcu_word adcCheckJEOC(void);


/**
 * @fn adcCheckAwd
 * @brief Checks the value of the ADC analog watchdog status bit
 * 
 * @return mcu_word the value of ADC::SR::AWD
 */
mcu_word adcCheckAwd(void);


/**
 * @fn adcCheckEOC
 * @brief Checks the value of ADC end of sequence flag in status register
 * 
 * @return mcu_word value of ADC::SR::EOC
 */
mcu_word adcCheckEOC(void);


/**
 * @fn adcEnableInterrupt 
 * @brief enables the corresponding interrupt in the the ADC
 * control registers
 * 
 * @param interrupt one of: ADC_ISR_t
 */
void adcEnableInterrupt(ADC_ISR_t interrupt);


/**
 * @fn adcDisableInterrupt
 * @brief disables the corresponding interrupt in the the ADC
 * control registers
 * 
 * @param interrupt one of: ADC_ISR_t
 */
void adcDisableInterrupt(ADC_ISR_t interrupt);



void adcStartConversion(ADC_CHANNEL_GROUPTYPE_t group_type);



void adcSetTriggerConfig(ADC_TRIG_t triggermode);



void adcSetSequenceTriggerType(ADC_END_OF_SEQUENCE_TRIGGER_TYPE_t trigger_type);



void adcEnableDMA(void);


void adcDisbleDMA(void);


void adcSetConvSeqElement(MCUPIN_t pin, ADC_SEQ_CONV_t pos);


/**
 * @fn adcSetConversionSequenceLength
 * @brief set the number of consecutive channels to be converted when a 
 * sequence conversion group is started by software
 * 
 * @param len the number of conversions. must be > 1.
 */
void adcSetConversionSequenceLength(mcu_word len);



void adcSetPrescaler(ADC_PRESCALER_t ps_val);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC */