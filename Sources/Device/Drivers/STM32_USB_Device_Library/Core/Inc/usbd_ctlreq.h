#ifndef __USB_REQUEST_H
#define __USB_REQUEST_H
#ifdef __cplusplus /* clinkage */
 extern "C" {
#endif /* C linkage */

#include <stdint.h> 

#include  "usbd_def.h"

#define USB_REQ_GET_STATUS 0x00U
#define USB_REQ_CLEAR_FEATURE 0x01U
#define USB_REQ_SET_FEATURE 0x03U
#define USB_REQ_SET_ADDRESS 0x05U
#define USB_REQ_GET_DESCRIPTOR 0x06U
#define USB_REQ_SET_DESCRIPTOR 0x07U
#define USB_REQ_GET_CONFIGURATION 0x08U
#define USB_REQ_SET_CONFIGURATION 0x09U
#define USB_REQ_GET_INTERFACE 0x0AU
#define USB_REQ_SET_INTERFACE 0x0BU
#define USB_REQ_SYNCH_FRAME 0x0CU

typedef enum
{
    USB_REQTYPE_standard = 0X00U,
    USB_REQTYPE_class    = 0X2U,
    USB_REQTYPE_vendor   = 0X4U,
    USB_REQTYPE_mask     = 0X6U,
}   USB_REQTYPE_t;


typedef enum
{
    USB_REQ_RECIPIENT_device    = 0x00U,
    USB_REQ_RECIPIENT_interface = 0x01U,
    USB_REQ_RECIPIENT_endpoint  = 0x02U,
    USB_REQ_RECIPIENT_mask      = 0x03U,
}   USB_REQ_RECIPIENT_t;

USBD_StatusTypeDef  USBD_StdDevReq (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef  *req);
USBD_StatusTypeDef  USBD_StdItfReq (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef  *req);
USBD_StatusTypeDef  USBD_StdEPReq  (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef  *req);


void USBD_CtlError  (USBD_HandleTypeDef  *pdev, USBD_SetupReqTypedef *req);

void USBD_ParseSetupRequest (USBD_SetupReqTypedef *req, uint8_t *pdata);

void USBD_GetString         (uint8_t *desc, uint8_t *unicode, uint16_t *len);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* __USB_REQUEST_H */
