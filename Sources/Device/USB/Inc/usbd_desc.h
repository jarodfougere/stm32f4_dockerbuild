#ifndef __USBD_DESC__C__
#define __USBD_DESC__C__
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */

#include <stdint.h>

#include "usbd_def.h"
#include "rimot_region_base_addresses.h"

/* UID ALIASES */
#define         DEVICE_ID1          (UID_BASE)
#define         DEVICE_ID2          (UID_BASE + 0x4)
#define         DEVICE_ID3          (UID_BASE + 0x8)

#define USB_SIZ_STRING_SERIAL           0x1AU
#define USB_LEN_DEV_QUALIFIER_DESC      0x0AU
#define USB_LEN_DEV_DESC                0x12U
#define USB_LEN_CFG_DESC                0x09U
#define USB_LEN_IF_DESC                 0x09U
#define USB_LEN_EP_DESC                 0x07U
#define USB_LEN_OTG_DESC                0x03U
#define USB_LEN_LANGID_STR_DESC         0x04U
#define USB_LEN_OTHER_SPEED_DESC_SIZ    0x09U

typedef enum
{
    USB_DESC_TYPE_device            = 0x01U,
    USB_DESC_TYPE_configuration     = 0x02U,
    USB_DESC_TYPE_string            = 0x03U,
    USB_DESC_TYPE_interface         = 0x04U,
    USB_DESC_TYPE_endpoint          = 0x05U,
    USB_DESC_TYPE_devQualifier      = 0x06U,
    USB_DESC_TYPE_otherSpeedConfig  = 0x07U,
    USB_DESC_TYPE_bos               = 0x0FU,
}   USB_DESC_TYPE_t;


typedef enum
{
    USBD_STRIDX_langId    = 0x00U,
    USBD_STRIDX_mfc       = 0x01U,
    USBD_STRIDX_product   = 0x02U,
    USBD_STRIDX_serial    = 0x03U,
    USBD_STRIDX_config    = 0x04U,
    USBD_STRIDX_interface = 0x05U,
}   USBD_STRIDX_t;

extern USBD_DescriptorsTypeDef FS_Desc;

#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* __USBD_DESC__C__ */
