#ifndef __SYSTEMCONFIG_H__
#define __SYSTEMCONFIG_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include "cmsis_compiler.h"

#define USER_DEVICE_NAME_SIZE 50

#define DEVICE_NAME_STRING "Low Power Sensor Card"
#define DEVICE_MODEL_STRING "Low Power Sensor Card V1"
#define FWID_RELEASE "0.1"
#define HWVERSION_MAJOR 1
#define HWVERSION_MINOR 0

#define OUTPOST_ID_STRLEN 6 // ex 02xxxx


#define DEFAULT_RUNTICK_INTERVAL_S (60)
#define MIN_RUNTICK_INTERVAL_S (30)
#define MAX_RUNTICK_INTERVAL_S (UINT32_MAX)

#define DEFAULT_DCIN_INFO_INTERVAL_S (60)
#define MIN_DCIN_INFO_INTERVAL_S (30)
#define MAX_DCIN_INFO_INTERVAL_S (UINT32_MAX)

#define MAX_DIGITAL_INS 8
#define MAX_DIGITAL_OUTS 4
#define MAX_ANALOG_INS 4
#define MAX_RF_SENSORS 2
#define MAX_MOTH_SENSORS 1


#include "pinConfig.h"

typedef struct
{
    int32_t       debounce; // debounce time in multiples of 100ms.
    triggerType_t triglvl;  // trigger level (rising or falling edge)
} __PACKED inputInterface_t;

typedef enum
{
    INVALID_RELAY_STATE = 0xff,
    OPEN                = 0x00,
    CLOSED              = 0x01,
} relayState_t;


typedef struct
{
    uint32_t holdTime; // hold time in intervals of 100ms. 0xffff is toggle mode
    relayState_t defaultState;
    relayState_t currentState;
    uint32_t     _reserved;
} __PACKED relayInterface_t;


typedef struct
{
    pinConfig_t      cfg;
    inputInterface_t interface;
    uint32_t         _reserved;
} __PACKED digitalInput_t;


typedef struct
{
    pinConfig_t      cfg;       /* 13 */
    relayInterface_t interface; /* 5 */
    uint32_t         _reserved; /* 4 */
} __PACKED relayOutput_t;


typedef struct
{
    uint32_t samplePeriod;
    uint16_t battType;
    uint16_t redHigh;
    uint16_t redLow;
    uint16_t yellowHigh;
    uint16_t yellowLow;
    uint32_t _reserved;
} __PACKED analogInInterface_t;


typedef struct
{
    pinConfig_t         cfg;
    analogInInterface_t interface;
    uint32_t            _reserved;
} __PACKED analogInput_t;


typedef struct
{
    char           outpostID[OUTPOST_ID_STRLEN];
    uint16_t       _reserved;
    uint32_t       runTickInterval;
    uint32_t       pinInfoInterval;
    digitalInput_t digitalIns[MAX_DIGITAL_INS];
    relayOutput_t  relays[MAX_DIGITAL_OUTS];
    analogInput_t  analogIns[MAX_ANALOG_INS];
} __PACKED systemConfig_t;

extern systemConfig_t       systemconfig_heap;
extern const systemConfig_t systemconfig;
extern const systemConfig_t systemconfig_defaults;

extern uint32_t runtick;

void jumpToBootloader(void);
void systemReset(void);


/**
 * @brief Set the device name
 *
 * @param new_name the new name for the device
 * @return int 0 on success, -1 on failure
 */
int setDeviceName(const char *new_name);


/**
 * @brief Get the Device Name
 *
 * @return char* device name
 */
char *getDeviceName(void);


/**
 * @brief Checks if the system is configured to bootjump on next reboot
 *
 * @return true if configured to jump to bootloader, otherwise false
 */
bool should_bootjump(void);


/**
 * @brief Perform a control transfer to the bootloader burned into system mem
 * @note  CALLER IS RESPONSIBLE TO DISABLE THE REQUIRED PERIPHERALS BEFORE
 *        EXECUTING THE BOOTJUMP
 */
void bootjump(void);


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __SYSTEMCONFIG_H__ */
