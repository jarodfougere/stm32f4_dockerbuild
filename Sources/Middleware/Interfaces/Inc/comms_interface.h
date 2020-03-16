#ifndef RIMOT_COMMS_MIDDLEWARE_INTERFACE
#define RIMOT_COMMS_MIDDLEWARE_INTERFACE
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */

enum comms_if_type 
{
    COMMS_usb,
    COMMS_spi,
    COMMS_iic,
    COMMS_uart,
};


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
int comms_printf(enum comms_if_type interface, const char* format, ...);


/**
 * @brief This returns a pointer to the rx buffer of a given interface if the 
 * interface has data to receive.
 * 
 * @param interface the specified interface.
 * @return char* base address of the received character byte array.
 */
char* comms_getbuf(enum comms_if_type interface);

#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* COMMS_MIDDLEWARE_INTERFACE */