#ifndef RIMOT_MCU_USB_OTG_CONFIG
#define RIMOT_MCU_USB_OTG_CONFIG
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage*/
#if defined(MCU_APP)

#include <stdlib.h> /* Size_t */
#include <stdint.h>

#if !defined(USE_HAL_DRIVER)

#include "rimot_register_field_sizes.h"

#define USB_OTG_FS_TOTAL_FIFO_SIZE 1280U   /* Size in Bytes */
#define USB_OTG_FS_HOST_MAX_CHANNEL_NBR 8U /* include HC0 */
#define __USB_OTG_FS_MAX_DEVICE_ENDPTS 4U  /* Including EP0 */
#define __USB_OTG_FS_MAX_IN_ENDPOINTS __USB_OTG_FS_MAX_DEVICE_ENDPTS
#define __USB_OTG_FS_MAX_OUT_ENDPOINTS __USB_OTG_FS_MAX_DEVICE_ENDPTS
#define __EP_ADDR_MSK 0xfU
#define USB_OTG_CORE_ID_300A 0x4F54300AU
#define USB_OTG_CORE_ID_310A 0x4F54310AU
#define __USB_OTG_FIFO_SIZE 4000U /* 4 kB */

    typedef enum
    {
        USB_OTG_MODE_device = 0x00u,
        USB_OTG_MODE_host = 0x01u,
        USB_OTG_MODE_drd = 0x02U
    } USB_OTG_MODE_t;

    typedef enum
    {
        USB_OTG_SPEED_high = 0x00u,
        USB_OTG_SPEED_high_in_full = 0x01u,
        USB_OTG_SPEED_full = 0x03u,
    } USB_OTG_SPEED_t;

    typedef enum
    {
        USB_HOST_DRIVER_SPEED_hs = 0x00u,
        USB_HOST_DRIVER_SPEED_fs = 0x01u,
    } USB_HOST_DRIVER_SPEED_t;

    typedef enum
    {
        USB_EPTYPE_ctl = 0x00u,
        USB_EPTYPE_isoc = 0x01u,
        USB_EPTYPE_bulk = 0x02u,
        USB_EPTYPE_intr = 0x03u,
    } USB_EPTYPE_t;

