/**
 * @file usbd_cdc_if.c
 * @author Carl Mattatall
 * @brief  This file implements the USB CDC class interface
 * using STM32USB device library drivers. The interface
 * supports additional line encodings and request/responses
 * for the OTG Peripheral. It was built using the GPIO controller
 * usbd_cdc_if.c as a reference.
 * 
 * @version 0.1
 * @date 2020-03-18
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h> /* memcpy */

#if defined(MCU_APP)
#include "drivers.h"
#endif /* MCU_APP */
#include "usbd_cdc_if.h"
#include "task_state.h"
extern volatile enum task_state *task_states[NUM_TASKS];

#define USB_DELIM '\r' /* Carriage return acts as a delimiter */
#define USB_IF_RX_BUF_SIZE 2048

/* 3 times the rx buffer size because gpio + rf + moth payloads */
#define USB_IF_TX_BUF_SIZE 3 * USB_IF_RX_BUF_SIZE

/* Actual buffers for USB transmit and Receive */
static uint8_t usb_if_tx_buf[USB_IF_TX_BUF_SIZE];
static uint8_t usb_if_rx_buf[USB_IF_RX_BUF_SIZE];
static uint8_t *usb_rx_outptr;
static uint8_t *usb_rx_inptr;

/* static function declarations */
static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);

/* user rx buffer exposed outside */
uint8_t usb_rx_buf_USER[USB_USER_COMMAND_STRING_BUF_SIZE];

extern USBD_HandleTypeDef hUsbDeviceFS;

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
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, usb_if_tx_buf, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, usb_if_rx_buf);
    usb_rx_outptr = usb_rx_buf_USER;
    usb_rx_inptr = usb_rx_buf_USER;
#else
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
  * @retval Result of the operation: USBD_OK if all operations are OK else
  *  USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{   
    static USBD_CDC_LineCodingTypeDef LineCoding =
    {
        115200, /* baud rate     */
        0x00,   /* stop bits-1   */
        0x00,   /* parity - none */
        0x08    /* 8 data bits   */
    };
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
        /**
         * @brief The table below describes the necessary struct
         * bit fields to enumerate
         * as a CDC class (class sub descriptor) once the usb OTG peripheral
         * has been established as a device in the device-root-tree of its 
         * host.
         * 
         * This beautiful table was brought to you by 20 minutes of frustration
         */

        /**********************************************************************/
        /*|------------------------------------------------------------------|*/
        /*|                 USB line coding structure and format             |*/
        /*|--------+-------------+--------------+---------+------------------|*/
        /*| Offset |  Field      | Size (bytes) |  Value  |  Description     |*/
        /*|--------+-------------+--------------+---------+------------------|*/
        /*|        |             |              |         | Data terminal    |*/
        /*|    0   |  dwDTERate  |       4      | number  | rate in bits per |*/
        /*|        |             |              |         | second           |*/
        /*|--------+-------------+--------------+---------+------------------|*/
        /*|        |             |              |         | Nun Stop bits    |*/
        /*|    4   | bCharFormat |       1      | number  | 0: 1 stop bit    |*/
        /*|        |             |              |         | 1: 1.5 stop bits |*/
        /*|        |             |              |         | 2: 2 stop bits   |*/
        /*|--------+-------------+--------------+---------+------------------|*/
        /*|        |             |              |         | Parity:          |*/
        /*|        |             |              |         | 0: None          |*/
        /*|    5   | bParityType |      1       | number  | 1: Odd           |*/
        /*|        |             |              |         | 2: Even          |*/
        /*|        |             |              |         | 3: Mark          |*/
        /*|        |             |              |         | 3: Space         |*/
        /*|--------+-------------+--------------+---------+------------------|*/
        /*|        |             |              |         | Num data bits    |*/
        /*|    6   | bDataBits   |      1       |  number | Valid values are |*/
        /*|        |             |              |         | 5, 6, 7, 8, 16   |*/
        /*|--------+-------------+--------------+---------+------------------|*/
        /**********************************************************************/
    case CDC_SET_LINE_CODING:
        LineCoding.bitrate    = (uint32_t)(pbuf[0] |
                                (pbuf[1] << 8)     |
                                (pbuf[2] << 16)    |
                                (pbuf[3] << 24));
        LineCoding.format     = pbuf[4];
        LineCoding.paritytype = pbuf[5];
        LineCoding.datatype   = pbuf[6];
        break;
    case CDC_GET_LINE_CODING:
        pbuf[0] = (uint8_t)(LineCoding.bitrate);
        pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
        pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
        pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
        pbuf[4] = LineCoding.format;
        pbuf[5] = LineCoding.paritytype;
        pbuf[6] = LineCoding.datatype;
        break;
    case CDC_SET_CONTROL_LINE_STATE:
        /* change in the control line state means we unblock the serial task */
        *task_states[task_index_serial] = TASK_STATE_ready; 
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
  *         transfer is complete on CDC interface (ie. using DMA controller) 
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received (caller provided)
  * 
  * @param  Len: Upon return, contains number of bytes that 
  *             would have been copied if the provided buffer was large
  *             enough. Caller must provide *Len on input with desired number
  *             of bytes to be copied.
  * @retval Result of the operation: USBD_OK if all operations are OK, else
  *         USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{
    /* return status */
    USBD_StatusTypeDef status = USBD_OK;

    /* idiotproofing. */
    if ((NULL != Buf) && (NULL != Len) && (*Len != 0))
    {
#if defined(MCU_APP)
        USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
        USBD_CDC_ReceivePacket(&hUsbDeviceFS);

        /* copy bytes into receive buffer and test for command terminator */
        uint32_t i = 0;
        do
        {
            /* copy byte into command buffer */
            *usb_rx_inptr++ = Buf[i];

            /* check if this is a command terminator character */
            if (Buf[i] == '\r')
            {   
                /* serial task has received data and is no longer blocked */
                *task_states[task_index_serial] = TASK_STATE_ready;
            }

            /* buffer pointer management */
            if (usb_rx_inptr >= usb_rx_buf_USER + sizeof(usb_rx_buf_USER))
            {
                usb_rx_inptr = usb_rx_buf_USER;
            }
        } while (++i < *Len);

#else
        /* for OS-hosted application, check for buffer overrun through stdin */
        return NULL == fgets((char *)Buf, *Len, stdin) ? USBD_FAIL : USBD_OK;
#endif /* MCU_APP */
    }
    else
    {
        status = USBD_FAIL;
    }
    return (int8_t)status; /* cast so compiler stops complainin on -Wall */
}

uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len)
{
    uint8_t result = USBD_OK;
    if ((0 == Len) || (NULL == Buf)) /* Idiotproofing */
    {
        result = USBD_FAIL;
    }
    else
    {
#if defined(MCU_APP)
        result = USBD_OK;

        USBD_CDC_HandleTypeDef *hcdc =
            (USBD_CDC_HandleTypeDef *)hUsbDeviceFS.pClassData;

        /* if peripheral is busy transmitting */
        if (hcdc->TxState != 0)
        {
            /* simply return. caller can decide if they want to block or not */
            return USBD_BUSY;
        }

        /* transfer payload into tx buffer and transmit */
        USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
        result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
#else
        result = printf("[USB CDC] : %s", Buf) > 0 ? USBD_OK : USBD_FAIL;
#endif
    }
    return result;
}


