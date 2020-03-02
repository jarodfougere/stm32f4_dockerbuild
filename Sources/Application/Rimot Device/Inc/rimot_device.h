#ifndef RIMOT_RIMOT_DEVICE
#define RIMOT_RIMOT_DEVICE
#include <stdint.h>

#include "rimot_device_config.h"
#include "system_config.h"
#include "outpost_config.h"

//USER CONFIGURES THESE BASED ON THE RELEASE
#define FIRMWARE_STRING  "0.1.0"
#define HARDWARE_STRING  "1.0.0"

#if defined(MCU_APP)
#define DEVICE_UID       {      \
    (char)(UID_BASE + 0),       \
    (char)(UID_BASE + 0x01),    \
    (char)(UID_BASE + 0x02),    \
    (char)(UID_BASE + 0x03),    \
    (char)(UID_BASE + 0x04),    \
    (char)(UID_BASE + 0x05),    \
    (char)(UID_BASE + 0x06),    \
    (char)(UID_BASE + 0x07),    \
    (char)(UID_BASE + 0x08),    \
    (char)(UID_BASE + 0x09),    \
    (char)(UID_BASE + 0x0a),    \
    (char)(UID_BASE + 0x0b),    \
    (char)('\0')                \
    }
#else
#define DEVICE_UID "DEVICE_UID_STRING"
#endif
#define UID_LEN sizeof(DEVICE_UID) /* WE MAY EVENTUALLY USE SNPRINTF */

struct rimot_device 
{   
    struct rimot_dev_cfg  device_config;   /* device configuration         */
    struct system_config  system_config;   /* interface configurations     */
    struct outpost_config outpost_config;  /* config of assigned outpost   */
};

#define RIMOT_DEV_DFLT_INITIALIZER {                        \
    .outpost_config = OUTPOST_CFG_DFLT_INITIALIZER,         \
    .device_config  = RIMOT_DEV_CFG_DFLT_INITIALIZER,       \
    .system_config  = SYS_CFG_DFLT_INITIALIZER,             \
}

int32_t update_device_config(   struct rimot_dev_cfg *dest_cfg, 
                                const struct rimot_dev_cfg *src_cfg);

#endif