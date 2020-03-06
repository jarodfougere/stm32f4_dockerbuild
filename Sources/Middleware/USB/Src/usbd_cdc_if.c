/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v1.0_Cube
  * @brief          : Usb device for Virtual Com Port.
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#if defined(MCU_APP)
#include "drivers.h"
#endif /* MCU_APP */
#include "usbd_cdc_if.h"

/* Define size for the receive and transmit buffer over CDC */
#define APP_RX_DATA_SIZE 2048
#define APP_TX_DATA_SIZE 2048

/* Create buffer for reception and transmission           */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

#if defined(MCU_APP)
extern USBD_HandleTypeDef hUsbDeviceFS;
#endif /* MCU_APP */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);

/* Function ptr struct for interface operations */
USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
    CDC_Init_FS,
    CDC_DeInit_FS,
    CDC_Control_FS,
    CDC_Receive_FS
};

/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{   
    #if defined(MCU_APP)
    /* Set Application Buffers */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
    #else 
    usb_printf("Executing CDC_Init_FS\n");
    #endif /* MCU_APP */
    return (USBD_OK);
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{   
    #if defined(MCU_APP)
    #else 
    #endif /* MCU_APP */
    return (USBD_OK);
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
    switch (cmd)
    {
    case CDC_SEND_ENCAPSULATED_COMMAND:

        break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

        break;

    case CDC_SET_COMM_FEATURE:

        break;

    case CDC_GET_COMM_FEATURE:

        break;

    case CDC_CLEAR_COMM_FEATURE:

        break;

        /*******************************************************************************/
        /* Line Coding Structure                                                       */
        /*-----------------------------------------------------------------------------*/
        /* Offset | Field       | Size | Value  | Description                          */
        /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
        /* 4      | bCharFormat |   1  | Number | Stop bits                            */
        /*                                        0 - 1 Stop bit                       */
        /*                                        1 - 1.5 Stop bits                    */
        /*                                        2 - 2 Stop bits                      */
        /* 5      | bParityType |  1   | Number | Parity                               */
        /*                                        0 - None                             */
        /*                                        1 - Odd                              */
        /*                                        2 - Even                             */
        /*                                        3 - Mark                             */
        /*                                        4 - Space                            */
        /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
        /*******************************************************************************/
    case CDC_SET_LINE_CODING:

        break;

    case CDC_GET_LINE_CODING:

        break;

    case CDC_SET_CONTROL_LINE_STATE:

        break;

    case CDC_SEND_BREAK:

        break;

    default:
        break;
    }

    return (USBD_OK);
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before
  *         transfer
  *         is complete on CDC interface (ie. using DMA controller) it will
  *         result in receiving more data while previous ones are still not
  *         sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else
  *         USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{   
    #if defined(MCU_APP)
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
    USBD_CDC_ReceivePacket(&hUsbDeviceFS);
    return (USBD_OK);
    #else 
    /* check for reception success/buffer overrun */
    return NULL == fgets((char* )Buf, *Len, stdin) ? USBD_FAIL : USBD_OK; 
    #endif /* MCU_APP */
}

/**
  * @brief  usb_print
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t usb_print(uint8_t *Buf, uint16_t Len)
{   
    uint8_t result = USBD_OK;
    if(0 == Len || NULL == Buf) /* Idiotproofing */
    {
        result = USBD_FAIL;
    }
    else
    {
#if defined(MCU_APP)
    result = USBD_OK;

    /* DO NOT REMOVE THIS. DATA LINE FORMATING IS DEVICE CLASS SPECIFIC */
    USBD_CDC_HandleTypeDef *hcdc = 
    (USBD_CDC_HandleTypeDef *)hUsbDeviceFS.pClassData; 
    /* cast to CDC class from generic class */
    
    /* if peripheral is busy transmitting */
    if (hcdc->TxState != 0) 
    {   
        /* simply return. user can decide if they want to block or not */
        return USBD_BUSY;
    }

    /* transfer payload into tx buffer and transmit */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
    result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
#else
    /* Theres no easy way to print a finite size. 
     *
     * I thought about doing snprintf into a buffer but typically a host 
     * system will not be resource limited like an MCU so simply printing 
     * here 
     * will suffice 
     */

    /* check if the transmit was successful */
    result = printf("%s", Buf) > 0 ? USBD_OK : USBD_FAIL; 
#endif
    }
    return result;
}

/**
 * @brief This function transmits serial data via the USB peripheral
 * 
 * @param format printf-style format specifier 
 * @param ...    printf-style format parameters
 * @return uint8_t indicating transmission success, periph busy, or failure.
 */
uint8_t usb_printf(const char *restrict format, ...)
{
    va_list args;
    va_start(args, format);
    uint8_t result = USBD_OK;
    const size_t tx_buf_offset = strlen((const char*)UserTxBufferFS) + 1;

    /* load into the tx buffer based on the provided format */
    vsnprintf((char*)(UserTxBufferFS + tx_buf_offset), sizeof(UserTxBufferFS) - tx_buf_offset, format, args);

    /* transmit */
    result = usb_print(UserTxBufferFS + tx_buf_offset, strlen((const char*)UserTxBufferFS + tx_buf_offset));

    va_end(args); /* end variable argument handler */
    return result;
}

