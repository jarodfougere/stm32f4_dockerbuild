/**
 * @file digital_input_interface.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides an interface for the "digital inputs" on
 * the integrated sensor module by bundling low level drivers
 * @version 0.1
 * @date 2020-04-09
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

#include "pin_config_interface.h"
#include "digital_input_interface.h"
#include "rimot_LL_debug.h"



struct gpio_input_config
{
    pinCfgCore_t pin;
    struct
    {   
        INPUT_TRIGGERMODE_t triggerMode;
        uint32_t debounceTime;  /* units in multiples of 100 ms */
    }   input;
};


inputConfig_t* newInputConfig(GPIO_PIN_ID_t id)
{
    inputConfig_t *cfg = (inputConfig_t*)malloc(sizeof(inputConfig_t));
    LL_ASSERT(NULL != cfg);
    LL_ASSERT(id > 0);
    LL_ASSERT(id <= NUM_DIGITAL_INPUT_PINS);
    pinCfg_resetToDefault(&cfg->pin, id, GPIO_PINTYPE_digital_input);
    cfg->input.debounceTime = DIGITAL_INPUT_DEFAULT_DEBOUNCE;  
    cfg->input.triggerMode  = INPUT_TRIGGERMODE_high; /* Default trigger mode */
    return cfg;
}


INPUT_TRIGGERMODE_t inputGetTriggerMode(const inputConfig_t *input)
{   
    LL_ASSERT(NULL != input);
    return (INPUT_TRIGGERMODE_t)input->input.triggerMode;
}

uint32_t inputGetDebounceTime(const inputConfig_t *input)
{
    LL_ASSERT(NULL != input);
    return (uint32_t)input->input.debounceTime;
}


pinCfgCore_t* inputGetPinConfig(const inputConfig_t *input)
{
    LL_ASSERT(NULL != input);
    return (pinCfgCore_t*)&input->pin;
}


void inputSetTriggerMode(inputConfig_t *input, INPUT_TRIGGERMODE_t mode)
{
    LL_ASSERT(NULL != input);
    input->input.triggerMode = mode;
}

void inputSetDebounceTime(inputConfig_t *input, uint32_t debounceTime)
{
    LL_ASSERT(NULL != input);
    input->input.debounceTime = debounceTime;
}
