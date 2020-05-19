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

#if defined(USE_HAL_DRIVER)
#include "stm32f4xx_hal_pcd.h"
extern PCD_HandleTypeDef hpcd_USB_OTG_FS; /* See usbd_conf.c */
#endif                                    /* USE_HAL_DRIVER */

#if !defined(USE_HAL_DRIVER)

#include <stdint.h>
#include <stdlib.h>
#include <string.h> /* memset */
#include <stdio.h>  /* printf formatting */

#include "cmsis_compiler.h" /* __unaligned_read32 and __unaligned_write32 */

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
#define USB_FS_PKT_SZMAX 64

/* Ref man page 1261 section 34.13.1 */
#define USB_OTG_FS_NUM_SETUP_PACKETS 10

/* This is my own value to prevent from hanging in an enum loop forever */
#define USB_OTG_ENUM_POLLTIMEOUT_MAX 20000

/* Device IN endpoints */
typedef __packed struct
{
    volatile uint32_t CTL; /* 0x0900 + (0x0020 * EP_idx)   */

    PAD_WITH_BYTES(0x0900, 0x0908);

    volatile uint32_t INT; /* 0x0908 + (0x0020 * EP_idx)   */

    PAD_WITH_BYTES(0x0908, 0x0910);

    volatile uint32_t TSIZ;   /* 0x0910 + (0x0020 * EP_idx)   */
    volatile uint32_t DMA;    /* 0x0914 + (0x0020 * EP_idx)   */
    volatile uint32_t TXFSTS; /* 0x0918 + (0x0020 * EP_idx)   */

    PAD_WITH_BYTES(0x0918, 0x0920);

} usbEPtRegs;

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
    usbEPtRegs DIEP[USB_OTG_FS_MAX_IN_ENDPOINTS];

    PAD_WITH_BYTES(0x097c, 0x0b00);

    /* Device OUT endpoints */
    usbEPtRegs DOEP[USB_OTG_FS_MAX_OUT_ENDPOINTS];

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

typedef struct
{
    usbEPtRegs *regs;      /* Ptr to the register structure for the ep        */
    uint8_t     parity;    /* 1 for odd, 0 for even                           */
    uint32_t    maxpacket; /* Endpoint Max Packet size (kB)                   */
    uint8_t     type;      /* type : eg CONTROL, ISOC, BULK, ETC..            */
    uint8_t     pidStart;  /* data PID start (can be 0 or 1)                  */
    struct
    {
        uint8_t *buf;     /* ptr to application xfer buffer                   */
        uint32_t xferLen; /* xfer len in BYTES                                */
        uint32_t xferCnt; /* xfer counts (case wherin multi pkt received)     */
        uint8_t  num;     /* FIFO index in the peripheral                     */
    } fifo;
} usbEndpointHandle;

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
        WAITING_FOR_USBRST,
        WAITING_FOR_ENUMDNE,
        ENUMERATION_SERVICED,
        ENUMERATION_COMPLETE,
    } enumState;

    usbEndpointHandle IN_ENDPTS[USB_OTG_FS_MAX_IN_ENDPOINTS];
    usbEndpointHandle OUT_ENDPTS[USB_OTG_FS_MAX_IN_ENDPOINTS];
    void (*delay)(uint32_t);
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

static uint8_t TEST_IN_EP_BUF0[250];
static uint8_t TEST_IN_EP_BUF1[250];
static uint8_t TEST_IN_EP_BUF2[250];
static uint8_t TEST_IN_EP_BUF3[250];

static uint8_t TEST_OUT_EP_BUF0[250];
static uint8_t TEST_OUT_EP_BUF1[250];
static uint8_t TEST_OUT_EP_BUF2[250];
static uint8_t TEST_OUT_EP_BUF3[250];

