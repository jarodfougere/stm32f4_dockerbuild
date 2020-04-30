/**
  ******************************************************************************
  * @file           : usbd_cdc_if.h
  * @version        : v1.0_Cube
  * @brief          : Header for usbd_cdc_if.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__
#ifdef __cplusplus
extern "C"
{
#endif /* c linkage */
#include <stdint.h>

#include "cdc_user_if.h"

#define USB_CDC_DEFAULT_BAUDRATE 115200
#define USB_CDC_DEFAULT_STOPBITS 0x00 /* 1 stop bit */
#define USB_CDC_DEFAULT_PARITY 0x00   /* no parity */
#define USB_CDC_DEFAULT_DATABITS 0x08 /* 8 data bits */

    /**
 * @brief Sets the contents of the user CDC TX endpoint as a payload
 * in the CDC Interface TX endpoint.
 * The value of Len is updated to the number of bytes successfully loaded
 * into the CDC interface TX endpoint buffer.
 * 
 * @param Len  Pointer to uint32_t containing the size of the user payload.
 * @return int8_t success : USBD_OK , else : USBD_FAIL
 */
    int8_t CDC_set_payload(int *Len);

    /**
 * @brief Transmits a single payload from the head of the CDC IF Payload queue.
 * @return int8_t Success: USBD_OK, else : USBD_FAIL
 */
    int8_t CDC_transmit_payload(void);

    /**
 * @brief Transmit a byte array of known size out of the USB CDC TX endpoint.
 * 
 * @param Buf The byte array
 * @param Len The size of the byte array
 * @return uint8_t success: USBD_OK, else : USBD_FAIL
 */
    uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len);

    /**
 * @brief Check how many tx payloads have been loaded into the CDC tx buffer.
 * caller can then decide how many payloads they want to transmit.
 * 
 * @return unsigned int : Number of payloads in CDC interface transmit buffer.
 */
    unsigned int CDC_peek_num_payloads_out(void);

    /**
 * @brief Initialize the user Receive endpoint for the CDC interface
 * 
 * @param user : struct cdc_user_if
 */
    void CDC_setUserRxEndPt(const struct cdc_user_if *user);

    /**
 * @brief Initialize the user Transmit endpoint for the CDC interface
 * 
 * @param user : struct cdc_user_if
 */
    void CDC_setUserTxEndPt(const struct cdc_user_if *user);

    /**
 * @brief Get the last unread command string from the CDC ring buffer.
 * 
 * @return int success: USBD_OK, else USBD_FAIL
 */
    int CDC_getCommandString(void);

#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* __USBD_CDC_IF_H__ */
