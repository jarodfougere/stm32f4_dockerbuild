/**
 * @file rimot_usb.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the usb otg
 * peripheral on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
 *
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 *
 * This software is licensed under the Berkley Software Distribution (BSD)
 * 3-Clause license. Redistribution and use in source and binary forms,
 * with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(USE_HAL_DRIVER)

#include <stdint.h>
#include <stdlib.h>
#include <string.h> /* memset */
#include <stdio.h>  /* printf formatting */

#include "rimot_rcc.h"
#include "rimot_gpio.h"
#include "rimot_usb.h"

#include "ATTRIBUTE_PORTABILITY_HEADER.h"
#include "cmsis_compiler.h"
#include "rimot_LL_debug.h"
#include "rimot_bus_region_offsets.h"
#include "rimot_interrupts.h"
#include "rimot_pin_aliases.h"
#include "rimot_usb_register_masks.h"

/* PHY DEFINTIONS */
#define USB_VBUS_PIN     MCUPIN_PA9
#define USB_DATA_POS_PIN MCUPIN_PA12
#define USB_DATA_NEG_PIN MCUPIN_PA11

#define USB_OTG_FS_TOTAL_FIFO_SIZE      1280U /* Size in Bytes */
#define USB_OTG_FS_HOST_MAX_CHANNEL_NBR 8U    /* include HC0 */
#define USB_OTG_FS_MAX_DEVICE_ENDPTS    4U    /* Including EP0 */
#define USB_OTG_FS_MAX_IN_ENDPOINTS     USB_OTG_FS_MAX_DEVICE_ENDPTS
#define USB_OTG_FS_MAX_OUT_ENDPOINTS    USB_OTG_FS_MAX_DEVICE_ENDPTS
#define USB_OTG_FIFO_SIZE               4000U /* 4 kB */

#define USB_OTG_CORE_ID_300A 0x4F54300AU
#define USB_OTG_CORE_ID_310A 0x4F54310AU

#define USB_OTG_REGISTER_BASE 0x50000000UL

/* Bit positions and masks in bmRequestType */
#define bmRequestType_DIR_POS    (7)
#define bmRequestType_DIR_MSK    (1U << bmRequestType_DIR_POS)
#define bmRequestType_DIR_toDev  (0)
#define bmRequestType_DIR_toHost (1)

#define bmReuqestType_TYPE_POS      (5u)
#define bmReuqestType_TYPE_MSK      (0x3u << (bmReuqestType_TYPE_POS))
#define bmRequestType_TYPE_standard (0u)
#define bmRequestType_TYPE_class    (1u)
#define bmRequestType_TYPE_vendor   (2u)
#define bmRequestType_TYPE_reserved (0u)

#define bmRequestType_TARGET_POS       (0)
#define bmRequestType_TARGET_MSK       (0xFU << (bmReuqestType_TARGET_POS))
#define bmRequestType_TARGET_device    (0)
#define bmRequestType_TARGET_interface (1)
#define bmRequestType_TARGET_endpoint  (2)
#define bmRequestType_TARGET_other     (3)

/* Codes for bRequest in a usb Setup packet */
#define bRequest_GET_STATUS        0
#define bRequest_CLEAR_FEATURE     1
#define bRequest_SET_FEATHER       3
#define bRequest_SET_ADDRESS       5
#define bRequest_GET_DESCRIPTOR    7
#define bRequest_GET_CONFIGURATION 8
#define bRequest_GET_INTERFACE     10
#define bRequest_SET_INTERFACE     11
#define bRequest_SYNC_FRAME        12

/* 64 BYTES MAX FOR FS (USB 2.0 SPEC) */
#define USB_OTG_FS_CTL_XFER_MAX_PACKET_SIZE 64

/* Ref man page 1261 section 34.13.1 */
#define USB_OTG_FS_NUM_SETUP_PACKETS 10

