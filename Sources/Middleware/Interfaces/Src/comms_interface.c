#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "comms_interface.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

static char comms_json_buf[USB_USER_COMMAND_STRING_BUF_SIZE];

void comms_init(void)
{
    MX_USB_DEVICE_Init();
}

void error_jsonformat(void)
{
    CDC_sendJSON("error", "json format");
}

char* comms_get_command_string(void)
{   
    /* call driver layer commandstring retreival */
    return (0 == CDC_GetCommandString((uint8_t*)comms_json_buf, (uint16_t)sizeof(comms_json_buf))) ? comms_json_buf : NULL;
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