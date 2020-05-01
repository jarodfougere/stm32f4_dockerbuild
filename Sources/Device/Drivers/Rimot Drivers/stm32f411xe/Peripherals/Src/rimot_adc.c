/**
 * @file rimot_adc.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This source module profides a low level "driver"
 * for the adc peripheral
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. 
 */
#include "rimot_bus_region_offsets.h"

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
#error NO DEFINITION FOR STM32F411xE package
#endif /* PACKAGE SELECTION */

#define ADC1_BASE_ADDRESS (APB2PERIPH_BASE + 0x2000U)
#define ADC1_COMMON_BASE_ADDRESS (APB2PERIPH_BASE + 0x2300U)

#define ADC_RSEQ_LEN_MSK 0XF /* 15 CONSECUTIVE CHANNELS */
#define ADC_JSEQ_LEN_MSK 0x3 /* 4 consecutive injected channels */

struct adc_common_regs
{
    volatile uint32_t SR;   /* common status register                       */
    uint32_t CR;            /* common config register                       */
    volatile uint32_t DR;   /* common data register.                        */
};                          /* DR only used in dual/triple/interleaved mode.*/
#define ADC1_COMMON ((struct adc_common_regs *)ADC1_COMMON_BASE_ADDRESS)

struct adc_regs
{
    volatile uint32_t SR;      /* Status register                       */
    volatile uint32_t CR1;     /* Control register1                     */
    volatile uint32_t CR2;     /* Control register2                     */
    volatile uint32_t SMPR1;   /* Sample time reigster 1                */
    volatile uint32_t SMPR2;   /* Sample time register 2                */
    volatile uint32_t JOFR[4]; /* Injected channel offset registers     */
    volatile uint32_t HTR;     /* Watchdog high threshhold register     */
    volatile uint32_t LTR;     /* Watchdog low threshhold register      */
    volatile uint32_t SQR[3];  /* Regular conversion sequence registers */
    volatile uint32_t JSQR;    /* Injected conversion sequence register */
    volatile uint32_t JDR[4];  /* Injected conversion data registers    */
    volatile uint32_t DR;      /* Conversion data register              */
};
#define ADC1 ((struct adc_regs *)ADC1_BASE_ADDRESS)


/* The ADC Channel */
typedef enum
{
    ADC_CHANNEL0 = 0U,
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
}   ADC_CHANNEL_t;


static const ADC_CHANNEL_t adc_pin_ch_tbl[] =
#if defined(STM32F411VE)
{
    [MCUPIN_PA0] = ADC_CHANNEL0,
    [MCUPIN_PA1] = ADC_CHANNEL1, 
    [MCUPIN_PA2] = ADC_CHANNEL2,
    [MCUPIN_PA3] = ADC_CHANNEL3, 
    [MCUPIN_PA4] = ADC_CHANNEL4,
    [MCUPIN_PA5] = ADC_CHANNEL5,
    [MCUPIN_PA6] = ADC_CHANNEL6, 
    [MCUPIN_PA7] = ADC_CHANNEL7,
    [MCUPIN_PB8] = ADC_CHANNEL8,
    [MCUPIN_PB9] = ADC_CHANNEL9,
    [MCUPIN_PC0] = ADC_CHANNEL10, 
    [MCUPIN_PC1] = ADC_CHANNEL11,
    [MCUPIN_PC2] = ADC_CHANNEL12,
    [MCUPIN_PC3] = ADC_CHANNEL13,
    [MCUPIN_PC4] = ADC_CHANNEL14,
    [MCUPIN_PC5] = ADC_CHANNEL15,
};


