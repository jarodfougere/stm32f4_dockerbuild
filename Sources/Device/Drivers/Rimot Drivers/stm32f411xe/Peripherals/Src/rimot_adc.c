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

#include "rimot_rcc.h"
#include "rimot_gpio.h"
#include "rimot_adc.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#if defined(STM32F411VE)
#define NUM_ADC_CHANNELS 18
#elif defined(STM32F411RE)
#error CARL YOU FORGOT TO DEFINE NUM_ADC_CHANNELS FOR THE PRODUCTION MCU PACKAGE
#else
#error NO DEFINITION FOR STM32F411xE packae
#endif /* PACKAGE SELECTION */

#define ADC1        ((struct adc_regs*) ADC1_BASE)
#define ADC1_COMMON ((struct adc_common_regs*) ADC1_COMMON_BASE)


/* ADC STATUS REGISTER BIT POSITIONS. PAGE 228 */
#define ADC_SR_AWD_POS   ((mcu_word)0)
#define ADC_SR_EOC_POS   ((mcu_word)1)
#define ADC_SR_JEOC_POS  ((mcu_word)2)
#define ADC_SR_JSTRT_POS ((mcu_word)3)
#define ADC_SR_STRT_POS  ((mcu_word)4)
#define ADC_SR_OVR_POS   ((mcu_word)5)


/* ADC CONTROL REGISTER BIT POSITIONS. PAGE 229 */
#define ADC_CR1_AWDCH_POS   ((mcu_word)0) /* Bits 0 to 4 */
#define ADC_CR1_EOCIE_POS   ((mcu_word)5)
#define ADC_CR1_AWDIE_POS   ((mcu_word)6)
#define ADC_CR1_JEOCIE_POS  ((mcu_word)7)
#define ADC_CR1_SCAN_POS    ((mcu_word)8)
#define ADC_CR1_AWDSGL_POS  ((mcu_word)9)
#define ADC_CR1_JAUTO_POS   ((mcu_word)10)
#define ADC_CR1_DISCEN_POS  ((mcu_word)11)
#define ADC_CR1_JDISCEN_POS ((mcu_word)12)
#define ADC_CR1_DISCNUM_POS ((mcu_word)13) /* Bits 13 to 15 */
/* BITS 16 to 21 RESERVED */
#define ADC_CR1_JAWDEN_POS  ((mcu_word)22)
#define ADC_CR1_AWDEN_POS   ((mcu_word)23)
#define ADC_CR1_RES_POS     ((mcu_word)24) /* BITS 24 TO 25 */
#define ADC_CR1_OVRIE_POS   ((mcu_word)26)
/* Bits 27 to 31 reserved */

#define ADC_CR1_AWDCH_BITCNT   5
#define ADC_CR1_EOCIE_BITCNT   1
#define ADC_CR1_AWDIE_BITCNT   1
#define ADC_CR1_JEOCIE_BITCNT  1
#define ADC_CR1_SCAN_BITCNT    1
#define ADC_CR1_AWDSGL_BITCNT  1
#define ADC_CR1_JAUTO_BITCNT   1
#define ADC_CR1_DISCEN_BITCNT  1
#define ADC_CR1_JDISCEN_BITCNT 1
#define ADC_CR1_DISCNUM_BITCNT 3
#define ADC_CR1_JAWDEN_BITCNT  1
#define ADC_CR1_AWDEN_BITCNT   1
#define ADC_CR1_RES_BITCNT     2 
#define ADC_CR1_OVRIE_BITCNT   1

