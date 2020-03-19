/**
 * @file usbd_cdc_if.c
 * @author Carl Mattatall
 * @brief  This file implements the USB CDC class interface
 * using STM32USB Low Level drivers. The interface
 * supports additional line encodings and request/responses
 * for the OTG Peripheral. It was built using the GPIO controller
 * usbd_cdc_if.c as a reference. This is NOT to be confused with
 * the name of the template file template generated using 
 * STM32MXCUBE software (which as I have unfortunately learned, 
 * shares the exact same name).
 * @version 0.3
 * @date 2020-03-19
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

#define USB_IF_RX_BUF_SIZE 4096
#define USB_IF_TX_BUF_SIZE 2 * USB_IF_RX_BUF_SIZE

struct cdc_if_endpoint_RX
{
    uint8_t buf[USB_IF_RX_BUF_SIZE];  /* rx ring buffer                       */
    uint8_t *outptr;                  /* tail of ring buffer                  */
    uint8_t *inptr;                   /* head of ring buffer                  */
    uint8_t num_payloads;             /* # payloads loaded into periph buffer */
    struct cdc_user_if user;          /* exposed user interface               */
};

struct cdc_if_endpoint_TX
{
    uint8_t buf[USB_IF_TX_BUF_SIZE];  /* tx ring buffer                       */
    uint8_t *outptr;                  /* tail of ring buffer                  */
    uint8_t *inptr;                   /* head of ring buffer                  */
    uint8_t num_payloads;             /* # payloads loaded into periph buffer */
    struct cdc_user_if user;          /* exposed user interface               */
};

struct USB_CDC_interface
{
    struct cdc_if_endpoint_TX tx;           /* the outgoing endpoint          */
    struct cdc_if_endpoint_RX rx;           /* the incoming endpoint          */
    USBD_CDC_LineCodingTypeDef Linecoding;  /* the configured linecoding      */
    void (*initCallback)(cdcUserCbParam_t); /* init success user cb func      */
    cdcUserCbParam_t initCbParam;           /* init success user cb arg       */
};

static struct USB_CDC_interface cdc = 
{
    .tx = 
    {   
        .buf = {0},
        .outptr = NULL,
        .inptr  = NULL,
        .user = 
        {
            .delim = '\0',
            .buf = NULL,
            .bufSize = 0,
            .callback = NULL,
            .cbParam  = NULL,
        },
    },
    
    .rx = 
    {   
        .buf = {0},
        .outptr = NULL,
        .inptr  = NULL,
        .user = 
        {
            .delim = '\0',
            .buf = NULL,
            .bufSize = 0,
            .callback = NULL,
            .cbParam  = NULL,
        },
    },

    .Linecoding = 
    {
        .bitrate    = USB_CDC_DEFAULT_BAUDRATE,
        .format     = USB_CDC_DEFAULT_STOPBITS,
        .paritytype = USB_CDC_DEFAULT_PARITY,
        .datatype   = USB_CDC_DEFAULT_DATABITS,
    },

    .initCallback = NULL,
    .initCbParam  = NULL,
};


/* THESE ARE CALLED BY THE PERIPHERAL VIA ISR SEQUENCE */
static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);
USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
    CDC_Init_FS,
    CDC_DeInit_FS,
    CDC_Control_FS,
    CDC_Receive_FS
};

/* STRUCT ALIAS ONTO THE USG OTG STRUCTURE MEMORY MAPPED PERIPHERAL */
extern USBD_HandleTypeDef hUsbDeviceFS;

/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{   
#if defined(MCU_APP)
    /* Set Application Buffers */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, cdc.tx.buf, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, cdc.rx.buf);
#else
#endif /* MCU_APP */
    return USBD_OK;
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
  * @param  cmd:  Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else
  *  USBD_FAIL
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
    case CDC_SET_LINE_CODING:
    /***************************************************************************
     * @brief The table below describes the necessary structure and
     * bit fields to enumerate the USB peripheral as a CDC class dev 
     * (class sub descriptor) once the usb OTG peripheral has enumerated
     * as a base usb device AND the CDC class request descriptor packet
     * has been sent.
     * This beautiful table was brought to you by 20 minutes of frustration
     * 
     * |------------------------------------------------------------------|
     * |              USB CDC line coding structure and format            |
     * |--------+-------------+--------------+---------+------------------|
     * | Offset |    Field    | Size (bytes) |  Value  |  Description     |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Data terminal    |
     * |   0    |  dwDTERate  |       4      | number  | rate in bits per |
     * |        |             |              |         | second           |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Num Stop bits    |
     * |   4    | bCharFormat |       1      | number  | 0: 1 stop bit    |
     * |        |             |              |         | 1: 1.5 stop bits |
     * |        |             |              |         | 2: 2 stop bits   |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Parity:          |
     * |        |             |              |         | 0: None          |
     * |   5    | bParityType |      1       | number  | 1: Odd           |
     * |        |             |              |         | 2: Even          |
     * |        |             |              |         | 3: Mark          |
     * |        |             |              |         | 3: Space         |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Num data bits    |
     * |   6    | bDataBits   |      1       | number  | Valid values are |
     * |        |             |              |         | 5, 6, 7, 8, 16   |
     * |--------+-------------+--------------+---------+------------------|
     **************************************************************************/
        cdc.Linecoding.bitrate =    (uint32_t)(pbuf[0] |
                                    (pbuf[1] << 8)     |
                                    (pbuf[2] << 16)    |
                                    (pbuf[3] << 24));
        cdc.Linecoding.format      = pbuf[4];
        cdc.Linecoding.paritytype  = pbuf[5];
        cdc.Linecoding.datatype    = pbuf[6];
        break;
    case CDC_GET_LINE_CODING:
        pbuf[0] = (uint8_t)(cdc.Linecoding.bitrate);
        pbuf[1] = (uint8_t)(cdc.Linecoding.bitrate >> 8);
        pbuf[2] = (uint8_t)(cdc.Linecoding.bitrate >> 16);
        pbuf[3] = (uint8_t)(cdc.Linecoding.bitrate >> 24);
        pbuf[4] = cdc.Linecoding.format;
        pbuf[5] = cdc.Linecoding.paritytype;
        pbuf[6] = cdc.Linecoding.datatype;
        break;
    case CDC_SET_CONTROL_LINE_STATE:
        cdc.initCallback(cdc.initCbParam);
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
#if defined(MCU_APP)
        USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
        USBD_CDC_ReceivePacket(&hUsbDeviceFS);

        uint32_t i = 0;
        do
        {   
            *cdc.rx.inptr++ = Buf[i];
            if (Buf[i] == cdc.rx.user.delim)    /* Check for terminator */
            {   
                /* nul-terminate so caller can use string.h */
                Buf[i] = '\0'; 
                cdc.rx.user.callback(cdc.rx.user.cbParam);
            }

            if(cdc.rx.inptr > cdc.rx.user.buf + cdc.rx.user.bufSize)
            {
                cdc.rx.inptr = cdc.rx.user.buf;
            }
        } while (++i < *Len);
