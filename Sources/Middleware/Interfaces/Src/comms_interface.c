#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "comms_interface.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#define MAX_COMMS_IF_DATA_PAYLOAD_SIZE 1024

void comms_init(void)
{
    MX_USB_DEVICE_Init();
    USBD_Interface_fops_FS.Init();
}


int comms_printf(enum comms_if_type interface, const char* format, ...)
{   
    int status = 0;
    va_list args;
    va_start(args, format);
    char tx_buf[MAX_COMMS_IF_DATA_PAYLOAD_SIZE];


    /* check if we were able to fully load the payload into the buffer */
    const int payload_size = vsnprintf(tx_buf, sizeof(tx_buf), format, args);
    if(payload_size < sizeof(tx_buf)) /* check if payload fit in buffer */
    {
        switch(interface)
        {
            case COMMS_usb:
                status = CDC_Transmit_FS((uint8_t*)tx_buf, payload_size);
                break;
            case COMMS_spi:

                break;
            case COMMS_iic:

                break;
            case COMMS_uart:

                break;
            default:
                /* do nothing */
                break;
        }
    }
    else
    {
        status = -1;
    }
    va_end(args);
    return status;
}


char* comms_getbuf(enum comms_if_type interface)
{   
    int8_t status = 0;
    uint32_t rx_len = 0;
    static char rxbuf[MAX_COMMS_IF_DATA_PAYLOAD_SIZE];
    switch(interface)
    {
        case COMMS_usb:
            status = USBD_Interface_fops_FS.Receive((uint8_t*)rxbuf, &rx_len);
            break;
        case COMMS_spi:

            break;
        case COMMS_iic:

            break;
        case COMMS_uart:

            break;
        default:
            /* do nothing */
            break;
    }
    return (status == 0) ? &rxbuf[0] : NULL;
}

