#ifndef RIMOT_ADC
#define RIMOT_ADC
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */

#include "rimot_pin_aliases.h"
#include "rimot_register_padding.h"

    typedef int16_t adcVal; /* 12 bit adc means 16 bits can hold the value */
    typedef float voltVal;

#define VALID_ANALOG_MEASUREMENT (0)
#define INVALID_ANALOG_MEASUREMENT (1)

/* Voltage reference */
#define ADC_VREF_HI ((voltVal)(3.000)) /* Positive reference voltage */
#define ADC_VREF_LO ((voltVal)(0.000)) /* Negative reference voltage */
#define ADC_VOLT_RANGE ((voltVal)(ADC_VREF_HI - ADC_VREF_LO))

/* Bit scaling */
#define ADC_BIT_MIN ((adcVal)(0x0000)) /* This should almost always be 0 */
#define ADC_BIT_MAX ((adcVal)(0x0FFF)) /* 12-bits */
#define ADC_BIT_RANGE ((adcVal)(ADC_BIT_MAX - ADC_BIT_MIN))

#define VOLTS_TO_ADC(val) ((adcVal)((val) * ((ADC_BIT_RANGE) / (ADC_VOLT_RANGE))))
#define ADC_TO_VOLTS(adc) ((voltVal)((adc) * ((ADC_VOLT_RANGE) / (ADC_BIT_RANGE))))

    /* The ADC resolution */
    typedef enum
    {
        ADC_RES_12 = 0U,
        ADC_RES_10 = 1U,
        ADC_RES_8 = 2U,
        ADC_RES_6 = 3U,
    } ADC_RES_t;

    /* The number of cycles to sample a given channel for */
    typedef enum
    {
        ADC_SAMPLE_3 = 0U,
        ADC_SAMPLE_15 = 1U,
        ADC_SAMPLE_28 = 2U,
        ADC_SAMPLE_56 = 3U,
        ADC_SAMPLE_84 = 4U,
        ADC_SAMPLE_112 = 5U,
        ADC_SAMPLE_144 = 6U,
        ADC_SAMPLE_480 = 7U,
    } ADC_SAMPLE_t;

    typedef enum
    {
        ADC_ISR_overrun,
        ADC_ISR_analog_watchdog,
        ADC_ISR_injected_end_of_conversion,
        ADC_ISR_regular_end_of_conversion,
    } ADC_ISR_t;

    typedef enum
    {
        ADC_TRIG_none = 0U,
        ADC_TRIG_rising = 1U,
        ADC_TRIG_falling = 2U,
        ADC_TRIG_edge = 3U,
    } ADC_TRIG_t;

    typedef enum
    {
        ADC_GROUPTYPE_regular,
        ADC_GROUPTYPE_injected,
    } ADC_GROUPTYPE_t;

    typedef enum
    {
        ADC_END_OF_SEQUENCE_TRIGGER_TYPE_each_conversion,
        ADC_END_OF_SEQUENCE_TRIGGER_TYPE_each_sequence,
    } ADC_END_OF_SEQUENCE_TRIGGER_TYPE_t;

    typedef enum
    {
        ADC_PRESCALER_2 = 0U,
        ADC_PRESCALER_4 = 1U,
        ADC_PRESCALER_6 = 2U,
        ADC_PRESCALER_8 = 3U
    } ADC_PRESCALER_t;

    typedef enum
    {
        ADC_SEQ_POS_1,
        ADC_SEQ_POS_2,
        ADC_SEQ_POS_3,
        ADC_SEQ_POS_4,
        ADC_SEQ_POS_5,
        ADC_SEQ_POS_6,
        ADC_SEQ_POS_7,
        ADC_SEQ_POS_8,
        ADC_SEQ_POS_9,
        ADC_SEQ_POS_10,
        ADC_SEQ_POS_11,
        ADC_SEQ_POS_12,
        ADC_SEQ_POS_13,
        ADC_SEQ_POS_14,
        ADC_SEQ_POS_15,
        ADC_SEQ_POS_16,
    } ADC_SEQ_POS_t;

    struct analog_measurement
    {
        adcVal max;    /* maximum conversion value in the data window   */
        adcVal min;    /* minimum conversion value in the data window   */
        adcVal avg;    /* average conversion value in the data window   */
        adcVal median; /* median conversion value in the data window    */
        adcVal Navg;   /* num samples evaluated in the data window      */
    };

    struct adc_stats_diffval
    {
        adcVal max;    /* maximum return loss in data window, units ADC  */
        adcVal min;    /* minimum return loss in data window, units ADC  */
        adcVal avg;    /* average return loss in data window, units ADC  */
        adcVal median; /* median return loss in data window              */
        adcVal Navg;   /* number of samples evaluated in the data window */
    };

    /**
 * @fn adcSetRes 
 * @brief set the resolution of the adc peripheral.
 * 
 * @param res one of ADC_RES_t
 * @return uint32_t if success, returns 0, else, res is defaulted
 * to 12 bits and !0 is returned.
 */
    uint32_t adcSetRes(ADC_RES_t res);

    /**
 * @fn adcSetSampleTime
 * @brief configure the sampling cycles for a given adc channel
 * 
 * @param smp one of ADC_SAMPLE_t
 * @param channel one of ADC_CHANNEL_t
 * @return uint32_t 
 */
    uint32_t adcSetSampleTime(ADC_SAMPLE_t smp, MCUPIN_t pin);

    /**
 * @fn adcGetConvData
 * @brief returns the data in the ADC DR
 * @return uint32_t the value from the ADC :: DR
 */
    uint32_t adcGetConvData(void);

    /**
 * @fn adcPinConfig
 * @brief Attempts to configure an ADC channel
 * @param pin the pin alias to configure
 * @return uint32_t 0 on success, 1 on failure
 */
    uint32_t adcChannelConfig(MCUPIN_t pin, ADC_SAMPLE_t smp);

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
 * @return uint32_t : value of ADC_SR::overrun bit
 */
    uint32_t adcCheckOverrun(void);

    /**
 * @fn adcCheckStart
 * @brief checks the status of ADC ongoing regular conversion flag in the
 * status register
 * @return uint32_t : value of ADC::SR::STRT bit
 */
    uint32_t adcCheckStart(void);

    /**
 * @fn adcCheckJstart
 * @brief Checks the status of the ADC ongoing injected conversion flag in 
 * the status register
 * 
 * @return uint32_t : value of ADC::SR::JSTRT bit
 */
    uint32_t adcCheckJstart(void);

    /**
 * @fn adcCheckJEOC
 * @brief Checks the value of ADC injected end of sequence flag in status
 * register
 * 
 * @return uint32_t : value of ADC::SR::JEOC bit
 */
    uint32_t adcCheckJEOC(void);

    /**
 * @fn adcCheckAwd
 * @brief Checks the value of the ADC analog watchdog status bit
 * 
 * @return uint32_t the value of ADC::SR::AWD
 */
    uint32_t adcCheckAwd(void);

    /**
 * @fn adcCheckEOC
 * @brief Checks the value of ADC end of sequence flag in status register
 * 
 * @return uint32_t value of ADC::SR::EOC
 */
    uint32_t adcCheckEOC(void);

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

    void adcStartConversion(ADC_GROUPTYPE_t group_type);

    void adcSetTriggerConfig(ADC_TRIG_t triggermode);

    void adcSetSequenceTriggerType(ADC_END_OF_SEQUENCE_TRIGGER_TYPE_t trigger_type);

    void adcEnableDMA(void);

    void adcDisbleDMA(void);

    void adcSetConvSeqPin(MCUPIN_t pin, ADC_GROUPTYPE_t group, uint32_t pos);

    void adcSetPrescaler(ADC_PRESCALER_t ps_val);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC */
