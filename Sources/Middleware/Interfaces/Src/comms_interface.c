#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "comms_interface.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

/* This interface hides the actual buffers from the task layer */
static char inBuf[COMMS_IF_USER_RX_BUF_SIZE];
static char outBuf[COMMS_IF_USER_TX_BUF_SIZE];


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
    CDC_setUserInitCb(callback, param);
}

int comms_set_payload(const char* format, ...)
{
    int status = 0;
    va_list args;
    va_start(args, format);
    if(vsnprintf(outBuf, sizeof(outBuf), format, args) < sizeof(outBuf))
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


#if 0
int usb_printf(const char* format, ...)
{   
    int status = 0;
    va_list args;
    va_start(args, format);
    const int maxlen = sizeof(outBuf); /* max size that can fit in buffer */
    if(vsnprintf(outBuf, maxlen, format, args) < maxlen)
    {
        
    }

    {
        status = CDC_Transmit_FS((uint8_t*)tx_buf, payload_size);
    }
    else
    {
        status = -1;
    }
    va_end(args);
    return status;
}
#endif

