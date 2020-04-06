/**
 * @file rimot_adc.c
 * @author Carl Mattatall
 * @brief  This source module profides a low level "driver"
 * for the adc peripheral
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#include "rimot_adc.h"
#include "rimot_adc_register_masks.h"

/* Required externals */
#include "rimot_rcc.h"
#include "rimot_gpio.h"

#if defined(STM32F411VE)
#elif defined(STM32F411RE)
#else
#error NO DEFINITION FOR STM32F411xE packae
#endif /* PACKAGE SELECTION */

struct adc_common_regs
{
    hw_reg SR; /* common status register                    */
    sw_reg CR; /* common config register                    */
    hw_reg DR; /* common data register.                     */
};             /* only used in dual/triple/interleaved mode.*/
#define ADC1_COMMON ((struct adc_common_regs *)ADC1_COMMON_BASE)

struct adc_regs
{
    hw_reg SR;      /* Status register                       */
    hw_reg CR1;     /* Control register1                     */
    hw_reg CR2;     /* Control register2                     */
    hw_reg SMPR1;   /* Sample time reigster 1                */
    hw_reg SMPR2;   /* Sample time register 2                */
    hw_reg JOFR[4]; /* Injected channel offset registers     */
    hw_reg HTR;     /* Watchdog high threshhold register     */
    hw_reg LTR;     /* Watchdog low threshhold register      */
    hw_reg SQR[3];  /* Regular conversion sequence registers */
    hw_reg JSQR;    /* Injected conversion sequence register */
    hw_reg JDR[4];  /* Injected conversion data registers    */
    hw_reg DR;      /* Conversion data register              */
};
#define ADC1 ((struct adc_regs *)ADC1_BASE)

static const mcu_word adc_channel_pin_map[] =
#if defined(STM32F411VE)
{
    [ADC_CHANNEL0] = MCUPIN_PA0,
    [ADC_CHANNEL1] = MCUPIN_PA1,
    [ADC_CHANNEL2] = MCUPIN_PA2,
    [ADC_CHANNEL3] = MCUPIN_PA3,
    [ADC_CHANNEL4] = MCUPIN_PA4,
    [ADC_CHANNEL5] = MCUPIN_PA5,
    [ADC_CHANNEL6] = MCUPIN_PA6,
    [ADC_CHANNEL7] = MCUPIN_PA7,
    [ADC_CHANNEL8] = MCUPIN_PB8,
    [ADC_CHANNEL9] = MCUPIN_PB9,
    [ADC_CHANNEL10] = MCUPIN_PC0,
    [ADC_CHANNEL11] = MCUPIN_PC1,
    [ADC_CHANNEL12] = MCUPIN_PC2,
    [ADC_CHANNEL13] = MCUPIN_PC3,
    [ADC_CHANNEL14] = MCUPIN_PC4,
    [ADC_CHANNEL15] = MCUPIN_PC5,
};

#elif defined(STM32F411RE)
#error CARL YOU FORGOT TO DEFINE NUM_ADC_CHANNELS FOR THE PRODUCTION MCU PACKAGE
    {0};
#else
    {0};
/* NEED TO MAKE ARRAY EMPTY SO I ACTUALLY GET THE DESIRED ERROR DIRECTIVE */
#error NO DEFINITION FOR STM32F411xE packae
#endif /* PACKAGE SELECTION */

void adcEnable(void)
{
    ADC1->CR2 |= CR2_ADON;
}

void adcDisable(void)
{
    ADC1->CR2 &= ~CR2_ADON;
}



mcu_word adcCheckOverrun(void)
{
    return !!(ADC1->SR & SR_OVR);
}

mcu_word adcCheckStart(void)
{
    return !!(ADC1->SR & SR_STRT);
}

mcu_word adcCheckJstart(void)
{
    return !!(ADC1->SR & SR_JSTRT);
}

mcu_word adcCheckJEOC(void)
{
    return !!(ADC1->SR & SR_JEOC);
}

mcu_word adcCheckEOC(void)
{
    return !!(ADC1->SR & SR_EOC);
}

mcu_word adcCheckAwd(void)
{
    return !!(ADC1->SR & SR_AWD);
}

mcu_word adcGetConvData(void)
{
    return ADC1->DR;
}

mcu_word adcSetRes(ADC_RES_t res)
{
    /* Wipe all 4 res bits */
    /* When res bits are zeroed, 12bit res is dflt */
    ADC1->CR1 &= CR1_RES;
    switch (res)
    {
    case ADC_RES_12:
    case ADC_RES_10:
    case ADC_RES_8:
    case ADC_RES_6:
        ADC1->CR1 |= res << CR1_RES_POS;
        return 0;
        break;
    default:
#if !defined(NDEBUG)
        while (1)
        {
            /* invalid value. hang here */
        }
#else
        /* 12 bit resolution is dflt but return 1
            so caller knows they made a mistake */
        return 1;
        break;
#endif /* DEBUG BUILD */
    }
}

mcu_word adcChannelConfig(ADC_CHANNEL_t ch, ADC_SAMPLE_t smp)
{
    mcu_word status = 0;
    mcu_word smp_val = (mcu_word)smp; /* Cast enum to unsigned */
    mcu_word channel = (mcu_word)ch;  /* Cast enum to unsigned */
    switch (ch)
    {
    /* Valid Channel Values */
    case ADC_CHANNEL0:
    case ADC_CHANNEL1:
    case ADC_CHANNEL2:
    case ADC_CHANNEL3:
    case ADC_CHANNEL4:
    case ADC_CHANNEL5:
    case ADC_CHANNEL6:
    case ADC_CHANNEL7:
    case ADC_CHANNEL8:
    case ADC_CHANNEL9:
    case ADC_CHANNEL10:
    case ADC_CHANNEL11:
    case ADC_CHANNEL12:
    case ADC_CHANNEL13:
    case ADC_CHANNEL14:
    case ADC_CHANNEL15:
        switch (smp)
        {
        /* Valid Sampling options */
        case ADC_SAMPLE_3:
        case ADC_SAMPLE_15:
        case ADC_SAMPLE_28:
        case ADC_SAMPLE_56:
        case ADC_SAMPLE_84:
        case ADC_SAMPLE_112:
        case ADC_SAMPLE_144:
        case ADC_SAMPLE_480:
            gpio_setPinMode(GPIO_MODE_analog, adc_channel_pin_map[ch]);
            /* Register selection */

            /* CHANNELS 0 -> 9 IN SMPR1, 10 -> 18 IN SMPR2 */
            if (ch > 9)
            {
                /* Clear previous sample config bits */
                ADC1->SMPR1 &= ~(7 << (3 * channel));

                /* Set sample config bits */
                ADC1->SMPR1 |= (smp_val << (3 * channel));
            }
            else
            {
                /* Clear previous sample config bits */
                ADC1->SMPR2 &= ~(7 << (3 * (channel - 9)));

                /* Set sample config bits */
                ADC1->SMPR2 |= (smp_val << (3 * (channel - 9)));
            }
            break;
        default:
            status = 1;
            /* Don't touch the bits */
#if !defined(NDEBUG)
            while (1)
                ; /* hang */
#else
            break;
#endif
        }
        break;
    default:
        status = 1;
#if !defined(NDEBUG)
        while (1)
            ;
#else
        break;
#endif
    }
    return status;
}

void adcEnableInterrupt(ADC_ISR_t interrupt)
{
    switch (interrupt)
    {
    case ADC_ISR_analog_watchdog:
        ADC1->CR1 |= CR1_AWDIE;
        break;
    case ADC_ISR_injected_end_of_conversion:
        ADC1->CR1 |= CR1_JEOCIE;
        break;
    case ADC_ISR_overrun:
        ADC1->CR1 |= CR1_OVRIE;
        break;
    case ADC_ISR_regular_end_of_conversion:
        ADC1->CR1 |= CR1_EOCIE;
        break;
    default:
#if !defined(NDEBUG)
        while (1)
        {
            /* Hang forever */
        }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}

void adcDisableInterrupt(ADC_ISR_t interrupt)
{
    switch (interrupt)
    {
    case ADC_ISR_analog_watchdog:
        ADC1->CR1 &= ~CR1_AWDIE;
        break;
    case ADC_ISR_injected_end_of_conversion:
        ADC1->CR1 &= ~CR1_JEOCIE;
        break;
    case ADC_ISR_overrun:
        ADC1->CR1 &= ~CR1_OVRIE;
        break;
    case ADC_ISR_regular_end_of_conversion:
        ADC1->CR1 &= ~CR1_EOCIE;
        break;
    default:
#if !defined(NDEBUG)
        while (1)
        {
            /* Hang forever */
        }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}



void adcStartConversion(ADC_CHANNEL_GROUPTYPE_t group_type)
{   
    switch(group_type)
    {
    case ADC_CHANNEL_GROUPTYPE_regular:
        /* If a conversion has not been started */
        while(ADC1->CR2 & CR2_SWSTART);
        ADC1->CR2 |= CR2_SWSTART;
    break;
    case ADC_CHANNEL_GROUPTYPE_injected:
        while(ADC1->CR2 & CR2_JSWSTART);
        ADC1->CR2 |= CR2_JSWSTART;
    break;
    default:
#if !defined(NDEBUG)
    while(1)
    {
        /* HANG */
    }
#else
    break;
#endif  /* DEBUG BUILD */

    }
}



void adcSetTriggerConfig(ADC_TRIG_t triggermode)
{   
    /* Clear existing configuration of the trigger bits */
    ADC1->CR2 &= ~CR2_EXTEN;
    switch(triggermode)
    {
    case ADC_TRIG_edge:
    case ADC_TRIG_falling:
    case ADC_TRIG_rising:
    case ADC_TRIG_none:
        /* Set the new configuration of the trigger bits */
        ADC1->CR2 |= triggermode << CR2_EXTEN_POS;
    break;
    default:
#if !defined(NDEBUG)
        while(1)
        {
            /* HANG */
        }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}



void adcSetSequenceTriggerType(ADC_END_OF_SEQUENCE_TRIGGER_TYPE_t trigger_type)
{   
    ADC1->CR2 &= ~CR2_EOCS; /* clear EOCS bits */
    switch(trigger_type)
    {
        case ADC_END_OF_SEQUENCE_TRIGGER_TYPE_each_conversion:
            /* ADC::SR::EOC is set after every conversion in a sequence */
            ADC1->CR2 |= CR2_EOCS; 
        break;
        case ADC_END_OF_SEQUENCE_TRIGGER_TYPE_each_sequence:
            /* We've already cleared the bits to this configuration */
        break;
        default:
        #if !defined(NDEBUG)
        while(1)
        {
            /* HANG */
        }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}


void adcEnableDMA(void)
{
    ADC1->CR2 |= CR2_DDS;
    ADC1->CR2 |= CR2_DMA;
}

void adcDisbleDMA(void)
{
    ADC1->CR2 &= ~CR2_DDS;
    ADC1->CR2 &= ~CR2_DMA;   
}


/* SEE PAGES 234, 235, 236 REFERENCE MANUAL */
static const struct 
{
    mcu_word seqRegIdx;
    mcu_word bitPos;
}   seqRegLookupTable[] = 
{
    [1]  = {.bitPos = 0,  .seqRegIdx = 2},
    [2]  = {.bitPos = 5,  .seqRegIdx = 2},
    [3]  = {.bitPos = 10, .seqRegIdx = 2},
    [4]  = {.bitPos = 15, .seqRegIdx = 2},
    [5]  = {.bitPos = 20, .seqRegIdx = 2},
    [6]  = {.bitPos = 25, .seqRegIdx = 2},
    [7]  = {.bitPos = 0,  .seqRegIdx = 1},
    [8]  = {.bitPos = 5,  .seqRegIdx = 1},
    [9]  = {.bitPos = 10, .seqRegIdx = 1},
    [10] = {.bitPos = 15, .seqRegIdx = 1},
    [11] = {.bitPos = 20, .seqRegIdx = 1},
    [12] = {.bitPos = 25, .seqRegIdx = 1},
    [13] = {.bitPos = 0,  .seqRegIdx = 0},
    [14] = {.bitPos = 5,  .seqRegIdx = 0},
    [15] = {.bitPos = 10, .seqRegIdx = 0},
    [16] = {.bitPos = 15, .seqRegIdx = 0},
};


void adcSetConvSeqElement(ADC_CHANNEL_t channel, mcu_word pos)
{   
    /* Validate the channel */
    switch(channel)
    {
    case ADC_CHANNEL0:
    case ADC_CHANNEL1:
    case ADC_CHANNEL2:
    case ADC_CHANNEL3:
    case ADC_CHANNEL4:
    case ADC_CHANNEL5:
    case ADC_CHANNEL6:
    case ADC_CHANNEL7:
    case ADC_CHANNEL8:
    case ADC_CHANNEL9:
    case ADC_CHANNEL10:
    case ADC_CHANNEL11:
    case ADC_CHANNEL12:
    case ADC_CHANNEL13:
    case ADC_CHANNEL14:
    case ADC_CHANNEL15:
        
        /* Clear the existing channel val for the position in conv sequence */
        ADC1->SQR[seqRegLookupTable[pos].seqRegIdx] &= 
        ~(ADC_MAX_SEQ_COUNT_VAL << seqRegLookupTable[pos].bitPos); 

        /* Set the channel number for the position in the conversion sequence */
        ADC1->SQR[seqRegLookupTable[pos].seqRegIdx] |= 
        (channel << seqRegLookupTable[pos].bitPos); 
    default:
#if !defined(NDEBUG)
        while(1)
        {
            /* HANG */
        }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}



void adcSetConversionSequenceLength(mcu_word len)
{
#if !defined(NDEBUG)
    if(len > ADC_MAX_SEQ_COUNT_VAL)
    {
        while(1)
        {
            /* HANG HERE. PROGRAMMER TO FIND ERROR */
        }
    }
#endif /* DEBUG BUILD */

    /* Clear sequence length bits */
    ADC1->SQR[0] &= ~SQR1_L;

    /* Set sequence length bits */
    ADC1->SQR[0] |= len;
}



void adcSetPrescaler(ADC_PRESCALER_t ps_val)
{   
    /* Clear existing prescaler bits */
    ADC1_COMMON->CR &= ~CCR_ADCPRE;
    switch(ps_val)
    {
    case ADC_PRESCALER_2:
    case ADC_PRESCALER_4:
    case ADC_PRESCALER_6:
    case ADC_PRESCALER_8:
        /* set new prescaler bits */
        ADC1_COMMON->CR |= ps_val << CCR_ADCPRE_POS;
        break;
    default:
#if !defined(NDEBUG)
        while(1)
        {
            /* HANG */
        }
#else
        break;
#endif  /* DEBUG BUILD */
    }
}
