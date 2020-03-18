#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "comms_interface.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

void comms_init(void)
{
    MX_USB_DEVICE_Init();
    USBD_Interface_fops_FS.Init();
}

int comms_get_command_string(uint8_t *buf, uint16_t buflen)
{   
    /* call driver layer commandstring retreival */
    return CDC_GetCommandString(buf, buflen);
}

void assign_comms_usb_rx_cb(void (*cb_func)(void))
{   
    /* pass the callback func provided by task layer down to drivers */
    assign_usb_rx_callback(cb_func);
}


int usb_printf(const char* format, ...)
{   
    int status = 0;
    va_list args;
    va_start(args, format);
    char tx_buf[2048];
    memset(tx_buf, 0, sizeof(tx_buf));

    /* check if we were able to fully load the payload into the buffer */
    const int payload_size = vsnprintf(tx_buf, sizeof(tx_buf), format, args);
    if(payload_size < sizeof(tx_buf)) /* check if payload fit in buffer */
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