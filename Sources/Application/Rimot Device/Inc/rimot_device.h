#ifndef RIMOT_RIMOT_DEVICE
#define RIMOT_RIMOT_DEVICE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "system_interface.h"
#include "outpost_config.h"

//USER CONFIGURES THESE BASED ON THE RELEASE
#define FIRMWARE_STRING  "0.1.0"
#define HARDWARE_STRING  "1.0.0"

//BOUNDARIES FOR HOW FREQUENTLY THE DEVICE SENDS SYSTICK
#define DEFAULT_DEVICE_HEARTBEAT_INTERVAL_S 60  //once a minute
#define MAX_DEVICE_HEARTBEAT_INTERVAL_S     300 //once every 5 minutes
#define MIN_DEVICE_HEARTBEAT_INTERVAL_S     30  //once every 30 seconds

//BOUNDARIES FOR HOW FREQUENTLY THE DEVICE SENDS ITS DATA PAYLOAD
#define DEFAULT_DEVICE_DATA_INTERVAL_S      60  //once a minute
#define MAX_DEVICE_DATA_INTERVAL_S          150 //once every 2.5minutes
#define MIN_DEVICE_DATA_INTERVAL_S          10  //once every 10 seconds

typedef enum
{
    DEVICE_STATE_boot,
    DEVICE_STATE_active,
    DEVICE_STATE_resetting,
    DEVICE_STATE_fault,
}   DEVICE_STATE_t;


typedef enum
{
    DEVICE_MODE_standard,
    DEVICE_MODE_lowpower,
    DEVICE_MODE_diagnostic,
}   DEVICE_MODE_t;

typedef struct rimot_device_structure virtualDev;

virtualDev* virtualDevInit(void);
DEVICE_STATE_t devGetState(const virtualDev *dev);
void devSetState(virtualDev *dev, DEVICE_STATE_t state);
void devSetCfgHbInterval(virtualDev *dev, uint32_t hbInterval);
uint32_t devGetHbInterval(const virtualDev *dev);
void devSetCfgDataInterval(virtualDev *dev, uint32_t dataInterval);
uint32_t devGetCfgDataInterval(const virtualDev *dev);
void devSetCfgMode(virtualDev *dev, uint32_t mode);
uint32_t devGetCfgMode(const virtualDev *dev);
outpost_config* devGetOutpostCfg(const virtualDev *dev);



#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RIMOT_DEVICE */