/* This is my own value to prevent from hanging in an enum loop forever */
#define USB_OTG_ENUM_POLLTIMEOUT_MAX 20000

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
    volatile uint32_t GOTGCTL;            /* 0x0000  */
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

    } DIEP[USB_OTG_FS_MAX_IN_ENDPOINTS];

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
    } DOEP[USB_OTG_FS_MAX_OUT_ENDPOINTS];

    PAD_WITH_BYTES(0X0B7c, 0x0E00);

    volatile uint32_t PCGCTL; /* 0x0e00 */

    PAD_WITH_BYTES(0x0e00, 0x1000);

    struct
    {
        /* Push/Pop to this region */
        volatile uint8_t buf[USB_OTG_FIFO_SIZE];
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
    uint8_t  num;            /* The endpoint number. 1 to 15               */
    uint8_t  is_in;          /* If the endpoint is an IN ep. 1 or 0        */
    uint8_t  is_stall;       /* If the endpoint is stalled. 1 or 0         */
    uint8_t  type;           /* Endpoint type                              */
    uint8_t  data_pid_start; /* 0 or 1                                     */
    uint8_t  even_odd_frame; /* Parity. 1 for odd, 0 for even              */
    uint16_t tx_fifo_num;    /* mapped FIFO id. 1 to 15                    */
    uint32_t maxpacket;      /* Endpoint Max Packet size (kB)              */
    uint8_t *xfer_buff;      /* Pointer to xfer buffer                     */
    uint32_t xfer_len;       /* xfer length IN BYTES (not words)           */
    uint32_t xfer_count;     /* xfer counts (case of multi-pkt xfer)       */
} usbEndPoint_t;

/* Host channels are pretty much endpoints with more features
(but  they're host mode only) */
typedef struct
{
    uint8_t  dev_addr;     /* USB device address. 1 to 255.             */
    uint8_t  ch_num;       /* Host channel number. 1 to 15              */
    uint8_t  ep_num;       /* Endpoint number. 1 to 15                  */
    uint8_t  ep_is_in;     /* Endpoint direction. 0 to 1 (1 == IN ep)   */
    uint8_t  speed;        /* USB Host speed. One of USBH_HPRT_PRTSPD_t */
    uint8_t  do_ping;      /* Ena/Dis the use of the PING for HS mode   */
    uint8_t  process_ping; /* HS mode flag to do ping protocol          */
    uint8_t  ep_type;      /* Endpoint Type. One of USB_EPTYPE_t        */
    uint16_t max_packet;   /* Endpoint Max packet size in kB. 0 to 64   */
    uint8_t  data_pid;     /* Initial data PID flag. 0 to 1             */
    uint8_t *xfer_buff;    /* Pointer to transfer buffer.               */
    uint32_t xfer_len;     /* Current transfer                          */
    uint32_t xfer_count;   /* xfer counts (case of multi-pkt xfer)      */
    uint8_t  toggle_in;    /* IN transfer current toggle flag. 0 to 1   */
    uint8_t  toggle_out;   /* OUT transfer current toggle flag. 0 to 1  */
    uint32_t ErrCnt;       /* Host channel error count.                 */
    uint32_t urb_state;    /* URB state. One of USBD_URB_STATE__t         */
    uint32_t state;        /* Host Channel state. One of USBH_CHSTATE_t */
} usbHostChannel_t;

typedef union
{
    __packed struct
    {
        /*
         * in bmRequest type:
         * bit[]
         * bit 7 : data direction (0 == to device, 1 == to host),
         * bit[6:5]
         *
         */
        uint8_t  bmRequestType;
        uint8_t  bRequest;
        uint16_t wValue;
        uint16_t wIndex;
        uint16_t wLength;
    } fields;
    uint8_t bytes[8];

} usbSetupPacket;

struct usbProtocolDriverStruct
{
    USB_t *regs;
    usbClassDriverPtr class;
    uint8_t setupPackets[USB_OTG_FS_NUM_SETUP_PACKETS];

    enum
    {
        CORE_INITIALIZATION,
        WAITING_FOR_BUS_IDLE,
        STARTUP_FROM_SOFT_RESET,
        DEVICE_INITIALIZATION,
        NEGOTIATING_WITH_HOST,
        ENUMERATION_COMPLETE,
    } enumState;

    /**
     * @todo:
     *
     * Pointer to word-aligned byte array for RX Fifo
     */
};

static uint32_t usbDeviceEnumerate(usbProtocolDriver *driver);

/*
 * READ REF MANUAL SECTION 34.17.1 FOR
 * REQUIRED ENUMERATION SEQUENCE
 * REV18 :: PAGE 1335
 */

/* We need a persistence pointer because exception frame has no
knowledge of lower callstack and USB interrupt occurs */
static usbProtocolDriver *driverPtr;

