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
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
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


