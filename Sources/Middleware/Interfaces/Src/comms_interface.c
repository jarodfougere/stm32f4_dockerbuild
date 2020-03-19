/**
 * @file comms_interface.c
 * @author Carl Mattatall
 * @brief  This module (in combination with its header file of the same name)
 *         provides a communication interface abstraction to the task layer.
 *         
 *         The interface bundles the USB periph, buffers, line coding, clocking,
 *         interupts, and line control state into an abstraction that can be
 *         exposed to the task / application layer without exposing the actual
 *         implementation details of the low layer drivers themselves.
 * @version 0.1
 * @date 2020-03-19
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "comms_interface.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

/* This interface hides the actual buffers from the task layer */
static uint8_t inBuf[COMMS_IF_USER_RX_BUF_SIZE];
static uint8_t outBuf[COMMS_IF_USER_TX_BUF_SIZE];


char* comms_get_command_string(void)
{
    return (char*)inBuf;
}


int comms_tx(char* buf, unsigned int len)
{   
    /* 
     * Mostly using this for debugging. 
     * Wrapped it in Comms interface so task layer doesnt know about drivers 
     */
    return (int)CDC_Transmit_FS((uint8_t*)buf, (uint16_t)len);
}


void comms_init(struct cdc_user_if *rx, struct cdc_user_if *tx)
{   
    rx->buf = inBuf;
    rx->bufSize = sizeof(inBuf);
    tx->buf = outBuf;
    tx->bufSize = sizeof(outBuf);
    CDC_setUserRxEndPt(rx);
    CDC_setUserTxEndPt(rx);
    MX_USB_DEVICE_Init();
}


void comms_setInitCb(void (*callback)(void*), void *param)
{   
    /* For now, the interface implementation is just wrapping my CDC module
     * user ISR injection function.
     * 
     * At least this way, we keep the modules decoupled.
     * in case the chipset changes, drivers change, or the application becomes
     * hosted.
     */
    CDC_setUserInitCb(callback, param);
}


int comms_set_payload(const char* format, ...)
{
    int status = 0;
    va_list args;
    va_start(args, format);

    /* vsnprintf returns # bytes that WOULD have been 
     * written if the provided buffer was large enough.
     */
    if(vsnprintf((char*)outBuf, sizeof(outBuf), format, args) 
        < sizeof(outBuf))
    {   
        /* Load the set buffer into peripheral FIFO */
        CDC_set_payload();
    }
    else
    {
        /* The buffer is not sufficiently large to fit the payload 
         *
         * If this keeps happening, consider increasing 
         * COMMS_IF_USER_TX_BUF_SIZE
         */
        status = 1;
    }
    va_end(args);
    return status;
}


int comms_send_payload(unsigned int num_payloads, unsigned int delay_ms)
{   
    int status = 0;
    int i;
    if(num_payloads > CDC_peek_num_payloads_out())
    {
        status = 1;
    }
    else
    {
        for(i = 0; i < num_payloads; i++)
        {

        }
    }
    return status;
}