#endif /* MCU_APP */
    return USBD_OK;
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


int CDC_transmit_payload(void)
{   
    int status = 0;
    int bytesToWrap = (cdc.tx.buf + sizeof(cdc.tx.buf)) - cdc.tx.outptr;
    if(cdc.tx.num_payloads > 0)
    {   
        /* If the latest set payload didn't wraparound */
        if(cdc.tx.user.bufSize < bytesToWrap)
        {
            USBD_CDC_SetTxBuffer(&hUsbDeviceFS, 
                                cdc.tx.outptr, 
                                cdc.tx.user.bufSize);
        }
        else /* The last loaded payload wrapped the FIFO */
        {
            /******************************************************************
             * TODO: find a way to transmit the packet without realigning the
             * FIFO buffer or using a temporary container for the wrapped bytes.
             *
             * THERE HAS TO BE A BETTER WAY THAN THIS BUT I KNOW THIS SOLVES
             * THE CASE WHEREIN THE LAST USER BUFFER LOADED INTO FIFO RING 
             * RESULTED IN THE USB PERIPH TX FIFO IN_PTR WRAPPING
             ******************************************************************/

            /* This is the most disgusting, hacky, fix I've ever done */
            /* Slide (ie: realign) the fifo to have out ptr at index 0 */

            uint8_t temp[sizeof(cdc.tx.buf)]; /* temporary duplicate of FIFO */
            memcpy(temp, cdc.tx.outptr, bytesToWrap);
            memcpy(&temp[bytesToWrap] + 1, cdc.tx.buf, cdc.tx.user.bufSize - bytesToWrap);
            memcpy(cdc.tx.buf, temp, sizeof(cdc.tx.buf));

            /* update position of inptr */
            if(cdc.tx.inptr + bytesToWrap > cdc.tx.buf + sizeof(cdc.tx.buf))
            {   
                /* In this case: inptr > outptr. so of course it wraps too */
                cdc.tx.inptr = cdc.tx.buf + (cdc.tx.inptr - cdc.tx.outptr);
            }
            else
            {   
                /* inptr < outptr so it doesn't wrap */
                cdc.tx.inptr += bytesToWrap;
            }

            /* Do this after moving inptr so we dont have to store old outptr */
            cdc.tx.outptr = cdc.tx.buf; 

            USBD_CDC_SetTxBuffer(&hUsbDeviceFS, temp, cdc.tx.user.bufSize);
        }
        status = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
    }
    else
    {
        status = 1;
    }
    return status;
}




int CDC_set_payload(void)
{   
    int status = 0;
    int i;
    for(i = 0; i < cdc.tx.user.bufSize; i++)
    {
        *cdc.tx.inptr = cdc.tx.user.buf[i];
        if(cdc.tx.inptr == cdc.tx.outptr)
        {   
            cdc.tx.num_payloads--;
            status = 1;
        }
        else if(cdc.tx.inptr == cdc.tx.buf + sizeof(cdc.tx.buf))
        {
            cdc.tx.inptr = cdc.tx.buf; /* wraparound condition */
        }
        cdc.tx.inptr += 1;
    }
    cdc.tx.num_payloads += 1; /* increment number of stored payloads */
    return status;
}


unsigned int CDC_peek_num_payloads_out(void)
{
    return cdc.tx.num_payloads;
}


void CDC_setUserRxEndPt(const struct cdc_user_if *user)
{
    cdc.rx.user.buf      = user->buf;
    cdc.rx.user.bufSize  = user->bufSize;
    cdc.rx.user.delim    = user->delim;
    cdc.rx.user.callback = user->callback;
    cdc.rx.user.cbParam = user->cbParam;
}

void CDC_setUserTxEndPt(const struct cdc_user_if *user)
{
    cdc.tx.user.buf      = user->buf;
    cdc.tx.user.bufSize  = user->bufSize;
    cdc.tx.user.delim    = user->delim;
    cdc.tx.user.callback = user->callback;
    cdc.tx.user.cbParam = user->cbParam;
}

void CDC_setUserInitCb(void (*initCbFunc)(void*), void* param)
{
    cdc.initCallback = initCbFunc;
    cdc.initCbParam  = param;
}