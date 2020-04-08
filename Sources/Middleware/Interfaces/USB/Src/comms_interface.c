/**
 * @file comms_interface.c
 * @author Carl Mattatall
 * @brief  This module (in combination with its header file of the same name)
 *         provides a communication interface abstraction to the task layer.
 *         
 *         The interface bundles the USB periph, buffers, line coding, clocking,
 *         interupts, and line control state into an abstraction that can be
 *         exposed to the task / application layer without exposing the actual
 *         implementation details of the low level drivers themselves.
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

#define MAX_TX_TRIES 5
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
    for(tx_tries = 0; tx_tries < MAX_TX_TRIES; tx_tries++)
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
#if defined(MCU_APP)
    rx->buf     = inBuf;
    rx->bufSize = sizeof(inBuf);
    tx->buf     = outBuf;
    tx->bufSize = sizeof(outBuf);
    CDC_setUserRxEndPt(rx);
    CDC_setUserTxEndPt(tx);
#if defined(USE_HAL_DRIVER)
    MX_USB_DEVICE_Init();
#else
#error NO ALTERNATIVE TO MX_USB_DEVICE_INIT in comms_interface.c
#endif /* STM32 HAL OR BARE METAL */
#else
    comms_printf("executed comms_init%c",'\n');
#endif /* MCU_APP */
}


int comms_set_payload(const char* format, ...)
{
    int status = 0;
    va_list args;
    va_start(args, format);
    int Len;
    int UserBytesLoaded;
    const char delimStrCheck[] = {RIMOT_USB_STRING_DELIM, '\0'};

    /* load buffer with printf formatting of payload */
    Len = vsnprintf((char*)outBuf, sizeof(outBuf), format, args);
    
    /* Tack on payload delimiter */
    strcat((char*)outBuf, delimStrCheck);
    Len += sizeof(delimStrCheck);

    UserBytesLoaded = Len;


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


int comms_send_payloads(unsigned int num_payloads, unsigned int ms)
{   
    /*
     * TODO: THIS CAN BE MADE MUCH BETTER.
     * 
     * CURRENTLY WHEN CALLER TRIES TO TRANSMIT MORE PAYLOADS 
     * THAN ARE LOADED INTO THE BUFFER, WE RETURN 0 TO INDICATE 
     * NONE HAVE BEEN TRANSMITTED.
     * 
     * REALLY, WE NEED A SEPARATE STATUS WHICH FUNCTIONS LIKE A 
     * "WARNING", INDICATING TO THE CALLER THAT ALL THEIR PAYLOADS
     * WERE TRANSMITTED BUT THAT THEY TRIED TO TRANSMIT A PAYLOAD
     * THAT EITHER WAS NOT QUEUED SUCCESSFULLY OR THAT THEY LOST 
     * TRACK OF THE NUMBER OF PAYLOADS THEY HAD STORED.
     */
    int tx_successes = 0;
    unsigned int i;
    unsigned int payloads_to_tx;
    unsigned int actual_delay;

    /* delay check */
    if(ms < COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS)
    {
        actual_delay = COMMS_TRANSMIT_ATTEMPT_INTERVAL_MS;
    }
    else
    {
        actual_delay = ms;
    }

    /* payload count check */
    if(num_payloads > CDC_peek_num_payloads_out())
    {   
        /*  
         * If caller wants to transmit more payloads than they have queued, 
         * only transmit what is available. 
         * 
         * TODO: should indicate to caller than this scenario has occurred.
         */
        payloads_to_tx = CDC_peek_num_payloads_out();
    }
    else
    {
        payloads_to_tx = num_payloads;
    }

    /* transmit payloads */
    for(i = 0; i < payloads_to_tx; i++)
    {
        USBD_StatusTypeDef status = USBD_OK;
        
        /* payload attempt loop */
        int tries = 0;
        for(;(tries < MAX_TX_TRIES) && (status != USBD_FAIL); tries++)
        {   

            /* eventaully I'll fix the return type so compiler stops complaining on -Wextra :( */
            status = (USBD_StatusTypeDef)CDC_transmit_payload(); 
            if(USBD_OK == status)
            {   
                tx_successes++;
                break;
            }
            else
            {
                delay_ms(actual_delay);
            }
        }

        if(USBD_FAIL == status)
        {   
            /* 
                * CDC_Transmit_payload only returns USBD_FAIL
                * when caller violates it's API contract
                */
            #if !defined(NDEBUG)
                while(1)
                {
                    /* programmer to catch error */
                }
            #else
                /* do nothing */
            #endif /* DEBUG BUILD */
        }
    }
    return tx_successes;
}