/**
 * @brief Copies the contents of the User Command String
 * Buffer into Buf.
 * 
 * @param Buf 
 * @param Len 
 * @return uint8_t 
 */
uint8_t CDC_GetCommandString(uint8_t *Buf, uint16_t Len)
{
    uint8_t status = 0;
    uint16_t i = 0;
    uint8_t flag = 0;

    /* check for API error */
    if (Len < 1)
    {
        status = 1;
    }
    else
    {
        do
        {
            Buf[i] = *usb_rx_outptr;    /* copy next byte */
            if (*usb_rx_outptr == '\r') /* check for delim */
            {
                Buf[i + 1] = '\0'; /* nul term and set flag */
                flag = 1;
            }

            if (++usb_rx_outptr >= (usb_rx_buf_USER + sizeof(usb_rx_buf_USER)))
            {
                usb_rx_outptr = usb_rx_buf_USER;
            }
        } while ((++i < Len) && (flag == 0));

        /* check if data fit in buffer, return 0 on error */
        if (flag == 0)
        {
            status = 1;
        }
    }
    return status;
}

/*******************************************************************************
 * @fn      CDC_sendJSON
 *
 * @brief   Sends single JSON formatted key/value on serial port
 *
 * @param   key     ... key text string
 *          value   ... value text string
 *
 * @return  Result of the operation: USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
 ******************************************************************************/
uint8_t CDC_sendJSON(char *key, char *value)
{
    uint8_t result = USBD_FAIL;
    char str[120] = {0};
    int slen;
    slen = sprintf(str, "{\"%s\":\"%s\"}\r\n", key, value);
    if (slen > 0)
    {
        result = CDC_Transmit_FS((uint8_t *)str, slen);
    }
    return result;
}