/* SEE PAGES 234, 235, 236 REFERENCE MANUAL */
static const struct 
{
    uint32_t seqRegIdx; /* Which of the 3 sequence registers to access   */
    uint32_t pos;       /* The bit position (left justified in register) */
}   seqRegTbl[] = 
{
    [ADC_SEQ_POS_1]  = {.pos = 0,  .seqRegIdx = 2},
    [ADC_SEQ_POS_2]  = {.pos = 5,  .seqRegIdx = 2},
    [ADC_SEQ_POS_3]  = {.pos = 10, .seqRegIdx = 2},
    [ADC_SEQ_POS_4]  = {.pos = 15, .seqRegIdx = 2},
    [ADC_SEQ_POS_5]  = {.pos = 20, .seqRegIdx = 2},
    [ADC_SEQ_POS_6]  = {.pos = 25, .seqRegIdx = 2},
    [ADC_SEQ_POS_7]  = {.pos = 0,  .seqRegIdx = 1},
    [ADC_SEQ_POS_8]  = {.pos = 5,  .seqRegIdx = 1},
    [ADC_SEQ_POS_9]  = {.pos = 10, .seqRegIdx = 1},
    [ADC_SEQ_POS_10] = {.pos = 15, .seqRegIdx = 1},
    [ADC_SEQ_POS_11] = {.pos = 20, .seqRegIdx = 1},
    [ADC_SEQ_POS_12] = {.pos = 25, .seqRegIdx = 1},
    [ADC_SEQ_POS_13] = {.pos = 0,  .seqRegIdx = 0},
    [ADC_SEQ_POS_14] = {.pos = 5,  .seqRegIdx = 0},
    [ADC_SEQ_POS_15] = {.pos = 10, .seqRegIdx = 0},
    [ADC_SEQ_POS_16] = {.pos = 15, .seqRegIdx = 0},
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



uint32_t adcCheckOverrun(void)
{
    return !!(ADC1->SR & SR_OVR);
}

uint32_t adcCheckStart(void)
{
    return !!(ADC1->SR & SR_STRT);
}

uint32_t adcCheckJstart(void)
{
    return !!(ADC1->SR & SR_JSTRT);
}

uint32_t adcCheckJEOC(void)
{
    return !!(ADC1->SR & SR_JEOC);
}

uint32_t adcCheckEOC(void)
{
    return !!(ADC1->SR & SR_EOC);
}

uint32_t adcCheckAwd(void)
{
    return !!(ADC1->SR & SR_AWD);
}

uint32_t adcGetConvData(void)
{
    return ADC1->DR;
}

uint32_t adcSetRes(ADC_RES_t res)
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

uint32_t adcChannelConfig(MCUPIN_t pin, ADC_SAMPLE_t smp)
{
    uint32_t status = 0;
    ADC_CHANNEL_t channel = adc_pin_ch_tbl[pin];
    switch (channel)
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
            gpio_setPinMode(pin, GPIO_MODE_analog);
            /* Register selection */

            /* CHANNELS 0 -> 9 IN SMPR1, 10 -> 18 IN SMPR2 */
            if (channel > 9)
            {
                /* Clear previous sample config bits */
                ADC1->SMPR1 &= ~(7 << (3 * channel));

                /* Set sample config bits */
                ADC1->SMPR1 |= (smp << (3 * channel));
            }
            else
            {
                /* Clear previous sample config bits */
                ADC1->SMPR2 &= ~(7 << (3 * (channel - 9)));

                /* Set sample config bits */
                ADC1->SMPR2 |= (smp << (3 * (channel - 9)));
            }
            break;
        default:
            status = 1;
            /* Don't touch the bits */
#if !defined(NDEBUG)
            while (1)
            {
                /* hang. programmer to find error */
            }
#else
            break;
#endif
        }
        break;
    default:
        status = 1;
#if !defined(NDEBUG)
        while (1)
        {
            /* hang. programmer to find error */
        }
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


void adcStartConversion(ADC_GROUPTYPE_t group_type)
{   
    switch(group_type)
    {
    case ADC_GROUPTYPE_regular:
        /* If a conversion has not been started */
        while(ADC1->CR2 & CR2_SWSTART);
        ADC1->CR2 |= CR2_SWSTART;
    break;
    case ADC_GROUPTYPE_injected:
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
            /* (Default option)                                         */
            /* ADC::SR:EOC is only set after the final conv in sequence */
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


void adcSetConvSeqPin(MCUPIN_t pin, ADC_GROUPTYPE_t group, uint32_t seqPos)
{   
    /* Validate group field */
    switch(group)
    {
        case ADC_GROUPTYPE_injected:
        {
            /* Make sure the pin actually maps to an adc channel */
            switch(adc_pin_ch_tbl[pin])
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
                {
                    /* Validate sequence position */
                    switch(seqPos)
                    {   
                        /* INJECTED SEQUENCE MAXES OUT AT 4 CONVERSIONS */
                        case ADC_SEQ_POS_1:
                        case ADC_SEQ_POS_2:
                        case ADC_SEQ_POS_3:
                        case ADC_SEQ_POS_4:
                        {
                            /* 
                            * Clear the existing channel val bits 
                            * for the position in conv sequence
                            */
                            ADC1->JSQR &=
                            ~((ADC_JSEQ_LEN_MSK) << seqRegTbl[seqPos].pos); 
                            ADC1->JSQR |= 
                            (adc_pin_ch_tbl[pin] << seqRegTbl[seqPos].pos); 

                            /* 
                             * If we are increasing the max 
                             * position in conv sequence,
                             * 
                             * Then update the conversion
                             * sequence length to the new
                             * max value.
                             */
                            if(((ADC1->JSQR & JSQR_JL) >> JSQR_JL_POS) < seqPos)
                            {   
                                ADC1->JSQR &= JSQR_JL;
                                ADC1->JSQR |= (seqPos << JSQR_JL_POS);
                            }
                        }
                        break;
                        case ADC_SEQ_POS_5: 
                        case ADC_SEQ_POS_6:
                        case ADC_SEQ_POS_7:
                        case ADC_SEQ_POS_8:
                        case ADC_SEQ_POS_9:
                        case ADC_SEQ_POS_10:
                        case ADC_SEQ_POS_11:
                        case ADC_SEQ_POS_12:
                        case ADC_SEQ_POS_13:
                        case ADC_SEQ_POS_14:
                        case ADC_SEQ_POS_15:
                        default:
                            LL_ASSERT(0);
                    }
                }
                break;
                default:
                    LL_ASSERT(0);
            }
        }
        break;
        case ADC_GROUPTYPE_regular:
        {    
            /* Make sure the pin actually maps to an adc channel */
            switch(adc_pin_ch_tbl[pin])
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
                {   
                    /* Validate sequence position */
                    switch(seqPos)
                    {
                        case ADC_SEQ_POS_1:
                        case ADC_SEQ_POS_2:
                        case ADC_SEQ_POS_3:
                        case ADC_SEQ_POS_4:
                        case ADC_SEQ_POS_5:
                        case ADC_SEQ_POS_6:
                        case ADC_SEQ_POS_7:
                        case ADC_SEQ_POS_8:
                        case ADC_SEQ_POS_9:
                        case ADC_SEQ_POS_10:
                        case ADC_SEQ_POS_11:
                        case ADC_SEQ_POS_12:
                        case ADC_SEQ_POS_13:
                        case ADC_SEQ_POS_14:
                        case ADC_SEQ_POS_15:
                        {
                            /* 
                            * Set the existing channel val bits 
                            * for the position in conv sequence
                            */
                            ADC1->SQR[seqRegTbl[seqPos].seqRegIdx] &= 
                            ~((ADC_RSEQ_LEN_MSK) << seqRegTbl[seqPos].pos); 
                            ADC1->SQR[seqRegTbl[seqPos].seqRegIdx] |= 
                            (adc_pin_ch_tbl[pin] << seqRegTbl[seqPos].pos); 

                            /* 
                             * If we are increasing the max 
                             * position in conv sequence,
                             * 
                             * Then update the conversion
                             * sequence length to the new
                             * max value.
                             */
                            if(((ADC1->SQR[0] & SQR1_L) >> SQR1_L_POS) < seqPos)
                            {
                                ADC1->SQR[0] &= SQR1_L;
                                ADC1->SQR[0] |= seqPos << SQR1_L_POS;
                            }
                        }
                        break;
                        default:
                            LL_ASSERT(0);
                    }
                }
                break;
                default:
                    LL_ASSERT(0);
            }
        }
        break;
        default:
            LL_ASSERT(0);   
    }
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




#if !defined(USE_HAL_DRIVER)
void ADC_IRQHandler(void)
{

}
#endif


