#ifndef RIMOT_MCU_USB_OTG_CONFIG
#define RIMOT_MCU_USB_OTG_CONFIG
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage*/
#if defined(MCU_APP)

#include <stdlib.h> /* Size_t */
#include <stdint.h>

    /**
 * @todo THIS MODULE IS GIGANTIC!!
 * 
 * REFACTOR INTO 5 PARTS.
 * - Peripheral memory map + register manipulation
 * - CORE API
 * - DEVICE LOW-LAYER
 * - HOST LOW-LAYER
 * - USB_DRIVER
 */

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
 * @brief REGISTER MEMORY MAP FOR USB OTG PERIPHERAL
 * 
 * @todo 
 * LOOK IN CMSIS_COMPILER.H 
 * AND USE THE ACTUAL PORTABLE 
 * KEYWORD FOR PACKING 
 */
    typedef __packed struct /* ## WARNING ## MUST BE PACKED TO BE PORTABLE */
    {
        /* USB CORE REGS */
        volatile uint32_t GOTCTL;             /* 0x0000  */
        volatile uint32_t GOTGINT;            /* 0x0004  */
        volatile uint32_t GAHBCFG;            /* 0x0008  */
        volatile uint32_t GUSBCFG;            /* 0x000C  */
        volatile uint32_t GRSTCTL;            /* 0x0010  */
        volatile uint32_t GINTSTS;            /* 0x0014  */
        volatile uint32_t GINTMSK;            /* 0x0018  */
        volatile uint32_t GRXSTSR;            /* 0x001C  */
        volatile uint32_t GRXSTSP;            /* 0x0020  */
        volatile uint32_t GRXFSIZ;            /* 0x0024  */
        volatile uint32_t DIEPTXF0_HNPTXFSIZ; /* 0x0028  */
        volatile uint32_t HNPTXSTS;           /* 0x002c  */

        PAD_WITH_BYTES(0x002c, 0x0038);

        volatile uint32_t GCCFG; /* 0x0038  */
        volatile uint32_t CID;   /* 0x003C  */

        PAD_WITH_BYTES(0x0100, 0x003C);

        volatile uint32_t HPTXFSIZ;    /* 0x0100  */
        volatile uint32_t DIEPTXF[15]; /* 0x0104  */

        PAD_WITH_BYTES(0x013C, 0x0400);

        /* USB HOST CFG REGS */
        volatile uint32_t HCFG;  /* 0x0400  */
        volatile uint32_t HFIR;  /* 0x0404  */
        volatile uint32_t HFNUM; /* 0x0408  */

        PAD_WITH_BYTES(0x0410, 0x0408);

        volatile uint32_t HPTXSTS;  /* 0x0410  */
        volatile uint32_t HAINT;    /* 0x0414  */
        volatile uint32_t HAINTMSK; /* 0x0418  */

        PAD_WITH_BYTES(0x0440, 0x0418);

        volatile uint32_t HPRT; /* 0x0440  */

        PAD_WITH_BYTES(0x0500, 0x0440);

        /* HOST CHANNELS */
        struct
        {
            volatile uint32_t CHAR;   /* 0x0500 + (0x0020 * ch_idx)   */
            volatile uint32_t SPLIT;  /* 0x0504 + (0X0020 * ch_idx)   */
            volatile uint32_t INT;    /* 0x0508 + (0x0020 * ch_idx)   */
            volatile uint32_t INTMSK; /* 0x050c + (0x0020 * ch_idx)   */
            volatile uint32_t TSIZ;   /* 0x0510 + (0x0020 * ch_idx)   */
            volatile uint32_t DMA;    /* 0x0514 + (0x0020 * ch_idx)   */

            PAD_WITH_BYTES(0x0520, 0x0514);

        } HC[USB_OTG_FS_HOST_MAX_CHANNEL_NBR];

        PAD_WITH_BYTES(0x05fc, 0x0800);

        /* DEVICE CONFIG REGISTERS */
        volatile uint32_t DCFG; /* 0x0800  */
        volatile uint32_t DCTL; /* 0x0804  */
        volatile uint32_t DSTS; /* 0x0808  */

        PAD_WITH_BYTES(0X0808, 0x0810);

        volatile uint32_t DIEPMSK;  /* 0x0810  */
        volatile uint32_t DOEPMSK;  /* 0x0814  */
        volatile uint32_t DAINT;    /* 0x0818  */
        volatile uint32_t DAINTMSK; /* 0x081c  */

        PAD_WITH_BYTES(0x081c, 0x0828);

        volatile uint32_t DVBUSDIS;   /* 0x0828  */
        volatile uint32_t DVBUSPULSE; /* 0x082c  */
        volatile uint32_t DTHRCTL;    /* 0x0830  */
        volatile uint32_t DIEPEMPMSK; /* 0x0834  */
        volatile uint32_t DEACHINT;   /* 0x0838  */
        volatile uint32_t DEACHMSK;   /* 0x083C  */

        PAD_WITH_BYTES(0x083c, 0x844);

        volatile uint32_t DINEP1MSK; /* 0x0844  */

        PAD_WITH_BYTES(0x0884, 0x844);

        volatile uint32_t DOUTEP1MSK; /* 0x0884  */

        PAD_WITH_BYTES(0x0884, 0x0900);

        /* Device IN endpoints */
        struct
        {
            volatile uint32_t CTL; /* 0x0900 + (0x0020 * EP_idx)   */

            PAD_WITH_BYTES(0x0900, 0x0908);

            volatile uint32_t INT; /* 0x0908 + (0x0020 * EP_idx)   */

            PAD_WITH_BYTES(0x0908, 0x0910);

            volatile uint32_t SIZ;    /* 0x0910 + (0x0020 * EP_idx)   */
            volatile uint32_t DMA;    /* 0x0914 + (0x0020 * EP_idx)   */
            volatile uint32_t TXFSTS; /* 0x0918 + (0x0020 * EP_idx)   */

            PAD_WITH_BYTES(0x0918, 0x0920);

        } DIEP[__USB_OTG_FS_MAX_IN_ENDPOINTS];

        PAD_WITH_BYTES(0x097c, 0x0b00);

        /* Device IN endpoints */
        struct
        {
            volatile uint32_t CTL; /* 0x0b00 + (0x0020 * EP_idx)   */

            PAD_WITH_BYTES(0x0900, 0x0908);

            volatile uint32_t INT; /* 0x0b08 + (0x0020 * EP_idx)   */

            PAD_WITH_BYTES(0x0908, 0x0910);

            volatile uint32_t SIZ;    /* 0x0b10 + (0x0020 * EP_idx)   */
            volatile uint32_t DMA;    /* 0x0b14 + (0x0020 * EP_idx)   */
            volatile uint32_t TXFSTS; /* 0x0b18 + (0x0020 * EP_idx)   */

            PAD_WITH_BYTES(0x0918, 0x0920);
        } DOEP[__USB_OTG_FS_MAX_OUT_ENDPOINTS];

        PAD_WITH_BYTES(0X0B7c, 0x0E00);

        volatile uint32_t PCGCTL; /* 0x0e00 */

        PAD_WITH_BYTES(0x0e00, 0x1000);

        struct
        {
            /* Push/Pop to this region */
            volatile uint8_t buf[__USB_OTG_FIFO_SIZE];
        } DFIFO[8];

        PAD_WITH_BYTES(0X8cfc, 0x20000);

        struct
        {
            /* Fifo for diagnostic info */
            volatile uint8_t buf[128000]; /* 128 kB */
        } DRW_FIFO;

    } USB_t;

    /* This is an abstract config structure for the features
supported by USB-OTG spec */
    typedef struct
    {
        uint32_t dev_endpoints;       /* Num Device Endpoints. 1 to 15       */
        uint32_t Host_channels;       /* Num host channels. 1 to 15          */
        uint32_t speed;               /* Core speed. One of USB_OTG_SPEED_t  */
        uint32_t ep0_mps;             /* Endpoint 0 Max Packet size (kB)     */
        uint32_t Sof_enable;          /* Ena/Dis the SOF signal              */
        uint32_t low_power_enable;    /* Ena/Dis the low power mode.         */
        uint32_t lpm_enable;          /* Ena/Dis Link Power Management.      */
        uint32_t bat_charging_ena;    /* Enable or disable Battery charging. */
        uint32_t vbus_sensing_enable; /* Enable or disable VBUS sensing      */
        uint32_t use_dedicated_ep1;   /* Ena/Dis the dedicated EP1 int.      */
        uint32_t use_external_vbus;   /* Ena/Dis use of the extern VBUS.     */
    } usbOTGConfig_t;

    /* abstract USB 2.0 EP config struct */
    typedef struct
    {
        uint8_t num;            /* The endpoint number. 1 to 15               */
        uint8_t is_in;          /* If the endpoint is an IN ep. 1 or 0        */
        uint8_t is_stall;       /* If the endpoint is stalled. 1 or 0         */
        uint8_t type;           /* Endpoint type                              */
        uint8_t data_pid_start; /* 0 or 1                                     */
        uint8_t even_odd_frame; /* Parity. 1 for odd, 0 for even              */
        uint16_t tx_fifo_num;   /* mapped FIFO id. 1 to 15                    */
        uint32_t maxpacket;     /* Endpoint Max Packet size (kB)              */
        uint8_t *xfer_buff;     /* Pointer to xfer buffer                     */
        uint32_t xfer_len;      /* xfer length IN BYTES (not words)           */
        uint32_t xfer_count;    /* xfer counts (case of multi-pkt xfer)       */
    } usbEndPoint_t;

    /* Host channels are pretty much endpoints with more features 
   (but  they're host mode only) */
    typedef struct
    {
        uint8_t dev_addr;     /* USB device address. 1 to 255.             */
        uint8_t ch_num;       /* Host channel number. 1 to 15              */
        uint8_t ep_num;       /* Endpoint number. 1 to 15                  */
        uint8_t ep_is_in;     /* Endpoint direction. 0 to 1 (1 == IN ep)   */
        uint8_t speed;        /* USB Host speed. One of USBH_HPRT_PRTSPD_t */
        uint8_t do_ping;      /* Ena/Dis the use of the PING for HS mode   */
        uint8_t process_ping; /* HS mode flag to do ping protocol          */
        uint8_t ep_type;      /* Endpoint Type. One of USB_EPTYPE_t        */
        uint16_t max_packet;  /* Endpoint Max packet size in kB. 0 to 64   */
        uint8_t data_pid;     /* Initial data PID flag. 0 to 1             */
        uint8_t *xfer_buff;   /* Pointer to transfer buffer.               */
        uint32_t xfer_len;    /* Current transfer                          */
        uint32_t xfer_count;  /* xfer counts (case of multi-pkt xfer)      */
        uint8_t toggle_in;    /* IN transfer current toggle flag. 0 to 1   */
        uint8_t toggle_out;   /* OUT transfer current toggle flag. 0 to 1  */
        uint32_t ErrCnt;      /* Host channel error count.                 */
        uint32_t urb_state;   /* URB state. One of USBD_URB_STATE__t         */
        uint32_t state;       /* Host Channel state. One of USBH_CHSTATE_t */
    } usbHostChannel_t;

    /* The actual driver handle */
    typedef struct
    {
        USB_t *Instance;                   /* Periph Register base         */
        usbOTGConfig_t Init;               /* Driver configuration params  */
        volatile uint8_t USB_Address;      /* USB Address. 0 to 255        */
        usbEndPoint_t IN_ep[16];           /* IN endpoint parameters       */
        usbEndPoint_t OUT_ep[16];          /* OUT endpoint parameters      */
        volatile USB_DRIVER_MUTEX_t mutex; /* PreEmption Mutex lock        */
        volatile USB_DRIVER_STATE_t state; /* Driver communication         */
        volatile uint32_t ErrorCode;       /* Driver Error code            */
        uint32_t Setup[12];                /* Setup packet buffer          */
        USB_DRIVER_LPM_t LPM_State;        /* Link Pwr Management State    */
        uint32_t BESL;
        uint32_t lpm_active; /* Ena/Dis Link Power MgMt      */
        uint32_t batChrgEna; /* Ena/Dis Bat charging. 0 to 1 */
        void *pData;         /* Ptr to upper stack Handler   */

        /* These are exposed because they are upper layer injected               */
        /* Caller must provide functions for these as part of driver init        */
        void (*PHYinitFunc)(void);
        void (*DelayFunc)(uint32_t);
        void (*DeallocFunc)(void *);
        void *(*AllocFunc)(size_t);
        void *(*MemsetFunc)(void *, int, size_t);
    } usbDriverHandle_t;

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

    /** @todo MORE FUNCTION DESCRIPTIONS FOR DOXYGEN AUTODOC GENERATION */
    void usbEnableGlobalInterrupt(void);
    void usbDisableGlobalInterrupt(void);
    int usbCoreInit(void);
    void usbSetTurnaroundTime(USBD_DEVSPEED_TYPE_t speed);
    int usbDeviceModeInit(void);
    int usbActivateEndpoint(usbEndPoint_t *ep);
    void usbStartEndPointXfer(usbEndPoint_t *ep);
    void usbEndPoint0StartXfer(usbEndPoint_t *ep);
    void usbEnableGlobalInterrupt(void);
    void usbDisableGlobalInterrupt(void);
    int usbCoreInit(void);
    void usbSetTurnaroundTime(USBD_DEVSPEED_TYPE_t speed);
    void usbSetMode(USB_OTG_MODE_t mode);
    int usbDeviceModeInit(void);
    int usbActivateEndpoint(usbEndPoint_t *ep);

    void *usbReadPkt(uint8_t *dst, uint16_t len);
    int usbSetEndPointStall(usbEndPoint_t *ep);
    int usbClearEndPointStall(usbEndPoint_t *ep);
    int usbStopDevice(void);
    void usbSetDeviceAddress(uint8_t address);
    void usbDeviceConnect(void);
    void usbDeviceDisconnect(void);
    uint32_t usbReadInterrupts(void);
    uint32_t usbDeviceReadAllEndPointInterrupts(uint8_t is_in);
    uint32_t usbDeviceReadOutEndPointInterrupt(uint8_t epnum);
    uint32_t usbDeviceReadInEndPointInterrupt(uint8_t epnum);
    void usbClearInterrupts(uint32_t interrupts);
    void usbActivateSetup(void);
    int usbOEP0Start(uint8_t *psetup);
    void usbHostInit(usbOTGConfig_t cfg);
    void usbHostInitFull_orLow_Speed_ClkSel(uint8_t freq);
    void usbHostResetPort(void);
    uint32_t usbHostGetSpeed(void);
    uint32_t usbHostGetCurrentFrameNum(void);
    int usbHostChannelStartXfer(usbHostChannel_t *ch);
    uint32_t usbHostChannelReadInterrupt(void);
    int usbHostChannelHalt(uint8_t chnum);
    int usbHostStop(void);
    void usbHostChannelInit(uint8_t chnum,
                            uint8_t epnum,
                            uint8_t devAddr,
                            uint8_t speed,
                            uint8_t eptype,
                            uint16_t mps);
    void usbActivateRemoteWakeup(void);
    void usbDeactivateRemoteWakeup(void);

    int usbLLDriverInit(void);
    int usbDriverStart(void);
    int usbDriverStop(void);

    void usbGatePhyClock(void);
    void usbUngatePhyClock(void);

    void usbDriver_LinkDeviceDriverHandle(void *devDriverHandle);

    int usbDeviceDriver_CloseEndpoint(usbDriverHandle_t *driver, uint8_t ep_addr);
    int usbDeviceDriver_FlushEndpoint(usbDriverHandle_t *driver, uint8_t ep_addr);
    int usbDeviceDriver_StallEndpoint(usbDriverHandle_t *driver, uint8_t ep_addr);

    int usbDeviceDriver_ClrStalledEndpoint(usbDriverHandle_t *driver,
                                           uint8_t ep_addr);

    int usbDeviceDriver_DeviceConnect(usbDriverHandle_t *driver);
    int usbDeviceDriver_DeviceDisconnect(usbDriverHandle_t *driver);

    int usbDeviceDriver_OpenEndpoint(usbDriverHandle_t *driver,
                                     uint8_t ep_addr,
                                     uint16_t ep_mps,
                                     uint8_t ep_type);

    int usbDeviceDriver_setDeviceAddress(usbDriverHandle_t *driver, uint8_t addr);

    void usbDeviceDriver_EP_Transmit(usbDriverHandle_t *driver,
                                     uint8_t ep_addr,
                                     uint8_t *pBuf,
                                     uint32_t len);

    void usbDeviceDriver_EP_Receive(usbDriverHandle_t *driver,
                                    uint8_t ep_addr,
                                    uint8_t *pBuf,
                                    uint32_t len);

    uint32_t usbDeviceDriver_GetEPRxCnt(usbDriverHandle_t *driver, uint8_t ep_addr);

#endif /* USE_HAL_DRIVER */

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */
