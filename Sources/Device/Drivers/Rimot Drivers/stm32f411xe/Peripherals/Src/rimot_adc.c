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
#include "rimot_register_bit_ops.h"
#include "rimot_LL_debug.h"

#define ADC1                ((struct adc_regs*) ADC1_BASE)
#define ADC1_COMMON         ((struct adc_common_regs*) ADC1_COMMON_BASE)


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



/* SOFTWARE EVENTS TO TRIGGER AN ADC CONVERSION PAGE 222 */
#define ADC_EXTSEL_tim1_ch1  ((mcu_word)0x00)
#define ADC_EXTSEL_tim1_ch2  ((mcu_word)0x01)
#define ADC_EXTSEL_tim1_ch3  ((mcu_word)0x02)
#define ADC_EXTSEL_tim2_ch2  ((mcu_word)0x03)
#define ADC_EXTSEL_tim2_ch3  ((mcu_word)0x04)
#define ADC_EXTSEL_tim2_ch4  ((mcu_word)0x05)
#define ADC_EXTSEL_tim2_TRGO ((mcu_word)0x06)
#define ADC_EXTSEL_tim3_ch1  ((mcu_word)0x07)
#define ADC_EXTSEL_tim3_TRGO ((mcu_word)0x08)
#define ADC_EXTSEL_tim4_ch1  ()


static void adcEnable(void)
{
    ADC1->CR2 |= (1 << ADC_CR2_ADON_POS);
}

static void adcDisable(void)
{
    ADC1->CR2 &= ~(1 << ADC_CR2_ADON_POS);
}


mcu_word adcSetSampleTime(ADC_SAMPLE_t smp, ADC_CHANNEL_t channel)
{   

    /* 
     * TODO: THIS COULD BE MADE FAR LESS UGLY. ITS NOT INEFFICIENT,
     *       BUT  SWEET MAMA IS IT UNREADABLE. SHOULD USE LOOKUP
     *       TABLES. IVE ALREADY CONFIRMED THAT COMPILER OPTIMIZES
     *       ADC_CHANNEL_t to map directly onto the actual masked
     *       value that would go in the corresponding bits for 
     *       ADC::SMP1 // ADC::SMP2 but its hard to read this 
     *       freaking function
     * 
     * [CARL MATTATALL, APRIL 3, 2020]
     */
    mcu_word status = 0;
    switch(channel)
    {
        case ADC_CHANNEL0:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL1:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL2:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL3:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL4:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL5:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL6:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL7:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL8:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL9:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL10:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL11:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL12:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL13:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL14:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL15:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL16:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL17:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        case ADC_CHANNEL18:
            switch(smp)
            {
                case ADC_SAMPLE_3:

                    break;
                case ADC_SAMPLE_15:

                    break;
                case ADC_SAMPLE_28:

                    break;
                case ADC_SAMPLE_56:

                    break;
                case ADC_SAMPLE_84:

                    break;
                case ADC_SAMPLE_112:

                    break;
                case ADC_SAMPLE_144:

                    break;
                case ADC_SAMPLE_480:

                    break;
                default:
                    status = 1;
#if !defined(NDEBUG)
                    while(1)
                    {
                        /* Hang here */
                    }
#else
                    break;
#endif /* DEBUG BUILD */
            }
            break;
        default:
            status = 1;
#if !defined(NDEBUG)
            while(1)
            {
                /* Hang here */
            }
#else       
            /* We won't do anything */
            return 1;
            break;
#endif /* DEBUG BUILD */
    }
    return status;
}





void adc_LL_init(void)
{   
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
    return ((mcu_short)(ADC1->DR & 0x0fff));
}




mcu_word adcSetRes(ADC_RES_t res)
{   
    /* Wipe all 4 res bits */
    /* When res bits are zeroed, 12bit res is dflt */
    ADC1->CR1 &= (0x4 << ADC_CR1_RES_POS);
    switch(res)
    {
        case ADC_RES_12:
            return 0; /* 12bit res is default */
            break;
        case ADC_RES_10:
            ADC1->CR1 |= (1 << ADC_CR1_RES_POS);
            return 0; 
            break;
        case ADC_RES_8:
            ADC1->CR1 |= (2 << ADC_CR1_RES_POS);
            return 0; 
            break;
        case ADC_RES_6:
            ADC1->CR1 |= (3 << ADC_CR1_RES_POS);
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
