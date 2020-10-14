#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#include "usbd_cdc.h"
#define APP_RX_DATA_SIZE 2048
#define APP_TX_DATA_SIZE 2048

#define USB_DELIMIT_STRING "\r\n"

extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;

uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len);
uint8_t CDC_getCommandString(uint8_t *Buf, uint16_t Len);


#ifdef __cplusplus
}
#endif
#endif /* __USBD_CDC_IF_H__ */
