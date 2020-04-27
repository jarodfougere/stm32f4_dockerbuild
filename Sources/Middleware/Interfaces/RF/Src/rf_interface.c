/**
 * @file rf_interface.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This module provides an interface that bundles measurement
 * of signal power envelope, statistical normalization of samples,
 * voltage conversion from the directional coupler, insertion loss
 * correction, and so on. The interface is used primarily by the RF task.
 * @version 0.1
 * @date 2020-03-30
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

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "rf_interface.h"
#include "rimot_adc.h"
#include "rimot_dma.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"


/* an "rf input" is a PAIR of the N type connectors going to a coupler */
#define NUM_RF_INPUTS 2
#define UNASSIGNED_TRANSMITTER_ID "0000000000000000000000"
#define UNUSED_SETPOINT_VALUE 0.0



struct rf_setpoints
{   
    rf_powerVal redHigh;
    rf_powerVal yellowHigh;  
};


struct rf_config_struct
{   
    struct
    {
        struct rf_setpoints forward_pwr;
        struct rf_setpoints reflected_pwr;
        struct rf_setpoints vswr;
    } setpoints;
};





#if defined(STM32F411VE)
#define RF1_FWD_PIN MCUPIN_PA0
#define RF1_REF_PIN MCUPIN_PA1
#define RF2_FWD_PIN MCUPIN_PA4
#define RF2_REF_PIN MCUPIN_PA5
#elif defined(STM32F411RE)
#error BAT_PINx must be defined for STM32F411RE in gpio_interface.c
#else
#error NO DEFINITION FOR STM32F411xE package
#endif /* PACKAGE SELECTION */



void rfIF_init(void)
{
    adcEnable();
    adcSetRes(ADC_RES_12);
    adcSetPrescaler(ADC_PRESCALER_2);
    adcEnableInterrupt(ADC_ISR_overrun);
    adcEnableInterrupt(ADC_ISR_injected_end_of_conversion);
    adcSetConvSeqPin(RF1_FWD_PIN, ADC_GROUPTYPE_injected, ADC_SEQ_POS_1);
    adcSetConvSeqPin(RF1_REF_PIN, ADC_GROUPTYPE_injected, ADC_SEQ_POS_2);
    adcSetConvSeqPin(RF2_FWD_PIN, ADC_GROUPTYPE_injected, ADC_SEQ_POS_3);
    adcSetConvSeqPin(RF2_REF_PIN, ADC_GROUPTYPE_injected, ADC_SEQ_POS_4);
}


rfConfig_t* rfCfgInit(void)
{
    rfConfig_t* cfg = (rfConfig_t*)malloc(sizeof(rfConfig_t));
    LL_ASSERT(NULL != cfg);


    return cfg;
}


