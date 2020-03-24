#ifndef RIMOT_COMMS_MIDDLEWARE_INTERFACE
#define RIMOT_COMMS_MIDDLEWARE_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>

#include "cdc_user_if.h"

#define COMMS_IF_USER_RX_BUF_SIZE 256
#define COMMS_IF_USER_TX_BUF_SIZE 512
#define COMMS_USB_STRING_DELIM '\r'

/**
 * @brief Initializes various drivers used by the comms interface
 */
void comms_init(struct cdc_user_if *rx, struct cdc_user_if *tx);

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
 * @return int :       The number of successfully transmitted payloads.
 */
int comms_send_payload(unsigned int num_payloads, unsigned int ms);


/**
 * @brief  get the base pointer of the user usb CDC endpoint RX buffer. 
 * @return char* byte address of the base of the user RX buffer.
 */
char* comms_get_command_string(void);


/**
 * @brief Transmit a byte array of known size over USB using the comms interface
 * @param buf The byte array
 * @param len The size of the byte array
 * @return int : 0 on success, != on error
 */
int comms_tx(char* buf, unsigned int len);


/* This is a macro to transmit a string literal */
#define comms_printstr(str) comms_tx(str, sizeof(str))


/* This is a macro to send an outgoing string using printf format-specifiers */
#if defined(MCU_APP)
#define comms_printf(format, ...) {                 \
    comms_set_payload(format, __VA_ARGS__);         \
    comms_send_payload(1, 0);                       \
}
#else
#define comms_printf printf(format __VA_ARGS__)
#endif
#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* COMMS_MIDDLEWARE_INTERFACE */