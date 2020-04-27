#ifndef __USB_DFU_H
#define __USB_DFU_H
#ifdef __cplusplus
 extern "C" {
#endif /* C linkage */

#include  "usbd_ioreq.h"
#include  "usbd_desc.h"

#ifndef USBD_DFU_MAX_ITF_NUM
#define USBD_DFU_MAX_ITF_NUM            1U
#endif /* USBD_DFU_MAX_ITF_NUM */

#ifndef USBD_DFU_XFER_SIZE
#define USBD_DFU_XFER_SIZE             1024U
#endif /* USBD_DFU_XFER_SIZE */

#ifndef USBD_DFU_APP_DEFAULT_ADD

/* The first sector (32 KB) is reserved for DFU code */
#define USBD_DFU_APP_DEFAULT_ADD       0x08008000U 

#endif /* USBD_DFU_APP_DEFAULT_ADD */

#define USB_DFU_CONFIG_DESC_SIZ  (18U + (9U * USBD_DFU_MAX_ITF_NUM))
#define USB_DFU_DESC_SIZ         9U
#define DFU_DESCRIPTOR_TYPE      0x21U


/**************************************************/
/* DFU Requests  DFU states                       */
/**************************************************/
typedef enum 
{
    DFU_STATE_idle                = 2U, 
    DFU_STATE_dnload_sync         = 3U, 
    DFU_STATE_dnload_busy         = 4U, 
    DFU_STATE_dnload_idle         = 5U, 
    DFU_STATE_manifest_sync       = 6U, 
    DFU_STATE_manifest            = 7U, 
    DFU_STATE_manifest_wait_reset = 8U, 
    DFU_STATE_upload_idle         = 9U, 
    DFU_STATE_error               = 10U,
}   DFU_STATE_t;

#define APP_STATE_IDLE              0U
#define APP_STATE_DETACH            1U

/**************************************************/
/* DFU errors                                     */
/**************************************************/
typedef enum
{
    DFU_ERROR_none          = 0x00U,
    DFU_ERROR_target        = 0x01U,
    DFU_ERROR_file          = 0x02U,
    DFU_ERROR_write         = 0x03U,
    DFU_ERROR_erase         = 0x04U,
    DFU_ERROR_checkErase    = 0x05U,
    DFU_ERROR_prog          = 0x06U,
    DFU_ERROR_verify        = 0x07U,
    DFU_ERROR_address       = 0x08U,
    DFU_ERROR_notdone       = 0x09U,
    DFU_ERROR_firmware      = 0x0AU,
    DFU_ERROR_vendor        = 0x0BU,
    DFU_ERROR_usb           = 0x0CU,
    DFU_ERROR_PwrOnRst      = 0x0DU,
    DFU_ERROR_unknown       = 0x0EU,
    DFU_ERROR_stalledPacket = 0x0FU,
}   DFU_ERROR_t;


/**************************************************/
/* DFU Manifestation State                        */
/**************************************************/
#define DFU_MANIFEST_COMPLETE          0x00U
#define DFU_MANIFEST_IN_PROGRESS       0x01U


/**************************************************/
/* Special Commands  with Download Request        */
/**************************************************/
#define DFU_CMD_GETCOMMANDS            0x00U
#define DFU_CMD_SETADDRESSPOINTER      0x21U
#define DFU_CMD_ERASE                  0x41U

#define DFU_MEDIA_ERASE                0x00U
#define DFU_MEDIA_PROGRAM              0x01U

/**************************************************/
/* Other defines                                  */
/**************************************************/
/* Bit Detach capable = bit 3 in bmAttributes field */
#define DFU_DETACH_MASK                (uint8_t)(1 << 4)
#define DFU_STATUS_DEPTH               6U

typedef enum
{
    DFU_DETACH = 0U,
    DFU_DNLOAD ,
    DFU_UPLOAD,
    DFU_GETSTATUS,
    DFU_CLRSTATUS,
    DFU_GETSTATE,
    DFU_ABORT
}   DFU_t;

typedef  void (*pFunction)(void);

/**********  Descriptor of DFU interface 0 Alternate setting n ****************/
#define USBD_DFU_IF_DESC(n) \
0x09,                       /* bLength: Interface Descriptor size */          \
USB_DESC_TYPE_interface,    /* bDescriptorType */                             \
0x00,                       /* bInterfaceNumber: Number of Interface */       \
(n),                        /* bAlternateSetting: Alternate setting */        \
0x00,                       /* bNumEndpoints*/                                \
0xFE,                       /* bInterfaceClass: App-Specific Class Code */    \
0x01,                       /* bInterfaceSubClass : Device FW Upgrade Code */ \
0x02,                       /* nInterfaceProtocol: DFU mode protocol */       \
USBD_STRIDX_interface + (n) + 1U /* iInterface: Index of string descriptor */ \



#define TRANSFER_SIZE_BYTES(size)       \
((uint8_t)(size)),  /* XFERSIZEB0 */    \
((uint8_t)(size >> 8)) /* XFERSIZEB1 */

#define IS_PROTECTED_AREA(add)          \
(uint8_t)(((add >= 0x08000000) && (add < (APP_DEFAULT_ADD)))? 1:0)


typedef struct
{
    union
    {
        uint32_t d32[USBD_DFU_XFER_SIZE / 4U];
        uint8_t  d8[USBD_DFU_XFER_SIZE];
    } buffer;

    uint32_t             wblock_num;
    uint32_t             wlength;
    uint32_t             data_ptr;
    uint32_t             alt_setting;

    uint8_t              dev_status[DFU_STATUS_DEPTH];
    uint8_t              ReservedForAlign[2];
    uint8_t              dev_state;
    uint8_t              manif_state;
}   USBD_DFU_HandleTypeDef;

typedef struct
{
    const uint8_t* pStrDesc;
    uint16_t (* Init)     (void);
    uint16_t (* DeInit)   (void);
    uint16_t (* Erase)    (uint32_t Add);
    uint16_t (* Write)    (uint8_t *src, uint8_t *dest, uint32_t Len);
    uint8_t* (* Read)     (uint8_t *src, uint8_t *dest, uint32_t Len);
    uint16_t (* GetStatus)(uint32_t Add, uint8_t cmd, uint8_t *buff);
}   USBD_DFU_MediaTypeDef;


extern USBD_ClassTypeDef  USBD_DFU;
#define USBD_DFU_CLASS    &USBD_DFU

uint8_t  USBD_DFU_RegisterMedia    (USBD_HandleTypeDef   *pdev,
                                    USBD_DFU_MediaTypeDef *fops);
#ifdef __cplusplus
}
#endif  /* C linkage */
#endif  /* __USB_DFU_H */
