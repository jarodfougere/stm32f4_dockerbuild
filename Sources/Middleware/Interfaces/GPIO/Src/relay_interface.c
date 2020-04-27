/**
 * @file relay_interface.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This file provides an abstract interface for the
 * "digital outputs" (relays) on the integrated sensor module 
 * by bundling together low level drivers
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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "pin_config_interface.h"
#include "relay_interface.h"
#include "rimot_LL_debug.h"

struct gpio_relay_config
{   
    pinCfgCore_t pin;
    struct
    {   
        RELAYPOS_t   current_pos;   /* Current position of relay contact     */
        RELAYPOS_t   normal_pos;    /* User-configured dflt contact position */
        RELAY_MODE_t mode;          /* Toggle or countdown mode              */
    }   relay;
};


/* Yes I know that the type and id are redundant information. we can fix this 
micro-optimation in a future refactor. Right now I'm literally only concerned 
about finishing the project on time */

relayConfig_t* newRelayConfig(GPIO_PIN_ID_t id)
{
    relayConfig_t *cfg = (relayConfig_t*)malloc(sizeof(relayConfig_t));
    LL_ASSERT(NULL != cfg);
    LL_ASSERT(id > 0);
    LL_ASSERT(id <= NUM_RELAY_PINS);
    pinCfg_resetToDefault(&cfg->pin, id, GPIO_PINTYPE_relay_output);
    cfg->relay.current_pos = RELAYPOS_open;
    cfg->relay.normal_pos  = RELAYPOS_open;
    cfg->relay.mode        = RELAY_MODE_toggle;
    cfg->pin.period        = 0; /* toggle mode has no period */
    return cfg;
}


RELAYPOS_t relayGetDfltPos(const relayConfig_t *relay)
{
    LL_ASSERT(NULL != relay);
    return relay->relay.normal_pos;
}

RELAYPOS_t relayGetCurrentPos(const relayConfig_t *relay)
{
    LL_ASSERT(NULL != relay);
    return relay->relay.current_pos;
}


uint32_t relayGetHoldTime(const relayConfig_t *relay)
{
    LL_ASSERT(NULL != relay);
    return relay->pin.period;
}


RELAY_MODE_t relayGetMode(const relayConfig_t *relay)
{
    LL_ASSERT(NULL != relay);
    return relay->relay.mode;
}


pinCfgCore_t* relayGetPinCfg(const relayConfig_t *relay)
{
    LL_ASSERT(NULL != relay);
    return (pinCfgCore_t*)&relay->pin;
}


void relaySetDfltPos(relayConfig_t *relay, RELAYPOS_t pos)
{
    LL_ASSERT(NULL != relay);
    relay->relay.normal_pos = pos;
}


void relaySetCurrentPos(relayConfig_t *relay, RELAYPOS_t pos)
{   
    LL_ASSERT(NULL != relay);
    relay->relay.current_pos = pos;
}


void relaySetMode(relayConfig_t *relay, RELAY_MODE_t mode)
{   
    LL_ASSERT(NULL != relay);
    switch(mode)
    {
        case RELAY_MODE_countdown:
            relay->relay.mode = mode;
        break;
        case RELAY_MODE_toggle:
            relay->relay.mode = RELAY_MODE_toggle;
            relay->pin.period = 0; /* Clear the hold time in toggle mode */
        break;  
        default:
#if !defined(NDEBUG)
            LL_ASSERT(0);   /* Hang forever in debug mode */
#else       
            relay->relay.mode = RELAY_MODE_toggle;
#endif /* DEBUG BUILD */
        break;
    }
}


int relaySetHoldTime(relayConfig_t *relay, uint32_t holdTime)
{   
    LL_ASSERT(NULL != relay);
    int status = 0;
    if(RELAY_MODE_toggle == relay->relay.mode)
    {   
        status = 1;
        LL_ASSERT(0);   /* In debug mode hang */
    }
    else
    {   
        relay->pin.period = holdTime;
    }
    return status;
}







