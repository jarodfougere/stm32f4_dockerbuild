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

/**
 * @brief This copies the contents of latest received USB Command 
 * String into Buf. Provided that buflen is large enough.
 * 
 * @param buf    the buffer to receive the command string
 * @param buflen the size of the buffer (CALLER PROVIDED)
 * @return int USBD_OK (0) on success, USBD_FAIL or USBD_BUSY on failure.
 */
char* comms_get_command_string(void);


/**
 * @brief Transmits the invalid json error message from the usb 
 * peripheral
 */
void error_jsonformat(void);



#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* COMMS_MIDDLEWARE_INTERFACE */