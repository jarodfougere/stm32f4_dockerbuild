#ifndef RIMOT_COMMS_MIDDLEWARE_INTERFACE
#define RIMOT_COMMS_MIDDLEWARE_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>

#include "cdc_user_if.h"

#define COMMS_IF_USER_RX_BUF_SIZE 128
#define COMMS_IF_USER_TX_BUF_SIZE 512


/**
 * @brief Initializes various drivers used by the comms interface
 */
void comms_init(struct cdc_user_if *rx, struct cdc_user_if *tx);


/**
 * @brief Assign a callback function to comms_init
 * 
 * @param callback The callback function  : void (*funcPtr)(void*)
 * @param param    The callback parameter : void *param
 */
void comms_setInitCb(void (*callback)(void*), void *param);


/**
 * @brief Load a payload to the transmit buffer using printf-style
 * formatting
 * 
 * @param format printf-style format string
 * @param ...    printf-style format specifiers 
 * @return int : 0 on success, !0 on error
 */
int comms_set_payload(const char* format, ...);


/**
 * @brief Transmit num_payloads from the USB CDC Transmit endpoint,
 * with a delay_ms milliseconds interval between each payload 
 * 
 * @param num_payloads the number of payloads to transmit
 * @param delay_ms     the millisecond delay between payloads
 * @return int : The number of successfully transmitted payloads.
 */
int comms_send_payload(unsigned int num_payloads, unsigned int delay_ms);


/* This is a macro to send an outgoing string using printf format-specifiers */
#if defined(MCU_APP)
#define usb_printf(format, ...) {                   \
    comms_payload_out(format, __VA_ARGS__);         \
    comms_send_payload(1, 0);                       \
}
#else
#define usb_printf printf(format __VA_ARGS__)
#endif


/**
 * @brief This copies the contents of latest received USB Command 
 * String into Buf. Provided that buflen is large enough.
 * 
 * @param buf    the buffer to receive the command string
 * @param buflen the size of the buffer (CALLER PROVIDED)
 * @return int USBD_OK (0) on success, USBD_FAIL or USBD_BUSY on failure.
 */
char* comms_get_command_string(void);









#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* COMMS_MIDDLEWARE_INTERFACE */