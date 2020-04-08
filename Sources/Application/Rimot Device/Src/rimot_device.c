
#include <stdint.h>
#include <stdlib.h>

#include "rimot_device.h"

#include "outpost_config.h"
#include "rimot_LL_debug.h"
#include "gpio_interface.h"
#include "rf_interface.h"

#warning rfConfig has not been added to rimot_device.c for \
struct rimot_device_structure

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

    /* RF CONFIG GOES HERE WHEN WE GET TO THAT POINT */

    
    DEVICE_STATE_t  state;
};

static const char *dev_cfg_error_messages[] = 
{   
    "configuration is valid",
    "configured data interval less than min",
    "configured data interval is more than max",
    "configured heartbeat interval is less than min",
    "configured heartbeat interval is more than max",
    "configured device name is too long"
    "configured device mode is invalid",
};

static int validate_device_config(const virtualDev *dev);


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
    /* Cast so compilation also works with C++ */
    virtualDev* dev = (virtualDev*)malloc(sizeof(virtualDev));
    dev->cfg.data_interval = DEFAULT_DEVICE_DATA_INTERVAL_S;
    dev->cfg.heartbeat_interval = DEFAULT_DEVICE_HEARTBEAT_INTERVAL_S;
    dev->state = DEVICE_STATE_boot;
    dev->outpost_cfg = outpost_configInit();
    dev->gpioCfg = gpioConfigInit();

    #warning RF_CONFIG_INIT NOT ADDED TO virtualDevInit Yet.
    /* RF configuration init (for both RF 1 and 2) goes here */

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
#ifndef NDEBUG
    LL_ASSERT(NULL != dev);
#endif 
    dev->cfg.heartbeat_interval = hbInterval;
}

uint32_t devGetHbInterval(const virtualDev *dev)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != dev);
#endif 
    return dev->cfg.heartbeat_interval;
}


void devSetCfgDataInterval(virtualDev *dev, uint32_t dataInterval)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != dev);
#endif 
    dev->cfg.data_interval = dataInterval;
}

uint32_t devGetCfgDataInterval(const virtualDev *dev)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != dev);
#endif 
    return dev->cfg.data_interval;
}


void devSetCfgMode(virtualDev *dev, uint32_t mode)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != dev);
#endif 
    dev->cfg.mode = mode;
}


uint32_t devGetCfgMode(const virtualDev *dev)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != dev);
#endif 
    return dev->cfg.mode;
}


/* TODO: FIX MAGIC NUMBERS */
static int validate_device_config(const virtualDev *dev)
{
    if(dev->cfg.data_interval < MIN_DEVICE_DATA_INTERVAL_S)
    {
        return 1;
    }

    if(dev->cfg.data_interval > MAX_DEVICE_DATA_INTERVAL_S)
    {
        return 2;
    }

    if(dev->cfg.heartbeat_interval < MIN_DEVICE_HEARTBEAT_INTERVAL_S)
    {
        return 3;
    }
    
    if(dev->cfg.heartbeat_interval > MAX_DEVICE_HEARTBEAT_INTERVAL_S)
    {
        return 4;
    }

    switch(dev->cfg.mode)
    {
        case DEVICE_MODE_lowpower:
        case DEVICE_MODE_diagnostic:
        case DEVICE_MODE_standard:
            break;
        
        //invalid device mode
        default:
            return 6;
            break;
    }
    return 0;
}


outpost_config* devGetOutpostCfg(const virtualDev *dev)
{
    return dev->outpost_cfg;
}