void usbDriver_setDelayFunc(void (*delayFunc)(uint32_t))
{
    if (NULL != delayFunc)
    {
        if (driverPtr != NULL)
        {
            driverPtr->delay = delayFunc;
        }
    }
}

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

    unsigned i;
    for (i = 0; i < USB_OTG_FS_MAX_DEVICE_ENDPTS; i++)
    {
        driver->IN_ENDPTS[i].regs  = &driver->regs->DIEP[i];
        driver->OUT_ENDPTS[i].regs = &driver->regs->DOEP[i];
    }

    driver->IN_ENDPTS[0].fifo.buf = TEST_IN_EP_BUF0;
    driver->IN_ENDPTS[1].fifo.buf = TEST_IN_EP_BUF1;
    driver->IN_ENDPTS[2].fifo.buf = TEST_IN_EP_BUF2;
    driver->IN_ENDPTS[3].fifo.buf = TEST_IN_EP_BUF3;

    driver->OUT_ENDPTS[0].fifo.buf = TEST_OUT_EP_BUF0;
    driver->OUT_ENDPTS[1].fifo.buf = TEST_OUT_EP_BUF1;
    driver->OUT_ENDPTS[2].fifo.buf = TEST_OUT_EP_BUF2;
    driver->OUT_ENDPTS[3].fifo.buf = TEST_OUT_EP_BUF3;

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
            errCode = 1;
            break;
        }

        switch (driver->enumState)
        {
            case WAITING_FOR_BUS_IDLE:
            {
                /* Wait until bus is idle */
                if (driver->regs->GRSTCTL & (GRSTCTL_AHBIDL))
                {
                    /* Initiate soft reset */
                    driver->regs->GRSTCTL |= (GRSTCTL_CSRST);
                    driver->enumState = STARTUP_FROM_SOFT_RESET;
                }
            }
            break;
            case STARTUP_FROM_SOFT_RESET:
            {
                /* Hardware has cleared CSRST indicating completed soft
                 * reset */
                if (0 == (driver->regs->GRSTCTL & (GRSTCTL_CSRST)))
                {
                    driver->enumState = CORE_INITIALIZATION;
                }
            }
            break;
            case CORE_INITIALIZATION:
            {
                /** @note SEE SECTION 22.17.1 IN RM0383 */

                /* STEP 1 */
                driver->regs->GAHBCFG |= ((GAHBCFG_GINT) | (GAHBCFG_TXFELVL));
                driver->regs->GINTSTS |= (GINTSTS_RXFLVL);

                /* STEP 2 */
                driver->regs->GUSBCFG =
                    ((GUSBCFG_HNPCAP) | (GUSBCFG_SRPCAP) |
                     (trdt_val << GUSBCFG_TRDT_POS) | (5 << GUSBCFG_TOCAL_POS));

                /* STEP 3 */
                driver->regs->GINTMSK |= ((GINTMSK_OTGINT) | (GINTMSK_MMISM));

                /**
                 * STEP 4  : FORCE DEVICE MODE.
                 * (step 4 in RM0383 is actually missing info, see note
                 * below
                 * @note SEC 22.5, BULLET PT 4 IN RM0383, PAGE 674
                 */

                if (!((driver->regs->GINTSTS & (GINTSTS_CMOD)) ==
                      (CMOD_DEVICE)))
                {
                    /*
                     * If the "B" plug event didn't correctly trigger core
                     * devCfg sequence, (likely due to USB_ID line not
                     * physically connected / used on PCB)
                     * then force device mode
                     */
                    driver->regs->GUSBCFG &=
                        ~((GUSBCFG_FDMOD) | (GUSBCFG_FHMOD));
                    driver->regs->GUSBCFG |= (GUSBCFG_FDMOD);

                    while (!((driver->regs->GINTSTS & GINTSTS_CMOD) ==
                             (CMOD_DEVICE)))
                    {
                        /* Wait for HW to complete transition */
                    }
                }

                /* UPDATE STATE MACHINE */
                driver->enumState = DEVICE_INITIALIZATION;
            }
            break;
            case DEVICE_INITIALIZATION:
            {
                uint32_t temp = 0;

                /** @note SEE SECTION 22.17.3 IN RM0383 */
                /* STEP 1 */
                driver->regs->DCFG |= ((DCFG_DSPD_FULLSPEED) | (DCFG_NZLSOHSK));
                /*
                 * note that DCFG::DSPD is to inform host of USB spec speed
                 * support. The bus will not not operate at full speed if
                 * HOST does not ALSO support to device's speed spec
                 */

                temp &= ~GCCFG_NOVBUSSENS;  /* Enable VBUS sensing */
                temp &= ~(GCCFG_VBUSASEN);  /* Disable type "A" VBUS sensing */
                temp |= (GCCFG_VBUSBSEN);   /* Enable type "B" VBUS sensing  */
                temp |= (GCCFG_PWRDWN);     /* Activate tranceiver           */
                driver->regs->GCCFG = temp; /* Load configuration register   */

                /* YOU GOTTA UPDATE THE STATE MACHINE BEFORE UNMASKING */
                driver->enumState = WAITING_FOR_USBRST;

                temp = 0;
                temp |= (GINTMSK_USBRST);   /* unmask host-initiated reset */
                temp |= (GINTMSK_USBSUSPM); /* unmask session suspend */
                temp |= (GINTMSK_ENUMDNEM); /* unmask enumeration complete */
                temp |= (GINTMSK_ESUSPM);   /* unmask early suspend        */
                temp |= (GINTMSK_SOFM);     /* unmask start of frame       */
                temp |= (GINTMSK_RXFLVLM);  /* unmask RX fifo non-empty    */
                driver->regs->GINTMSK |= temp;
            }
            break;
            case WAITING_FOR_USBRST:
            {
                /* DO NOTHING, IRQ WILL SERVICE */
            }
            break;
            case WAITING_FOR_ENUMDNE:
            {
            }
            break;
            case ENUMERATION_SERVICED:
            {
                /* hang here while we test some stuff */
                LL_ASSERT(0);
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

#endif /* !USE_HAL_DRIVER */

static uint32_t serviceEndpointInterrupt(uint32_t epNum, uint32_t isInEp)
{
    uint32_t retVal = 0;
    if (isInEp)
    {
    }
    else
    {
    }
    return retVal;
}

void OTG_FS_IRQHandler(void)
{
#if defined(USE_HAL_DRIVER)
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
#else
    LL_ASSERT(NULL != driverPtr);
    if (((driverPtr->regs->GINTSTS & (GINTSTS_CMOD)) == (CMOD_DEVICE)))
    {
        if (driverPtr->regs->GINTSTS &
            (GINTSTS_MMIS)) /* Mode mismanagement interrupt */
        {
            /*
             * The core sets this bit when the application is trying
             * to access) – A host mode register, when the core is
             * operating in device mode – A device mode register,
             * when the core is operating in host mode The register
             * access is completed on the AHB with an OKAY response,
             * but is ignored by the core internally and does not
             * affect the operation of the core.
             */

            /* Acknowledge interrupt but do nothing */
            driverPtr->regs->GINTSTS &= ~(GINTSTS_MMIS);
        }

        if (driverPtr->regs->GINTSTS &
            (GINTSTS_OTGINT)) /* OTG protocol event */
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

        if (driverPtr->regs->GINTSTS & (GINTSTS_USBRST))
        {
            /* See sectuib 22.17.5 in RM0383 */

            /* STEP 1 */
            unsigned i;
            for (i = 0; i < USB_OTG_FS_MAX_DEVICE_ENDPTS; i++)
            {
                /* Clear EP ISR flags before stall */
                driverPtr->regs->DIEP[i].INT = 0xFB7FU;
                driverPtr->regs->DOEP[i].INT = 0xFB7FU;

                /* Unstall any stalled endpoints */
                driverPtr->regs->DIEP[i].CTL &= ~(DIEPCTL_STALL);
                driverPtr->regs->DOEP[i].CTL &= ~(DOEPCTL_STALL);

                /* Send endpoint (IN AND OUT) NAK bits */
                driverPtr->regs->DOEP[i].CTL |= (DOEPCTL_SNAK);
                driverPtr->regs->DIEP[i].CTL |= (DIEPCTL_SNAK);
            }

            /* STEP 2 */
            driverPtr->regs->DAINTMSK =
                ((DAINTMSK_OEPM_EP0) | (DAINTMSK_IEPM_EP0));

            driverPtr->regs->DOEPMSK |=
                ((DOEPMSK_STUPM) | (DOEPMSK_XFRCM) | (DOEPMSK_EPDM) |
                 (DOEPMSK_OTEPSPRM) | (DOEPMSK_NAKM));
            driverPtr->regs->DIEPMSK |=
                ((DIEPMSK_TOCM) | (DIEPMSK_XFRCM) | (DIEPMSK_EPDM));

            /* STEP 3 */
            /* SET UP THE DATA FIFO RAM FOR EACH OF THE FIFOS */

            while (!(driverPtr->regs->GRSTCTL & (GRSTCTL_AHBIDL)))
            {
                /* Wait for master bus to finish activity */
            }

            /* Flush transmit fifos */
            driverPtr->regs->GRSTCTL =
                ((GRSTCTL_TXFFLSH) | (GRSTCTL_TXFNUM_ALL));

            /*
             * Absolute minimum fifo depth is sufficient bytes for
             * 1 standard packet
             *          +
             * 1 control packet
             *          +
             * 1 setup packet
             */
            uint32_t tmp = USB_FS_PKT_SZMAX;

            /** @todo FIX MAGIC NUMBERS ONCE CODE IS WORKING */
            tmp += 2; /* 2 words for status of control packet */

            /* room for setup packets */
            /* 10 words. See pg 785, step 2, RM0383 */
            tmp += 10 * sizeof(uint32_t);

            tmp *= 2; /* Factor of 2 for headroom */

            /* set fifo depth register */
            driverPtr->regs->GRXFSIZ = (tmp << (GRXFSIZ_RXFD_POS));

            /* program TXF0 fifo size register */
            driverPtr->regs->DIEPTXF0_HNPTXFSIZ = USB_FS_PKT_SZMAX;

            /*
             * STEP 4 ) program OUT endpoint to receive 3 back to back
             * setup packets
             */

            /** @todo FIX MAGIC NUMBERS */
            driverPtr->regs->DOEP[0].TSIZ = (3 << (DOEPTSIZ_STUPCNT_POS)) |
                                            (1 << DOEPTSIZ_PKTCNT_POS) |
                                            (30 << DOEPTSIZ_XFRSIZ_POS);

            driverPtr->regs->GINTSTS &= (GINTSTS_USBRST);

            if (driverPtr->enumState == WAITING_FOR_USBRST)
            {
                /*
                 * Reset command has been serviced,
                 * now we wait for host to indicate enumeration complete
                 */
                driverPtr->enumState = WAITING_FOR_ENUMDNE;
            }
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_ENUMDNE))
        {
            /* See section 22.17.5 in RM0383 */

#if defined(STM32F411VE)
            /* On eval board turn on orange LED to indicate enum success */
            gpio_enablePinClock(MCUPIN_PD14);
            gpio_setPinMode(MCUPIN_PD14, GPIO_MODE_output);
            gpio_setPinPull(MCUPIN_PD14, GPIO_PIN_PULL_MODE_none);
            gpio_setPinSpeed(MCUPIN_PD14, GPIO_SPEED_max);
            gpio_setPinSupplyMode(MCUPIN_PD14, GPIO_PIN_SUPPLY_MODE_push_pull);
            gpio_setDigitalPinState(MCUPIN_PD14, GPIO_PIN_STATE_high);
#endif /* STM32F411VE */

            /* Get enumerated speed bits from DSTS */
            if ((driverPtr->regs->DSTS & (DSTS_ENUMSPD)) == (DSTS_ENUMSPD_FS))
            {
                driverPtr->regs->DIEP[0].CTL &= ~(DIEPCTL_MPSIZ);
                driverPtr->regs->DIEP[0].CTL |=
                    ((DIEPCTL_MPSIZ_64bytes) << (DIEPCTL_MPSIZ_POS));
            }
            else
            {
                LL_ASSERT(0); /* 48MHZ is only speed valid on this mcu */
            }

            /* Set the MPS of the IN EP0 to 64 bytes */
            driverPtr->regs->DIEP[0].CTL &= ~(DIEPCTL_MPSIZ);
            driverPtr->regs->DIEP[0].CTL |= (DIEPCTL_MPSIZ_64bytes);

            /**
             * [CARL, APRIL 12, 2020]
             * @note RM0383 (REV3), PAGE 738
             * SEEMS TO INDICATE THAT HARDWARE KEEPS DIEPCTL::EPENA
             * ALWAYS SET AT PART OF ENUMERATION SEQUENCE BUT THE
             * FACT THAT IT HAS AHB WRITE ACCESS BY APPLICATION
             * SEEMS TO INDICATE OTHERWISE.
             *
             * ALSO, HW DEBUG FOR cortex m4 (ISA v7) via SWD probe
             * indicates that DIEPCTL::EPENA DOES #### NOT ####
             * GET SET AS PART OF HOST ACKNOWLEDGEMENT DURING
             * USB DEVICE SESSION ENUMERATION SEQUENCE (ISR SERVICE)
             *
             * FOR NOW, I'm manually setting the bit
             */
            driverPtr->regs->DIEP[0].CTL |= (DIEPCTL_EPENA);

            /*
             * Prompt clear of global control
             * endpoint IN host-pkt unack bit
             * (hw will clear)
             */
            driverPtr->regs->DCTL |= (DCTL_CGINAK);

            /** @todo Consider hanging (block w/ timeout)
             *  until RXFLVL gets serviced
             */

            /* Update application state machine */
            if (driverPtr->enumState == WAITING_FOR_ENUMDNE)
            {
                driverPtr->enumState = ENUMERATION_SERVICED;
            }

            driverPtr->regs->GINTSTS &= (GINTSTS_ENUMDNE);
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_SOF)) /* Start of frame */
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

        if (driverPtr->regs->GINTSTS & (GINTSTS_RXFLVL))
        {
            /* Mask Interrupt until packet moves from FIFO to Application */
            driverPtr->regs->GINTMSK &= ~(GINTMSK_RXFLVLM);

            /* Get current status */
            uint32_t GRXSTSP = driverPtr->regs->GRXSTSR;
            uint32_t BCNT    = (GRXSTSP & (GRXSTSP_BCNT)) >> (GRXSTSP_BCNT_POS);
            uint32_t EPNUM = (GRXSTSP & (GRXSTSP_EPNUM)) >> (GRXSTSP_EPNUM_POS);
            uint32_t PKTSTS = GRXSTSP & (GRXSTSP_PKTSTS);

            volatile uint32_t *pktSrc =
                (volatile uint32_t *)driverPtr->regs->DFIFO[EPNUM].buf;

            uint32_t *pktDst;
            switch (PKTSTS)
            {
                case GRXSTSP_PKTSTS_DEVMODE_OUT_PKT:
                {
                    /* Destination is EP receive buffer */
                    pktDst =
                        (uint32_t *)(driverPtr->OUT_ENDPTS[EPNUM].fifo.buf +
                                     driverPtr->OUT_ENDPTS[EPNUM].fifo.xferCnt);
                }
                break;
                case GRXSTSP_PKTSTS_DEVMODE_STUP_PKT:
                {
                    /* Destination is setup packets */
                    pktDst =
                        (uint32_t *)(driverPtr->setupPackets +
                                     driverPtr->OUT_ENDPTS[EPNUM].fifo.xferCnt);
                }
                break;
                case GRXSTSP_PKTSTS_DEVMODE_STUP_CPLT:
                {
                    pktDst =
                        (uint32_t *)(driverPtr->setupPackets +
                                     driverPtr->OUT_ENDPTS[EPNUM].fifo.xferCnt);

                    /* clear transfer count */
                    driverPtr->OUT_ENDPTS[EPNUM].fifo.xferCnt = 0;
                }
                break;
                case GRXSTSP_PKTSTS_DEVMODE_OUT_CPLT:
                {
                    driverPtr->OUT_ENDPTS[EPNUM].fifo.xferCnt = 0;
                }
                break;
                case GRXSTSP_PKTSTS_DEVMODE_GONAK:
                {
                }
                break;
            }

            /* POP received data from peripheral FIFO stack */
            if (BCNT)
            {
                uint32_t wordCnt = (BCNT + 3) / sizeof(uint32_t);
                if (NULL != driverPtr->OUT_ENDPTS[EPNUM].fifo.buf)
                {
                    uint32_t b;
                    if (NULL != pktDst)
                    {
                        for (b = 0; b < wordCnt; b++)
                        {
                            __UNALIGNED_UINT32_WRITE(pktDst, *pktSrc);
                            pktDst++;
                        }
                    }
                    else
                    {
                        LL_ASSERT(0);
                    }
                }
            }

            /* Update transfer count for endpoint */
            driverPtr->OUT_ENDPTS[EPNUM].fifo.xferCnt += BCNT;

            /* Unmask RXLVL interrupt */
            driverPtr->regs->GINTMSK |= (GINTMSK_RXFLVLM);
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_NPTXFE))
        {
            /* Non-periodic fifo non-empty (device wants to xmit) */
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_GINAKEFF))
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
             * NOTE ) The STALL bit takes precedence over the NAK
             * bit.
             */

            /* Clear GINSTS )) GINAKEFF by clearing DTCL))GGINAK */
            driverPtr->regs->DCTL &= ~(DCTL_CGINAK);
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_GOUTNAKEFF))
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

            /* Clear GINSTS )) GONAKEFF by setting DTCL))GGONAK */
            driverPtr->regs->DCTL |= (DCTL_CGONAK);
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_ESUSP))
        {
            /* Early suspend (no activity on D+ for ~3ms) */
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_USBSUSP))
        {
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_ISOODRP))
        {
            /* dropped isoc OUT packet */
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_EOPF))
        {
            /* End of periodic frame */
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_IEPINT))
        {
            /* an IN endpt caused an interrupt */
            const uint32_t daint = driverPtr->regs->DAINT;
            uint32_t       epnum = DAINT_IEPINT_EP0;
            uint32_t       epPos;
            /* FIND WHICH ENDPOINT CAUSED THE INTERRUPT */
            for (epPos = 0; epPos < USB_OTG_FS_MAX_DEVICE_ENDPTS; epPos++)
            {
                uint32_t epMsk          = epnum << epPos;
                uint32_t epNeedsService = daint & epMsk;
                if (epNeedsService)
                {
                    serviceEndpointInterrupt(epPos, 1);
                }
            }
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_OEPINT))
        {
            /* an OUT endpt caused an interrupt */
            uint32_t daint = driverPtr->regs->DAINT;
            uint32_t epnum = DAINT_OEPINT_EP0;
            uint32_t epPos;
            /* FIND WHICH ENDPOINT CAUSED THE INTERRUPT */
            for (epPos = 0; epPos < USB_OTG_FS_MAX_DEVICE_ENDPTS; epPos++)
            {
                uint32_t epMsk          = epnum << epPos;
                uint32_t epNeedsService = daint & epMsk;
                if (epNeedsService)
                {
                    serviceEndpointInterrupt(epPos, 0);
                }
            }
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_IISOIXFR))
        {
            /* Incomple isoc xfer IN */
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_PXFR_INCOMPISOOUT))
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

        if (driverPtr->regs->GINTSTS & (GINTSTS_CIDSCHG))
        {
            /* Connector ID status change */
        }

        if (driverPtr->regs->GINTSTS & (GINTSTS_SRQINT))
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

        if (driverPtr->regs->GINTSTS &
            (GINTSTS_WKUINT)) /* Resume/remote wakeup detcted */
        {
            /*
             * In device mode, this interrupt is asserted
             * when a resume is detected on the USB.
             * In host mode, this interrupt is asserted when a
             * remote wakeup is detected on the USB.
             */
        }
    }
    else /* HOST MODE */
    {
    }
#endif /* USE_HAL_DRIVER */
}
