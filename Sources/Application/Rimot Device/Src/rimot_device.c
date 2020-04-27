/**
 * @file rimot_device.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This module provides an abstraction to represent the device 
 * configuration state in the application
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

#include "rimot_device.h"
#include "outpost_config.h"
#include "rimot_LL_debug.h"
#include "gpio_interface.h"
#include "rf_interface.h"


struct rimot_device_structure
{   
    struct
    {
        uint32_t  heartbeat_interval;         /* device systick interval      */
        uint32_t  data_interval;              /* data transmission interval   */
        uint32_t  mode;                       /* the device's operation mode  */
    }   cfg;
    outpost_config *outpost_cfg;
    gpioConfig_t   *gpioCfg;
    rfConfig_t*     rfCfg[NUM_RF_INPUTS];
    DEVICE_STATE_t  state;
};


/* 
 * Stuff like this is why I HATE C. I should be able to statically declare 
 * a struct. But nooooo, in C, structures dont have linkage so I have to put
 * it on the heap - making linker scripts a pain in the ass. 
 * 
 *  ________________________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
 *  ____________________¶¶¶___________________¶¶¶¶_____
 *  ________________¶¶¶_________________________¶¶¶¶___
 *  ______________¶¶______________________________¶¶¶__
 *  ___________¶¶¶_________________________________¶¶¶_
 *  _________¶¶_____________________________________¶¶¶
 *  ________¶¶_________¶¶¶¶¶___________¶¶¶¶¶_________¶¶
 *  ______¶¶__________¶¶¶¶¶¶__________¶¶¶¶¶¶_________¶¶
 *  _____¶¶___________¶¶¶¶____________¶¶¶¶___________¶¶
 *  ____¶¶___________________________________________¶¶
 *  ___¶¶___________________________________________¶¶_
 *  __¶¶____________________¶¶¶¶____________________¶¶_
 *  _¶¶_______________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶______________¶¶__
 *  _¶¶____________¶¶¶¶___________¶¶¶¶¶___________¶¶___
 *  ¶¶¶_________¶¶¶__________________¶¶__________¶¶____
 *  ¶¶_________¶______________________¶¶________¶¶_____
 *  ¶¶¶______¶________________________¶¶_______¶¶______
 *  ¶¶¶_____¶_________________________¶¶_____¶¶________
 *  _¶¶¶___________________________________¶¶__________
 *  __¶¶¶________________________________¶¶____________
 *  ___¶¶¶____________________________¶¶_______________
 *  ____¶¶¶¶______________________¶¶¶__________________
 *  _______¶¶¶¶¶_____________¶¶¶¶¶_____________________
 * 
 * The alternative is just to put the structure declaration in a header file 
 * but then the caller knows about the elements in the structure (can't fully)
 * encapsulate them. 
 * 
 * In any case, its safe because the malloc occurs at the start of the mainline.
 * Even if there were an RTOS kernel, it wouldnt have been called to Init yet.
 * 
 */
virtualDev* virtualDevInit(void)
{   
    virtualDev* dev = (virtualDev*)malloc(sizeof(virtualDev));
    dev->cfg.data_interval = DEFAULT_DEVICE_DATA_INTERVAL_S;
    dev->cfg.heartbeat_interval = DEFAULT_DEVICE_HEARTBEAT_INTERVAL_S;
    dev->state = DEVICE_STATE_boot;
    dev->outpost_cfg = outpost_configInit();
    dev->gpioCfg = gpioConfigInit();
    dev->rfCfg[0]   = rfCfgInit();
    dev->rfCfg[1]   = rfCfgInit();
    return dev;
}


DEVICE_STATE_t devGetState(const virtualDev *dev)
{
    return dev->state;
}


void devSetState(virtualDev *dev, DEVICE_STATE_t state)
{
    dev->state = state;
}


void devSetCfgHbInterval(virtualDev *dev, uint32_t hbInterval)
{   
    LL_ASSERT(NULL != dev);
    dev->cfg.heartbeat_interval = hbInterval;
}


uint32_t devGetHbInterval(const virtualDev *dev)
{
    LL_ASSERT(NULL != dev);
    return dev->cfg.heartbeat_interval;
}


void devSetCfgDataInterval(virtualDev *dev, uint32_t dataInterval)
{
    LL_ASSERT(NULL != dev);
    dev->cfg.data_interval = dataInterval;
}


uint32_t devGetCfgDataInterval(const virtualDev *dev)
{
    LL_ASSERT(NULL != dev);
    return dev->cfg.data_interval;
}


void devSetCfgMode(virtualDev *dev, uint32_t mode)
{
    LL_ASSERT(NULL != dev);
    dev->cfg.mode = mode;
}


uint32_t devGetCfgMode(const virtualDev *dev)
{
    LL_ASSERT(NULL != dev);
    return dev->cfg.mode;
}




outpost_config* devGetOutpostCfg(const virtualDev *dev)
{
    return dev->outpost_cfg;
}