/* Driver instance constructor */
usbProtocolDriver *usbProtocolDriverInit(usbClassDriverPtr class)
{
    usbProtocolDriver *driver;
    driver = (usbProtocolDriver *)malloc(sizeof(usbProtocolDriver));
    LL_ASSERT(driver != NULL);

    driver->regs = ((USB_t *)(USB_OTG_REGISTER_BASE));
    driverPtr    = driver; /* Link initializer to static module ptr */

    driver->class = class; /* Link class handle */
    memset(driver->setupPackets, 0, sizeof(driver->setupPackets));
    driver->enumState = WAITING_FOR_BUS_IDLE;

    return driver;
}

uint32_t usbDeviceInit(usbProtocolDriver *driver)
{
    /* CONFIGURE THE PHY */

    gpio_enablePinClock(USB_VBUS_PIN);
    gpio_setPinMode(USB_VBUS_PIN, GPIO_MODE_input);
    gpio_setPinPull(USB_VBUS_PIN, GPIO_PIN_PULL_MODE_none);
    gpio_setPinAlternateFunc(USB_VBUS_PIN, GPIO_ALT_FUNC_10);

    /* Configure D- pin */
    gpio_enablePinClock(USB_DATA_NEG_PIN);
    gpio_setPinMode(USB_DATA_NEG_PIN, GPIO_MODE_alternate);
    gpio_setPinPull(USB_DATA_NEG_PIN, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSupplyMode(USB_DATA_NEG_PIN, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setPinSpeed(USB_DATA_NEG_PIN, GPIO_SPEED_max);
    gpio_setPinAlternateFunc(USB_DATA_NEG_PIN, GPIO_ALT_FUNC_10);

    /* Configure D+ pin */
    gpio_enablePinClock(USB_DATA_POS_PIN);
    gpio_setPinMode(USB_DATA_POS_PIN, GPIO_MODE_alternate);
    gpio_setPinPull(USB_DATA_POS_PIN, GPIO_PIN_PULL_MODE_none);
    gpio_setPinSupplyMode(USB_DATA_POS_PIN, GPIO_PIN_SUPPLY_MODE_push_pull);
    gpio_setPinSpeed(USB_DATA_POS_PIN, GPIO_SPEED_max);
    gpio_setPinAlternateFunc(USB_DATA_POS_PIN, GPIO_ALT_FUNC_10);

    /* Start USB Peripheral clock (assumes prescalers already set) */
    rccEnablePeriphClock(RCC_PERIPH_CLOCK_usb);

    /* Configure interrupt preemption in NVIC and unmask ISR */
    interruptSetPrio(OTG_FS_IRQn, NVIC_PREEMPTION_PRIO_0, NVIC_SUBPRIO_0);
    interruptSetState(OTG_FS_IRQn, INTERRUPT_STATE_enabled);

    uint32_t status = 0;
    LL_ASSERT(NULL != driver);

    /* Acquire a session with the host */
    usbDeviceEnumerate(driver);

    return status;
}

/*
Device initialization
The application must perform the following steps to initialize the core as a
device on powerup or after a mode change from host to device.
1. Program the following fields in the OTG_FS_DCFG register:
– Device speed
– Non-zero-length status OUT handshake
2. Program the OTG_FS_GINTMSK register to unmask the following interrupts:
– USB reset
– Enumeration done
– Early suspend
– USB suspend
– SOF
3. Program the VBUSBSEN bit in the OTG_FS_GCCFG register to enable VBUS
sensing in “B” device mode and supply the 5 volts across the pull-up
resistor on the DP line.
4. Wait for the USBRST interrupt in OTG_FS_GINTSTS. It indicates that a
reset has been detected on the USB that lasts for about 10 ms on receiving
this interrupt. Wait for the ENUMDNE interrupt in OTG_FS_GINTSTS. This
interrupt indicates the end of reset on the USB. On receiving this
interrupt, the application must read the OTG_FS_DSTS register to determine
the enumeration speed and perform the steps listed in Endpoint
initialization on enumeration completion on page 1353. At this point, the
device is ready to accept SOF packets and perform control transfers on
control endpoint 0.
*/

static uint32_t usbDeviceEnumerate(usbProtocolDriver *driver)
{
    uint32_t errCode = 0;
    uint32_t count   = 0;

    /**
     *
     * TURNAROUND VALUE.
     *
     * THIS IS A FUNCTION OF AHB BUS FREQUENCY
     * (IE: FUNCTION OF RCC CONFIGURATION)
     * SEE TABLE 203 IN REF MANUAL PAGE 1276 (REV 18)
     *
     * @todo Implement the table lookup based on RCC config.
     * For now, Since we know we'll be running at 48MHz,
     * we can just set 0x06u as the value.
     */
    const uint32_t trdt_val = 0x0A; /** @todo revise val to table lookup*/
    const uint32_t maxCount = USB_OTG_ENUM_POLLTIMEOUT_MAX;

    /*
     * Make sure we aren't re-enumerating. This could occur when we
     * transition from CDC to DFU in composite device class
     */

    /* State machine */
    for (driver->enumState = STARTUP_FROM_SOFT_RESET;
         driver->enumState != ENUMERATION_COMPLETE;
         count++)
    {
        /* Timeout check */
        if (count > maxCount)
        {
            errCode = driver->enumState;
            break;
        }

        switch (driver->enumState)
        {
            case WAITING_FOR_BUS_IDLE:
            {
                /* Wait until bus is idle */
                if (driver->regs->GRSTCTL & GRSTCTL_AHBIDL)
                {
                    /* Initiate soft reset */
                    driver->regs->GRSTCTL |= GRSTCTL_CSRST;
                    driver->enumState = STARTUP_FROM_SOFT_RESET;
                }
            }
            break;
            case STARTUP_FROM_SOFT_RESET:
            {
                /* Hardware has cleared CSRST indicating completed soft reset */
                if (0 == (driver->regs->GRSTCTL & GRSTCTL_CSRST))
                {
                    driver->enumState = CORE_INITIALIZATION;
                }
            }
            break;
            case CORE_INITIALIZATION:
            {
                /** @note SEE SECTION 22.17.1 IN RM0383 */
                driver->regs->GAHBCFG |= (GAHBCFG_GINT | GAHBCFG_PTXFELVL);
                driver->regs->GINTSTS |= GINTSTS_RXFLVL;
                driver->enumState = DEVICE_INITIALIZATION;

                driver->regs->GUSBCFG =

                    /* Enable host negotiaton protocol */
                    (GUSBCFG_HNPCAP) |

                    /* Enable session request protocol */
                    (GUSBCFG_SRPCAP) |

                    /* Set the turnaround time for bit xfer on AHB */
                    (trdt_val << GUSBCFG_TRDT_POS) |

                    /* Recommended value for FS PHY calibration */
                    (18 << GUSBCFG_TOCAL_POS);

                /* Enable on-the-go and mode mismanagement interrupts */
                driver->regs->GINTMSK |= (GINTMSK_OTGINT | GINTMSK_MMISM);

                /* Force device mode */
                driver->regs->GUSBCFG &= ~(GUSBCFG_FDMOD | GUSBCFG_FHMOD);
                driver->regs->GUSBCFG |= GUSBCFG_FDMOD;

                driver->enumState = DEVICE_INITIALIZATION;
            }
            break;
            case DEVICE_INITIALIZATION:
            {
                driver->regs->GINTMSK |= (GINTMSK_USBRST) | (GINTMSK_ENUMDNEM) |
                                         (GINTMSK_ESUSPM) | (GINTMSK_USBSUSPM) |
                                         (GINTMSK_SOFM);
                /** @note SEE SECTION 22.17.3 IN RM0383 */

                /* Force device mode */

                /*
                 * DCFG :: NZLSOHSK: Non-zero-length status OUT handshake
                 * 1:  Send a STALL handshake on a nonzero-length status OUT
                 *     transaction and do not send the received OUT packet to
                 *     the application.
                 * 0:  Send the received OUT packet to the application
                 *     (zero-length or nonzero-length) and send a handshake
                 *     based on theNAK and STALL bits for the endpoint in
                 *     the Device endpoint control register.
                 */
                driver->regs->DCFG &= ~(DCFG_NZLSOHSK);

                /* Configure for full speed */
                driver->regs->DCFG |= (DCFG_DSPD_FULLSPEED);

                driver->regs->GCCFG &= ~GCCFG_NOVBUSSENS;
                driver->regs->GCCFG |= (GCCFG_VBUS_B_SEN);

                driver->enumState = NEGOTIATING_WITH_HOST;
            }
            break;
            default:
            {
                LL_ASSERT(0);
            }
            break;
        }
    }
    return errCode;
}

void OTG_FS_IRQHandler(void)
{
    LL_ASSERT(NULL != driverPtr);

    volatile uint32_t globalInt = driverPtr->regs->GINTSTS;
    uint32_t          flagMsk;

    if (((driverPtr->regs->GINTSTS & GINTSTS_CMOD) == CMOD_DEVICE))
    {
        for (flagMsk = 0; flagMsk < 31; flagMsk <<= 1)
        {
            switch (globalInt & flagMsk)
            {
                case GINTSTS_MMIS: /* Mode mismanagement interrupt */
                {
                    /*
                     * The core sets this bit when the application is trying
                     * to access: – A host mode register, when the core is
                     * operating in device mode – A device mode register,
                     * when the core is operating in host mode The register
                     * access is completed on the AHB with an OKAY response,
                     * but is ignored by the core internally and does not
                     * affect the operation of the core.
                     */

                    /* Acknowledge interrupt but do nothing */
                    driverPtr->regs->GINTSTS &= ~(GINTSTS_MMIS);
                }
                break;
                case GINTSTS_OTGINT: /* OTG protocol event */
                {
                    /*
                     * The core sets this bit to indicate an OTG protocol
                     * event. The application must read the OTG Interrupt
                     * Status (OTG_FS_GOTGINT) register to determine the
                     * exact event that caused this interrupt. The
                     * application must clear the appropriate status bit in
                     * the OTG_FS_GOTGINT register to clear this bit.
                     */
                }
                break;
                case GINTSTS_SOF: /* Start of frame */
                {
                    /*
                     * In host mode, the core sets this bit to indicate that
                     * an SOF (FS), or Keep-Alive (LS) is transmitted on the
                     * USB. The application must write a 1 to this bit to
                     * clear the interrupt. In device mode, in the core sets
                     * this bit to indicate that an SOF token has been
                     * received on the USB. The application can read the
                     * Device Status register to get the current frame
                     * number. This interrupt is seen only when the core is
                     * operating in FS.
                     */
                }
                break;
                case GINTSTS_RXFLVL:
                {
                    /*
                     * RX FIFO level non-empty
                     * (device has recieved from host)
                     */
                }
                break;
                case GINTSTS_NPTXFE:
                {
                    /* Non-periodic fifo non-empty (device wants to xmit) */
                }
                case GINTSTS_GINAKEFF:
                {
                    /*
                     * isochronous IN NAK effective interrupt
                     * Indicates that the Set global non-periodic IN NAK bit
                     * in the OTG_FS_DCTL register (SGINAK bit in
                     * OTG_FS_DCTL), set by the application, has taken
                     * effect in the core. That is, the core has sampled the
                     * Global IN NAK bit set by the application. This bit
                     * can be cleared by clearing the Clear global
                     * non-periodic IN NAK bit in the OTG_FS_DCTL register
                     * (CGINAK bit in OTG_FS_DCTL). This interrupt does not
                     * necessarily mean that a NAK handshake is sent out on
                     * the USB.
                     *
                     * NOTE : The STALL bit takes precedence over the NAK
                     * bit.
                     */

                    /* Clear GINSTS :: GINAKEFF by clearing DTCL::GGINAK */
                    driverPtr->regs->DCTL &= ~(DCTL_CGINAK);
                }
                break;
                case GINTSTS_GOUTNAKEFF:
                {
                    /*
                     * OUT NAK effective interrupt.
                     * Indicates that the Set global OUT NAK bit in the
                     * OTG_FS_DCTL register (SGONAK bit in OTG_FS_DCTL),
                     * set by the application, has taken effect in the core.
                     * This bit can be cleared by writing the Clear global
                     * OUT NAK bit in the OTG_FS_DCTL register (CGONAK bit
                     * in OTG_FS_DCTL).
                     */

                    /* Clear GINSTS :: GONAKEFF by setting DTCL::GGONAK */
                    driverPtr->regs->DCTL |= (DCTL_CGONAK);
                }
                break;
                case GINTSTS_ESUSP:
                {
                    /* Early suspend (no activity on D+ for ~3ms) */
                }
                break;
                case GINTSTS_USBSUSP:
                {
                    /* Host-issued USB suspend */
                }
                break;
                case GINTSTS_USBRST:
                {
                    /* See sectuib 22.17.5 in RM0383 */
                    unsigned i;

                    /* Set the NAK bit for all OUT endpoints */
                    for (i = 0; i < USB_OTG_FS_MAX_OUT_ENDPOINTS; i++)
                    {
                        driverPtr->regs->DIEP[i].CTL |= (DIEPCTL_SNAK);
                    }

                    /* Unmaks IN_EP0 and OUT_EP0 in DAINTMSK */
                    driverPtr->regs->DAINTMSK |=
                        (1 << DAINTMSK_IEPM_POS) | (1 << DAINTMSK_OEPM_POS);

                    driverPtr->regs->DOEPMSK |=
                        (DOEPMSK_STUPM) | (DOEPMSK_XFRCM);

                    driverPtr->regs->DIEPMSK |= (DIEPMSK_XFRCM | DIEPMSK_TOC);

                    /* STEP 3: Set up the Data FIFO RAM for each of the FIFOs */

                    uint32_t tmp = USB_OTG_FS_CTL_XFER_MAX_PACKET_SIZE;
                    tmp += 2;  /* 2 words for status of control packet */
                    tmp += 10; /* 10 words for bytes in setup pkts */

                    driverPtr->regs->GRXFSIZ = (tmp << GRXFSIZ_RXFD_POS);

                    /*
                     * Factor of 2 for greater performance
                     * (datasheet advised)
                     */
                    tmp = 2 * USB_OTG_FS_CTL_XFER_MAX_PACKET_SIZE;
                    driverPtr->regs->DIEPTXF0_HNPTXFSIZ &= ~(DIEPTXF_INEPTXFD);
                    driverPtr->regs->DIEPTXF0_HNPTXFSIZ |=
                        (tmp << DIEPTXF_INEPTXFD_POS);

                    /*
                     * STEP 4 : program OUT endpoint to receive 3 back to back
                     * setup packets
                     */
                    driverPtr->regs->DOEP[0].SIZ |= (3 << DOEPTSIZ_STUPCNT_POS);
                }
                break;
                case GINTSTS_ENUMDNE:
                {
                    /* See sectuib 22.17.5 in RM0383 */
                    /* Get enumerated speed bits from DSTS */
                    uint32_t enumeratedSpeed = driverPtr->regs->DSTS;
                    enumeratedSpeed &= DSTS_ENUMSPD;
                    enumeratedSpeed >>= DSTS_ENUMSPD_POS;

                    /*
                     * On this MCU, the only speed at which the periph
                     * can enumerate is FS @ 48MHz. It seems like this
                     * is a hardware limitation
                     */
                    switch (enumeratedSpeed)
                    {
                        case 3:
                        {
                            driverPtr->regs->DIEP[0].CTL &= ~DIEPCTL_MPSIZ;
                            driverPtr->regs->DIEP[0].CTL |=
                                (DIEPCTL_MPSIZ_64bytes << DIEPCTL_MPSIZ_POS);
                        }
                        break;
                        default:
                        {
                            /* Hang forever in debug mode */
                            LL_ASSERT(0);
                        }
                        break;
                    }
                }
                break;
                case GINTSTS_ISOODRP:
                {
                    /* dropped isoc OUT packet */
                }
                break;
                case GINTSTS_EOPF:
                {
                    /* End of periodic frame */
                }
                break;
                case GINTSTS_IEPINT:
                {
                    /* an IN endpt caused an interrupt */
                }
                break;
                case GINTSTS_OEPINT:
                {
                    /* an OUT endpt caused an interrupt */
                }
                break;
                case GINTSTS_IISOIXFR:
                {
                    /* Incomple isoc xfer IN */
                }
                break;
                case GINTSTS_PXFR_INCOMPISOOUT:
                {
                    /*
                     * Incomplete isochronous OUT trnasfer interrupt
                     *  In device mode, the core sets this interrupt to
                     * indicate that there is at least one isochronous OUT
                     * endpoint on which the transfer is not completed in
                     * the current frame. This interrupt is asserted along
                     * with the End of periodic frame interrupt (EOPF) bit
                     * in this register
                     */
                }
                break;
                case GINTSTS_CIDSCHG:
                {
                    /* Connector ID status change */
                }
                break;
                case GINTSTS_SRQINT:
                {
                    /*
                     * Session request/new session detected interrupt
                     *
                     *  In host mode, this interrupt is asserted when a
                     * session request is detected from the device. In
                     * device mode, this interrupt is asserted when VBUS is
                     *  in the valid range for a B-peripheral
                     */
                }
                break;
                case GINTSTS_WKUINT: /* Resume/remote wakeup detcted */
                {
                    /*
                     * In device mode, this interrupt is asserted
                     * when a resume is detected on the USB.
                     * In host mode, this interrupt is asserted when a
                     * remote wakeup is detected on the USB.
                     */
                }
                break;
                default:
                {
                    /* DO NOTHING */
                }
                break;
            }
        }
    }
    else /* HOST MODE */
    {
    }
}

#endif /* !USE_HAL_DRIVER */