/* slightly annoying but compiler will yell if two enums have same value */
#define USB_EPTYPE_msk (USB_EPTYPE_t) USB_EPTYPE_intr

    typedef enum
    {
        USBD_DCFG_FRAME_INTERVAL_80 = 0x00u,
        USBD_DCFG_FRAME_INTERVAL_85 = 0x01u,
        USBD_DCFG_FRAME_INTERVAL_90 = 0x02u,
        USBD_DCFG_FRAME_INTERVAL_95 = 0x03u,
    } USBD_DCFG_FRAME_INTERVAL_t;

    typedef enum
    {
        USBD_DSTS_ENUMSPD_PHYBITS_highSpeed_30_60 = 0x00u,
        USBD_DSTS_ENUMSPD_PHYBITS_fullSpeed_30_60 = 0x01u,
        USBD_DSTS_ENUMSPD_PHYBITS_lowSpeed_6 = 0x02u,
        USBD_DSTS_ENUMSPD_PHYBITS_fullSpeed_48 = 0x03u,
    } USBD_DSTS_ENUMSPD_PHYBITS_t;

    typedef enum
    {
        USBD_DEVSPEED_TYPE_hs = 0x00u,
        USBD_DEVSPEED_TYPE_hsInFs = 0x01u,
        USBD_DEVSPEED_TYPE_fs = 0x02u,
        USBD_DEVSPEED_TYPE_ls = 0x03u,
    } USBD_DEVSPEED_TYPE_t;

    typedef enum
    {
        USBH_HCFG_FREQ_30_60MHZ = 0x00u,
        USBH_HCFG_FREQ_48MHZ = 0x01u,
        USBH_HCFG_FREQ_6MHZ = 0x02u,
    } USBH_HCFG_FREQ_t;

    typedef enum
    {
        USBH_HPRT_PRTSPD_hs = 0x00u,
        USBH_HPRT_PRTSPD_fs = 0x01u,
        USBH_HPRT_PRTSPD_ls = 0x02u,
    } USBH_HPRT_PRTSPD_t;

    typedef enum
    {
        USBD_URB_STATE__idle = 0x00u,
        USBD_URB_STATE__done = 0x01u,
        USBD_URB_STATE__notready = 0x02u,
        USBD_URB_STATE__nyet = 0x03u,
        USBD_URB_STATE__error = 0x04u,
        USBD_URB_STATE__stall = 0x05u,
    } USBD_URB_STATE__t;

    typedef enum
    {
        USBD_EP0_STATE_idle = 0x00u,
        USBD_EP0_STATE_setup = 0x01u,
        USBD_EP0_STATE_dataIn = 0x02u,
        USBD_EP0_STATE_dataOut = 0x03u,
        USBD_EP0_STATE_statusIn = 0x04u,
        USBD_EP0_STATE_statusOut = 0x05u,
        USBD_EP0_STATE_stall = 0x06u,
    } USBD_EPO_STATE_t;

    typedef enum
    {
        USBD_DEVSTATE_default = 0x01u,
        USBD_DEVSTATE_addressed = 0x02u,
        USBD_DEVSTATE_configured = 0x03u,
        USBD_DEVSTATE_suspended = 0x04u,
    } USBD_DEVSTATE_t;

    typedef enum
    {
        USBH_CHSTATE_idle = 0x00u,
        USBH_CHSTATE_xfercmplt = 0x01u,
        USBH_CHSTATE_halted = 0x02u,
        USBH_CHSTATE_nak = 0x03u,
        USBH_CHSTATE_nyet = 0x04u,
        USBH_CHSTATE_stall = 0x05u,
        USBH_CHSTATE_xacterr = 0x06u,
        USBH_CHSTATE_bblerr = 0x07u,
        USBH_CHSTATE_dataLenErr = 0x08u,
    } USBH_CHSTATE_t;

    typedef enum
    {
        USB_DRIVER_STATE_reset = 0x00u,
        USB_DRIVER_STATE_ready = 0x01u,
        USB_DRIVER_STATE_error = 0x02u,
        USB_DRIVER_STATE_busy = 0x03u,
        USB_DRIVER_STATE_timeout = 0x04u,
    } USB_DRIVER_STATE_t;

    typedef enum
    {
        USB_DRIVER_MUTEX_unlocked = 0x00u,
        USB_DRIVER_MUTEX_locked = 0x01u,
    } USB_DRIVER_MUTEX_t;

    /* Link-power management state */
    typedef enum
    {
        USB_DRIVER_LPM_l0 = 0x00u,
        USB_DRIVER_LPM_l1 = 0x01u,
        USB_DRIVER_LPM_l2 = 0x02u,
        USB_DRIVER_LPM_l3 = 0x03u,
    } USB_DRIVER_LPM_t;

    typedef enum
    {
        GINTSTS_RXFLVL_gout_nak = 0x01u,
        GINTSTS_RXFLVL_data_update = 0x02u,
        GINTSTS_RXFLVL_xfer_cplt = 0x03u,
        GINTSTS_RXFLVL_stup_cplt = 0x04u,
        GINTSTS_RXFLVL_stup_update = 0x06u,
    } GINTSTS_RXFLVL_t;

    /**
 * @fn usbDriver_setDelayFunc
 * @brief register a function pointer that generates a blocking delay 
 * with the USB driver layer
 * 
 * @param delayFunc the function ptr to register.
 */
    void usbDriver_setDelayFunc(void (*delayFunc)(uint32_t));

    /**
 * @fn usbDriver_setAllocatorFunc
 * @brief register a function pointer to a runtime allocator
 * with the USB driver layer
 * 
 * @param allocatorFunc the allocator function pointer
 */
    void usbDriver_setAllocatorFunc(void *(*allocatorFunc)(size_t));

    /**
 * @fn usbDriver_setDeallocatorFunc
 * @brief register a function pointer to a runtime deallocator with
 * the USB driver layer
 * 
 * @param deallocatorFunc the function pointer
 */
    void usbDriver_setDeallocatorFunc(void (*deallocatorFunc)(void *));

    /**
 * @fn usbDriver_setMemsetFunc
 * @brief register a function pointer to a memory writing func
 * with the USB driver layer
 * 
 * @param memsetFunc the function pointer
 */
    void usbDriver_setMemsetFunc(void *(*memsetFunc)(void *, int, size_t));

    /**
 * @fn usbDriver_setPhyInitFunc
 * @brief register a function pointer that performs the initialization
 * of the USB peripheral PHY. It must comply with the specification on
 * enumeration sequence for USB 2.0 spec.
 * 
 * @param physicalLayerInitFunc the function pointer
 */
    void usbDriver_setPhyInitFunc(void (*physicalLayerInitFunc)(void));

    /**
 * @fn USBD_Delay
 * @brief Execute a blocking delay with the USB driver's registered delay
 * function
 * 
 * @param ms the blocking period in milliseconds 
 */
    void USBD_Delay(uint32_t ms);

    /**
 * @fnUSBD_malloc
 * @brief Return a runtime-pointer to an allocated block of memory
 * created with the USB driver's registered allocator function
 * 
 * @param size the size of the block of memory to allocate in bytes
 * @return void* Pointer to the start of the block of memory
 */
    void *USBD_malloc(size_t size);

    /**
 * @fn USBD_free
 * @brief Deallocate a block of memory at runtime using the USB driver
 * layer's registered deallocator
 * 
 * @param ptr pointer to the start of the block of memory
 */
    void USBD_free(void *ptr);

    /**
 * @fn USBD_memset
 * @brief Write a block of memory using the memset function
 * registered with the USB device driver
 * 
 * @param ptr pointer to start of memory block to write
 * @param value the value to write
 * @param num the number of bytes to write starting from
 * address of ptr
 * @return void* the address of the last byte written successfully
 */
    void *USBD_memset(void *ptr, int value, size_t num);

    /**
 * @fn USBD_PhyInit
 * @brief perform initialization of the USB Peripheral's 
 * PHY configuration using the registered function
 * in the USB driver
 */
    void USBD_PhyInit(void);

#endif /* USE_HAL_DRIVER */

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */
