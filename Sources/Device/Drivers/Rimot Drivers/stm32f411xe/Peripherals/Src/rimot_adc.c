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

#include "rimot_adc.h"
#include "rimot_adc_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

/* Required externals */
#include "rimot_rcc.h"
#include "rimot_gpio.h"

#if defined(STM32F411VE)
#define NUM_ADC_CHANNELS 18
#elif defined(STM32F411RE)
#error CARL YOU FORGOT TO DEFINE NUM_ADC_CHANNELS FOR THE PRODUCTION MCU PACKAGE
#else
#error NO DEFINITION FOR STM32F411xE packae
#endif /* PACKAGE SELECTION */

struct adc_common_regs
{
    hw_reg SR;   /* common status register                    */
    sw_reg CR;   /* common config register                    */
    hw_reg DR;   /* common data register.                     */
};               /* only used in dual/triple/interleaved mode.*/
#define ADC1_COMMON ((struct adc_common_regs*) ADC1_COMMON_BASE)

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
#define ADC1        ((struct adc_regs*) ADC1_BASE)


struct
{
    mcu_word      pin;
    ADC_CHANNEL_t channel;
}   pin_channel_map[NUM_ADC_CHANNELS] = 
#if defined(STM32F411VE)
{
    {PA0, ADC_CHANNEL0},
    {PA1, ADC_CHANNEL1},
};
#elif defined(STM32F411RE)
#error CARL YOU FORGOT TO DEFINE NUM_ADC_CHANNELS FOR THE PRODUCTION MCU PACKAGE
{};
#else
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


void adc_LL_init(void)
{   
    /* Configure RF1 input to be used by the ADC */

    /* Enable the overrun interrupt */
    ADC1->CR1 |= CR1_OVRIE;

    LL_ASSERT(0 == adcSetRes(ADC_RES_12));

    /* Enable end of conversion interrupts for regular channels */
    ADC1->CR1 |= CR1_EOCIE;

    /* Enable end of conversion interrupts for injected channels */
    ADC1->CR1 |= CR1_JEOCIE;

    /* Dma requests are issued as long as data is converted */
    ADC1->CR2 |= CR2_DDS;

    /* DMA transfers are enabled */
    ADC1->CR2 |=  CR2_DMA;

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
    switch(res)
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
            while(1)
            {
                /* invalid value. hang here */
            }
#else   
            /* 12 bit resolution is dflt but return 1
            so caller knows they made a mistake */
            return 1; 
            break;
#endif  /* DEBUG BUILD */
    }
}


mcu_word adcChannelConfig(ADC_CHANNEL_t ch, ADC_SAMPLE_t smp)
{
    mcu_word status = 0;
    mcu_word smp_val = (mcu_word)smp; /* Cast enum to unsigned */
    mcu_word channel = (mcu_word)ch;  /* Cast enum to unsigned */
    switch(ch)
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
        case ADC_CHANNEL16:
        case ADC_CHANNEL17:
        case ADC_CHANNEL18:
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
                    set_pin_mode(GPIO_MODE_analog, pin_channel_map[ch].pin);

                    /* Register selection */

                    /* CHANNELS 0 -> 9 IN SMPR1, 10 -> 18 IN SMPR2 */
                    if(ch > 9)  
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
                    while(1);   /* hang */
#else
                    break;
#endif 
            }
            break;
        default:
            status = 1;
#if !defined(NDEBUG)
            while(1);
#else
            break;
#endif 
    }
    return status;
}

