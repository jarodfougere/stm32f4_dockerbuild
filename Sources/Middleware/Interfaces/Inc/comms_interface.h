#ifndef RIMOT_COMMS_MIDDLEWARE_INTERFACE
#define RIMOT_COMMS_MIDDLEWARE_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */


/**
 * @brief Initializes various drivers used by the comms interface
 */
void comms_init(void);


/**
 * @brief This transmits a character byte array to the specified peripheral
 * interface using printf-style format specifiers.
 * 
 * @param interface the interface to transmit
 * @param format format specifiers
 * @param ... args list outlining format specifiers
 * @return int 0 on success, !0 on error.
 */
int usb_printf(const char* format, ...);

void assign_comms_usb_rx_cb(void (*cb_func)(void));

int comms_get_command_string(uint8_t *buf, uint16_t buflen);


#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* COMMS_MIDDLEWARE_INTERFACE */