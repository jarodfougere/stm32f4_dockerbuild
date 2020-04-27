#ifndef RIMOT_USB_DRIVER_CONFIG
#define RIMOT_USB_DRIVER_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USBD_MAX_NUM_INTERFACES     1U
#define USBD_MAX_NUM_CONFIGURATION  1U
#define USBD_MAX_STR_DESC_SIZ       512U
#define USBD_DEBUG_LEVEL            0U
#define USBD_LPM_ENABLED            0U
#define USBD_SELF_POWERED           1U

#include "rimot_usb.h"

void usbDeviceDriver_SOFCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_SetupStageCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_SuspendCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_ResumeCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_ConnectCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_DisconnectCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_ResetCallback(usbDriverHandle_t *hpcd);
void usbDeviceDriver_DataInStageCallback(usbDriverHandle_t *hpcd, 
                                         uint8_t epnum);
void usbDeviceDriver_DataOutStageCallback(usbDriverHandle_t *hpcd, 
                                          uint8_t epnum);
void usbDeviceDriver_ISOOUTIncompleteCallback(usbDriverHandle_t *hpcd, 
                                              uint8_t epnum);
void usbDeviceDriver_ISOINIncompleteCallback(usbDriverHandle_t *hpcd, uint8_t epnum);


/* #define for FS and HS identification */
#define DEVICE_FS 		0
#define DEVICE_HS 		1

#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* RIMOT_USB_DRIVER_CONFIG */










