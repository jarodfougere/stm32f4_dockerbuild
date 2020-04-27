#ifndef __USBD_DEF_H
#define __USBD_DEF_H
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include "usbd_conf.h"

#ifndef NULL
#define NULL 0U
#endif /* NULL */

#ifndef USBD_MAX_NUM_INTERFACES
#define USBD_MAX_NUM_INTERFACES 1U
#endif /* USBD_MAX_NUM_CONFIGURATION */

#ifndef USBD_MAX_NUM_CONFIGURATION
#define USBD_MAX_NUM_CONFIGURATION 1U
#endif /* USBD_MAX_NUM_CONFIGURATION */

#ifndef USBD_LPM_ENABLED
#define USBD_LPM_ENABLED 0U
#endif /* USBD_LPM_ENABLED */

#ifndef USBD_SELF_POWERED
#define USBD_SELF_POWERED 1U
#endif /*USBD_SELF_POWERED */

#ifndef USBD_SUPPORT_USER_STRING
#define USBD_SUPPORT_USER_STRING 1U
#endif /* USBD_SUPPORT_USER_STRING */

typedef struct usb_setup_req
{
    uint8_t bmRequest;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} USBD_SetupReqTypedef;

struct _USBD_HandleTypeDef;

typedef struct _Device_cb
{
    uint8_t (*Init)(struct _USBD_HandleTypeDef *pdev, uint8_t cfgidx);
    uint8_t (*DeInit)(struct _USBD_HandleTypeDef *pdev, uint8_t cfgidx);
    /* Control Endpoints*/
    uint8_t (*Setup)(struct _USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);
    uint8_t (*EP0_TxSent)(struct _USBD_HandleTypeDef *pdev);
    uint8_t (*EP0_RxReady)(struct _USBD_HandleTypeDef *pdev);
    /* Class Specific Endpoints*/
    uint8_t (*DataIn)(struct _USBD_HandleTypeDef *pdev, uint8_t epnum);
    uint8_t (*DataOut)(struct _USBD_HandleTypeDef *pdev, uint8_t epnum);
    uint8_t (*SOF)(struct _USBD_HandleTypeDef *pdev);
    uint8_t (*IsoINIncomplete)(struct _USBD_HandleTypeDef *pdev, uint8_t epnum);
    uint8_t (*IsoOUTIncomplete)(struct _USBD_HandleTypeDef *pdev, uint8_t epnum);

    uint8_t *(*GetHSConfigDescriptor)(uint16_t *length);
    uint8_t *(*GetFSConfigDescriptor)(uint16_t *length);
    uint8_t *(*GetOtherSpeedConfigDescriptor)(uint16_t *length);
    uint8_t *(*GetDeviceQualifierDescriptor)(uint16_t *length);
#if (USBD_SUPPORT_USER_STRING == 1U)
    uint8_t *(*GetUsrStrDescriptor)(struct _USBD_HandleTypeDef *pdev, uint8_t index, uint16_t *length);
#endif

}   USBD_ClassTypeDef;

/* Following USB Device Speed */
typedef enum
{
    USBD_SPEED_HIGH = 0U,
    USBD_SPEED_FULL = 1U,
    USBD_SPEED_LOW = 2U,
}   USBD_SpeedTypeDef;

/* Following USB Device status */
typedef enum
{
    USBD_OK = 0U,
    USBD_BUSY,
    USBD_FAIL,
} USBD_StatusTypeDef;

/* USB Device descriptors structure */
typedef struct
{
    uint8_t *(*GetDeviceDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
    uint8_t *(*GetLangIDStrDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
    uint8_t *(*GetManufacturerStrDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
    uint8_t *(*GetProductStrDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
    uint8_t *(*GetSerialStrDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
    uint8_t *(*GetConfigurationStrDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
    uint8_t *(*GetInterfaceStrDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
#if (USBD_LPM_ENABLED == 1U)
    uint8_t *(*GetBOSDescriptor)(USBD_SpeedTypeDef speed, uint16_t *length);
#endif
} USBD_DescriptorsTypeDef;

/* USB Device handle structure */
typedef struct
{
    uint32_t status;
    uint32_t is_used;
    uint32_t total_length;
    uint32_t rem_length;
    uint32_t maxpacket;
}   USBD_EndpointTypeDef;

/* USB Device handle structure */
typedef struct _USBD_HandleTypeDef
{
    uint8_t id;
    uint32_t dev_config;
    uint32_t dev_default_config;
    uint32_t dev_config_status;
    USBD_SpeedTypeDef dev_speed;
    USBD_EndpointTypeDef ep_in[15];
    USBD_EndpointTypeDef ep_out[15];
    uint32_t ep0_state;
    uint32_t ep0_data_len;
    uint8_t dev_state;
    uint8_t dev_old_state;
    uint8_t dev_address;
    uint8_t dev_connection_status;
    uint8_t dev_test_mode;
    uint32_t dev_remote_wakeup;
    USBD_SetupReqTypedef request;
    USBD_DescriptorsTypeDef *pDesc;
    USBD_ClassTypeDef *pClass;
    void *pClassData;
    void *pUserData;
    void *pData;
}   USBD_HandleTypeDef;


#define SWAPBYTE(addr) (((uint16_t)(*((uint8_t *)(addr)))) + \
                    (((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))

#define LOBYTE(x) ((uint8_t)(x & 0x00FFU))
#define HIBYTE(x) ((uint8_t)((x & 0xFF00U) >> 8U))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* ATTRIBUTE SPECIFIER BASED ON TOOLCHAIN */
#if defined(__GNUC__)
#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */

/* In HS mode and when the DMA is used, all variables and data structures dealing
with the DMA during the transaction process should be 4-bytes aligned */

/* ALIGNMENT SPEICIFER BASED ON TOOLCHAIN */

#if defined(__GNUC__) /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(4)))
#endif /* __ALIGN_END */
#define __ALIGN_BEGIN
#else
#define __ALIGN_END
#if defined(__CC_ARM) /* ARM Compiler */
#define __ALIGN_BEGIN __align(4)
#elif defined(__ICCARM__) /* IAR Compiler */
#define __ALIGN_BEGIN
#elif defined(__TASKING__) /* TASKING Compiler */
#define __ALIGN_BEGIN __align(4)
#endif /* __CC_ARM */
#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif /* C linkage */

#endif /* __USBD_DEF_H */

