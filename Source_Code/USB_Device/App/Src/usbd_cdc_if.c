
#include <stdio.h> /* vsnprintf and snprintf */
#include <stdint.h>
#include <limits.h>
#include <string.h> /* memset */

#include "cmsis_os.h"
#include "queue.h"
#include "task.h"
#include "main.h"
#include "task_defs.h"
#include "usbd_cdc_if.h"
#include "cmsis_compiler.h"


#define APP_RX_USER_CMD_DATA_SIZE 128

uint8_t  UserRxBufferFS[APP_RX_DATA_SIZE];
uint8_t  UserTxBufferFS[APP_TX_DATA_SIZE];
uint8_t  UserRxCmdBuf[APP_RX_USER_CMD_DATA_SIZE];
uint8_t *UserRxInPtr;  /**< Data insertion USB Rx buffer pointer     */
uint8_t *UserRxOutPtr; /**< Data removal USB RX buffer pointer       */

USBD_CDC_LineCodingTypeDef linecoding = {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* nb. of bits 8*/
};

extern USBD_HandleTypeDef hUsbDeviceFS;

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);
static int8_t CDC_TransmitCplt_FS(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);


/* clang-format off */
USBD_CDC_ItfTypeDef USBD_Interface_fops_FS = 
{
    CDC_Init_FS, 
    CDC_DeInit_FS,
    CDC_Control_FS, 
    CDC_Receive_FS,
    CDC_TransmitCplt_FS,
};
/* clang-format on */

/**
 * @brief  Initializes the CDC media low layer over the FS USB IP
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Init_FS(void)
{
    /* Set Application Buffers */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);

    memset(UserRxCmdBuf, 0, sizeof(UserRxCmdBuf));
    memset(UserTxBufferFS, 0, sizeof(UserTxBufferFS));
    UserRxInPtr  = UserRxCmdBuf;
    UserRxOutPtr = UserRxCmdBuf;

    return (USBD_OK);
}

/**
 * @brief  DeInitializes the CDC media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_DeInit_FS(void)
{
    return (USBD_OK);
}

/**
 * @brief  Manage the CDC class requests
 * @param  cmd: Command code
 * @param  pbuf: Buffer containing command data (request parameters)
 * @param  length: Number of data to be sent (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 * USBD_FAIL
 */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
    USBSERIALMSGQ_t usmsg                = {0};
    BaseType_t      xHigherPrioTaskWoken = pdFALSE;
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

            linecoding.bitrate    = (uint32_t)(pbuf[0] | (pbuf[1] << 8) |
                                            (pbuf[2] << 16) | (pbuf[3] << 24));
            linecoding.format     = pbuf[4];
            linecoding.paritytype = pbuf[5];
            linecoding.datatype   = pbuf[6];
            break;
        case CDC_GET_LINE_CODING:
            pbuf[0] = (uint8_t)(linecoding.bitrate);
            pbuf[1] = (uint8_t)(linecoding.bitrate >> 8);
            pbuf[2] = (uint8_t)(linecoding.bitrate >> 16);
            pbuf[3] = (uint8_t)(linecoding.bitrate >> 24);
            pbuf[4] = linecoding.format;
            pbuf[5] = linecoding.paritytype;
            pbuf[6] = linecoding.datatype;
            break;
        case CDC_SET_CONTROL_LINE_STATE:
            memset(&usmsg, MSG_CONTENT_NONE, sizeof(usmsg));
            usmsg.msg.ctx  = TASK_USBSERIAL_CONTEXT_general;
            usmsg.msg.evt  = TASK_USBSERIAL_GENERAL_EVENT_com_open;
            usmsg.callback = NULL;
            xQueueSendToBackFromISR(usbSerialMsgQHandle, (void *)&(usmsg),
                                    &xHigherPrioTaskWoken);
            portYIELD_FROM_ISR(xHigherPrioTaskWoken);
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
 *         This function will issue a NAK packet on any OUT packet received on
 *         USB endpoint until exiting this function. If you exit this function
 *         before transfer is complete on CDC interface (ie. using DMA
 * controller) it will result in receiving more data while previous ones are
 * still not sent.
 *
 * @param  Buf: Buffer of data to be received (HARDWARE FIFO)
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 * USBD_FAIL
 *
 * @note CALLED FROM ISR
 */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{
    USBSERIALMSGQ_t usmsg;
    BaseType_t      xHigherPriorityTaskWoken = pdFALSE;
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
    USBD_CDC_ReceivePacket(&hUsbDeviceFS);

    /* copy bytes into receive buffer and test for command terminator */
    uint32_t i = 0;
    do
    {
        /* copy byte into command buffer */
        *(UserRxInPtr++) = Buf[i];

        if (Buf[i] == (uint8_t)USB_DELIMIT_CHAR)
        {
            /* notify command handler */
            memset(&usmsg, MSG_CONTENT_NONE, sizeof(usmsg));
            usmsg.msg.ctx  = TASK_USBSERIAL_CONTEXT_receive;
            usmsg.msg.evt  = TASK_USBSERIAL_RECIEVE_EVENT_message_received;
            usmsg.callback = NULL;
            xQueueSendToBackFromISR(usbSerialMsgQHandle, (void *)&usmsg,
                                    &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }

        /* wrap around user buffer  */
        if (UserRxInPtr >= UserRxCmdBuf + sizeof(UserRxCmdBuf))
        {
            UserRxInPtr = UserRxCmdBuf;
        }

    } while (++i < *Len);
    return (USBD_OK);
}


/**
 * @brief  CDC_Transmit_FS
 *         Data to send over USB IN endpoint are sent over CDC interface
 *         through this function.
 *         @note
 *
 *
 * @param  Buf: Buffer of data to be sent
 * @param  Len: Number of data to be sent (in bytes)
 * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
 */
uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len)
{
    uint8_t                 result = USBD_OK;
    USBD_CDC_HandleTypeDef *hcdc =
        (USBD_CDC_HandleTypeDef *)hUsbDeviceFS.pClassData;
    if (hcdc->TxState != 0)
    {
        return USBD_BUSY;
    }
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
    result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
    return result;
}


/**
 * @brief  CDC_getCommandString
 *         Copies command string into provided buffer.
 *         @note
 *
 *
 * @param  Buf: Buffer to store command string
 * @param  Len: Buffer length
 * @return 0
 */
uint8_t CDC_getCommandString(uint8_t *Buf, uint16_t Len)
{
    uint_fast16_t i      = 0;
    uint_least8_t status = 1;
    if (Len < 1) /* check for API error */
    {
        status = 1;
    }
    else
    {
        do
        {
            Buf[i] = *UserRxOutPtr++;
            if (Buf[i] == USB_DELIMIT_CHAR)
            {
                Buf[i] = '\0';
                status = 0;
            }

            if (UserRxOutPtr >= UserRxCmdBuf + sizeof(UserRxCmdBuf))
            {
                UserRxOutPtr = UserRxCmdBuf;
            }
        } while (++i < Len && (status == 1));
    }
    return status;
}


/**
 * @brief  CDC_TransmitCplt_FS
 *         Data transmited callback
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 * USBD_FAIL
 * @note CALLED FROM ISR
 */
static int8_t CDC_TransmitCplt_FS(uint8_t *Buf, uint32_t *Len, uint8_t epnum)
{
    uint8_t result = USBD_OK;
    UNUSED(Buf);
    UNUSED(Len);
    UNUSED(epnum);
    return result;
}