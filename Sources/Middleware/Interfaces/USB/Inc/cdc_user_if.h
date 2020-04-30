#ifndef RIMOT_USB_CDC_USER_INTERFACE
#define RIMOT_USB_CDC_USER_INTERFACE
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage */

    typedef void *cdcUserCbParam_t;

    struct cdc_user_if
    {
        uint8_t delim;                      /* user assigned delimiter */
        uint8_t *buf;                       /* user assigned buffer    */
        uint32_t bufSize;                   /* size of the user buffer */
        void (*callback)(cdcUserCbParam_t); /* user assigned callback  */
        cdcUserCbParam_t cbParam;           /* user assigned cb arg    */
    };

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_USB_CDC_USER_INTERFACE*/
