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
#include <string.h>

#include "comms_interface.h"
#include "middleware_core.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#define MAX_COMMS_TRANSMIT_ATTEMPTS 5
#define COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS 3

/* This interface hides the actual buffers from the task layer */
static uint8_t inBuf[COMMS_IF_USER_RX_BUF_SIZE];
static uint8_t outBuf[COMMS_IF_USER_TX_BUF_SIZE];


char* comms_get_command_string(void)
{   
    if(USBD_OK == CDC_getCommandString())
    {
        return (char*)inBuf;
    }
    else
    {
        return NULL;
    }
}


int comms_tx(char* buf, unsigned int len)
{   
    int tx_tries;
    for(tx_tries = 0; tx_tries < MAX_COMMS_TRANSMIT_ATTEMPTS; tx_tries++)
    {   
        switch(CDC_Transmit_FS((uint8_t*)buf, (uint16_t)len))
        {
            case USBD_OK:   
            {
                return 0;
            }
            break;
            case USBD_FAIL: 
            {
                return 1;
            }
            break;
            case USBD_BUSY:
            {
                delay_ms(COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS);
            }
            break;  /* try again */
            default:
#if !defined(NDEBUG)
            {
                while(1)
                {
                    /* programmer catches omission error in debug build */
                }
            }
#else
            break;
#endif /* DEBUG BUILD */
        }
    }

    /* failure because 5 attempts were done and still no transmit success */
    return 1; 
}


void comms_init(struct cdc_user_if *rx, struct cdc_user_if *tx)
{   
    rx->buf     = inBuf;
    rx->bufSize = sizeof(inBuf);
    tx->buf     = outBuf;
    tx->bufSize = sizeof(outBuf);
    CDC_setUserRxEndPt(rx);
    CDC_setUserTxEndPt(rx);
    MX_USB_DEVICE_Init();
}


int comms_set_payload(const char* format, ...)
{
    int status = 0;
    va_list args;
    va_start(args, format);
    int Len;
    int UserBytesLoaded;
    const char delimStrCheck[] = {COMMS_USB_STRING_DELIM, '\0'};

    /* load buffer with printf formatting of payload */
    Len = vsnprintf((char*)outBuf, sizeof(outBuf), format, args);
    Len++; /* extra byte for nul character */
    UserBytesLoaded = Len;
    
    /* Tack on payload delimiter */
    strcat((char*)outBuf, delimStrCheck);

    /* Load the payload into CDC TX endpoint */
    if(USBD_OK == CDC_set_payload(&Len))
    {
        /* Wipe the user payload buffer if it's loaded correctly */
        memset(outBuf, 0, sizeof(outBuf));
    }
    else
    {   
        if(UserBytesLoaded != Len)
        {
            /* 
             * Payload would fit in user buffer but 
             * there are too many payloads in USB OUT
             * endpoint already to queue the transmit.
            */
            status = 2;

            /*
             * TODO:
             * 
             * IF OUTPOST STATE IS ACTIVE, WE CAN TRANSMIT A PAYLOAD
             * AND TRY TO LOAD THE DESIRED PAYLOAD NOW THAT THERE
             * IS MORE ROOM IN THE CDC INTERFACE OUT ENDPOINT.
             * 
             * BUT IF OUTPOST IS ASLEEP, THERES NOTHING WE CAN DO OTHER
             * THAN INCREASING THE SIZE OF THE CDC INTERFACE PAYLOAD BUFFER.
             */
        }
        else
        {   
            /* Couldn't load the payload into CDC TX OUT buffer (wont' fit) */
            status = 1;
        }
    }
    va_end(args);
    return status;
}


int comms_send_payload(unsigned int num_payloads, unsigned int delay_ms)
{   
    int i;
    int tx_successes = 0;
    unsigned int actual_delay = delay_ms;
    if(actual_delay < COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS)
    {
        actual_delay = COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS;
    }
    if(num_payloads > CDC_peek_num_payloads_out())
    {
        tx_successes = 0;
    }
    else
    {
        for(i = 0; i < num_payloads; i++)
        {
            if(USBD_OK == CDC_transmit_payload())
            {
                tx_successes++;
            }
        }
        
        if(tx_successes != num_payloads)
        {
            tx_successes = 0;
        }
    }

    return tx_successes;
}