/* Probably one of the worst cases of macro abuse I've ever done */
#define ADC_CR1(reg) \
((BITMAX(ADC_CR1_ ## reg ## _BITCNT)) << (ADC_CR1_ ## reg ## _POS))


/* PAGE 231. ADC CONTROL REGISTER 2 BIT POSITIONS */
#define ADC_CR2_ADON_POS     ((mcu_word)0)
#define ADC_CR2_CONT_POS     ((mcu_word)1)
/* bits 2 to 7 reserved */
#define ADC_CR2_DMA_POS      ((mcu_word)8)
#define ADC_CR2_DDS_POS      ((mcu_word)9)
#define ADC_CR2_EOCS_POS     ((mcu_word)10)
#define ADC_CR2_ALIGN_POS    ((mcu_word)11)
/* Bits 12 to 15 reserved */
#define ADC_CR2_JEXTSEL_POS  ((mcu_word)16) /* Bits 16 to 19 */
#define ADC_CR2_JEXTEN_POS   ((mcu_word)20) /* Bits 20 to 21 */
#define ADC_CR2_JSWSTART_POS ((mcu_word)22)
/* bit 23 reserved */
#define ADC_CR2_EXTSEL_POS   ((mcu_word)24) /* Bits 24 to 27 */
#define ADC_CR2_EXTEN_POS    ((mcu_word)28) /* Bits 28 to 29 */
#define ADC_CR2_SWSTART_POS  ((mcu_word)30)
/* BIT 31 RESERVED */

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
    ADC1->CR2 |= (1 << ADC_CR2_ADON_POS);
}

void adcDisable(void)
{
    ADC1->CR2 &= ~(1 << ADC_CR2_ADON_POS);
}


void adc_LL_init(void)
{   
    /* Configure RF1 input to be used by the ADC */



    /* Enable the overrun interrupt */
    ADC1->CR1 |= ADC_CR1_OVRIE_POS;

    LL_ASSERT(0 == adcSetRes(ADC_RES_12));

    /* Enable end of conversion interrupts for regular channels */
    ADC1->CR1 |= (1 << ADC_CR1_EOCIE_POS);

    /* Enable end of conversion interrupts for injected channels */
    ADC1->CR1 |= (1 << ADC_CR1_JEOCIE_POS);

    /* Dma requests are issued as long as data is converted */
    ADC1->CR2 |= (1 << ADC_CR2_DDS_POS);

    /* DMA transfers are enabled */
    ADC1->CR2 |= (1 << ADC_CR2_DMA_POS);

    mcu_word test = BITMAX(5);
}


mcu_word adcCheckOverrun(void)
{
    return ISBITSET(ADC1->SR, ADC_SR_OVR_POS);
}


mcu_word adcCheckStart(void)
{
    return ISBITSET(ADC1->SR, ADC_SR_STRT_POS);
}

mcu_word adcCheckJstart(void)
{
    return ISBITSET(ADC1->SR, ADC_SR_JSTRT_POS);
}


mcu_word adcCheckJEOC(void)
{
    return ISBITSET(ADC1->SR, ADC_SR_JEOC_POS);
}


mcu_word adcCheckEOC(void)
{
    return ISBITSET(ADC1->SR, ADC_SR_EOC_POS);
}

mcu_word adcCheckAwd(void)
{
    return ISBITSET(ADC1->SR, ADC_SR_AWD_POS);
}


mcu_short adcGetConvData(void)
{   
    /* 12 bit mask (since max resolution is 12 bits) */
    return ((mcu_short)(ADC1->DR & BITMAX(12)));
}




mcu_word adcSetRes(ADC_RES_t res)
{   
    /* Wipe all 4 res bits */
    /* When res bits are zeroed, 12bit res is dflt */
    ADC1->CR1 &= ADC_CR1(RES);
    switch(res)
    {
        case ADC_RES_12:
        case ADC_RES_10:
        case ADC_RES_8:
        case ADC_RES_6:
            ADC1->CR1 |= (ADC_CR1(RES) & res);
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
    switch(ch)
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
        case ADC_CHANNEL16:
        case ADC_CHANNEL17:
        case ADC_CHANNEL18:
            switch (smp)
            {
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
                        ADC1->SMPR1 &= ~(7 << (3 * ch));

                        /* Set sample config bits */
                        ADC1->SMPR1 |= (smp << (3 * ch));
                    }
                    else
                    {
                        /* Clear previous sample config bits */
                        ADC1->SMPR2 &= ~(0b111 << (3 * (ch - 9)));

                        /* Set sample config bits */
                        ADC1->SMPR2 |= (smp << (3 * (ch - 9)));
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

