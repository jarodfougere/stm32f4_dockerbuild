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

#include "ATTRIBUTE_PORTABILITY_HEADER.h"

#include <stdint.h>
#include <stdlib.h>

#include "rimot_usb_register_masks.h"
#include "rimot_bus_region_offsets.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#include "rimot_interrupts.h"
#include "rimot_rcc.h"

#include "cmsis_compiler.h"

typedef struct
{
    volatile uint32_t GOTGCTL;            /*USB_OTG Control and Status Register          000h */
    volatile uint32_t GOTGINT;            /*USB_OTG Interrupt Register                   004h */
    volatile uint32_t GAHBCFG;            /*Core AHB Configuration Register              008h */
    volatile uint32_t GUSBCFG;            /*Core USB Configuration Register              00Ch */
    volatile uint32_t GRSTCTL;            /*Core Reset Register                          010h */
    volatile uint32_t GINTSTS;            /*Core Interrupt Register                      014h */
    volatile uint32_t GINTMSK;            /*Core Interrupt Mask Register                 018h */
    volatile uint32_t GRXSTSR;            /*Receive Sts Q Read Register                  01Ch */
    volatile uint32_t GRXSTSP;            /*Receive Sts Q Read & POP Register            020h */
    volatile uint32_t GRXFSIZ;            /*Receive FIFO Size Register                   024h */
    volatile uint32_t DIEPTXF0_HNPTXFSIZ; /*EP0 / Non Periodic Tx FIFO Size Register     028h */
    volatile uint32_t HNPTXSTS;           /*Non Periodic Tx FIFO/Queue Sts reg           02Ch */
    uint32_t Reserved30[2];               /*Reserved                                     030h */
    volatile uint32_t GCCFG;              /*General Purpose IO Register                  038h */
    volatile uint32_t CID;                /*User ID Register                             03Ch */
    uint32_t Reserved40[48];              /*Reserved                                0x40-0xFF */
    volatile uint32_t HPTXFSIZ;           /*Host Periodic Tx FIFO Size Reg               100h */
    volatile uint32_t DIEPTXF[0x0F];      /*dev Periodic Transmit FIFO                        */
} USB_OTG_GlobalTypeDef;

typedef struct
{
    volatile uint32_t DCFG;       /*dev Configuration Register   800h */
    volatile uint32_t DCTL;       /*dev Control Register         804h */
    volatile uint32_t DSTS;       /*dev Status Register (RO)     808h */
    uint32_t Reserved0C;          /*Reserved                     80Ch */
    volatile uint32_t DIEPMSK;    /*dev IN Endpoint Mask         810h */
    volatile uint32_t DOEPMSK;    /*dev OUT Endpoint Mask        814h */
    volatile uint32_t DAINT;      /*dev All Endpoints Itr Reg    818h */
    volatile uint32_t DAINTMSK;   /*dev All Endpoints Itr Mask   81Ch */
    uint32_t Reserved20;          /*Reserved                     820h */
    uint32_t Reserved9;           /*Reserved                     824h */
    volatile uint32_t DVBUSDIS;   /*dev VBUS discharge Register  828h */
    volatile uint32_t DVBUSPULSE; /*dev VBUS Pulse Register      82Ch */
    volatile uint32_t DTHRCTL;    /*dev threshold                830h */
    volatile uint32_t DIEPEMPMSK; /*dev empty msk                834h */
    volatile uint32_t DEACHINT;   /*dedicated EP interrupt       838h */
    volatile uint32_t DEACHMSK;   /*dedicated EP msk             83Ch */
    uint32_t Reserved40;          /*dedicated EP mask            840h */
    volatile uint32_t DINEP1MSK;  /*dedicated EP mask            844h */
    uint32_t Reserved44[15];      /*Reserved                 844-87Ch */
    volatile uint32_t DOUTEP1MSK; /*dedicated EP msk             884h */
} USB_OTG_DeviceTypeDef;

typedef struct
{
    volatile uint32_t HCFG;     /*Host Configuration Register          400h */
    volatile uint32_t HFIR;     /*Host Frame Interval Register         404h */
    volatile uint32_t HFNUM;    /*Host Frame Nbr/Frame Remaining       408h */
    uint32_t Reserved40C;       /*Reserved                             40Ch */
    volatile uint32_t HPTXSTS;  /*Host Periodic Tx FIFO/ Queue Status  410h */
    volatile uint32_t HAINT;    /*Host All Channels Interrupt Register 414h */
    volatile uint32_t HAINTMSK; /*Host All Channels Interrupt Mask     418h */
} USB_OTG_HostTypeDef;

typedef union
{
    struct
    {
        volatile uint32_t CHAR;   /*Host Channel Characteristics Register    500h */
        volatile uint32_t SPLT;   /*Host Channel Split Control Register      504h */
        volatile uint32_t INT;    /*Host Channel Interrupt Register          508h */
        volatile uint32_t INTMSK; /*Host Channel Interrupt Mask Register     50Ch */
        volatile uint32_t TSIZ;   /*Host Channel Transfer Size Register      510h */
        volatile uint32_t DMA;    /*Host Channel DMA Address Register        514h */
        uint32_t Reserved[2];
    } HC;

    struct
    {
        volatile uint32_t CTL;  /*dev OUT Endpoint Control Reg           B00h + (ep_num * 20h) + 00h */
        uint32_t Reserved04;    /*Reserved                               B00h + (ep_num * 20h) + 04h */
        volatile uint32_t INT;  /*dev OUT Endpoint Itr Reg               B00h + (ep_num * 20h) + 08h */
        uint32_t Reserved0C;    /*Reserved                               B00h + (ep_num * 20h) + 0Ch */
        volatile uint32_t TSIZ; /*dev OUT Endpoint Txfer Size            B00h + (ep_num * 20h) + 10h */
        volatile uint32_t DMA;  /*dev OUT Endpoint DMA Address           B00h + (ep_num * 20h) + 14h */
        uint32_t Reserved18[2]; /*Reserved B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
    } OUTEP;

    struct
    {
        volatile uint32_t CTL;    /*dev IN Endpoint Control Reg    900h + (ep_num * 20h) + 00h */
        uint32_t Reserved04;      /*Reserved                       900h + (ep_num * 20h) + 04h */
        volatile uint32_t INT;    /*dev IN Endpoint Itr Reg        900h + (ep_num * 20h) + 08h */
        uint32_t Reserved0C;      /*Reserved                       900h + (ep_num * 20h) + 0Ch */
        volatile uint32_t TSIZ;   /*IN Endpoint Txfer Size         900h + (ep_num * 20h) + 10h */
        volatile uint32_t DMA;    /*IN Endpoint DMA Address Reg    900h + (ep_num * 20h) + 14h */
        volatile uint32_t TXFSTS; /*IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h */
        uint32_t Reserved18;      /*Reserved  900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch */
    } INEP;
} HC_EP_overlay;

#define USB_OTG_FS_PERIPH_BASE 0x50000000UL
#define USB_OTG_GLOBAL_BASE 0x000UL
#define USB_OTG_DEVICE_BASE 0x800UL
#define USB_OTG_IN_ENDPOINT_BASE 0x900UL
#define USB_OTG_OUT_ENDPOINT_BASE 0xB00UL
#define USB_OTG_EP_REG_SIZE 0x20UL
#define USB_OTG_HOST_BASE 0x400UL
#define USB_OTG_HOST_PORT_BASE 0x440UL
#define USB_OTG_HOST_CHANNEL_BASE 0x500UL
#define USB_OTG_HOST_CHANNEL_SIZE 0x20UL
#define USB_OTG_PCGCCTL_BASE 0xE00UL
#define USB_OTG_FIFO_BASE 0x1000UL
#define USB_OTG_FIFO_SIZE 0x1000UL
#define USB_OTG_FS_HOST_MAX_CHANNEL_NBR 8U
#define USB_OTG_FS_MAX_IN_ENDPOINTS 4U   /* Including EP0 */
#define USB_OTG_FS_MAX_OUT_ENDPOINTS 4U  /* Including EP0 */
#define USB_OTG_FS_TOTAL_FIFO_SIZE 1280U /* in Bytes */
#define USB_OTG_FS ((USB_OTG_GlobalTypeDef *)USB_OTG_FS_PERIPH_BASE)

static struct
{
    USB_OTG_GlobalTypeDef *global;
    USB_OTG_DeviceTypeDef *device;
    USB_OTG_HostTypeDef *host;
    struct
    {
        volatile uint32_t PCGCCTL;
    } * powerClockCtl;
    HC_EP_overlay endpoints[15];
} usbRegs;

static void (*DelayFunc)(uint32_t);

void usbInjectDelayFunc(void (*delayFunc)(uint32_t))
{
    LL_ASSERT(NULL != delayFunc);
    DelayFunc = delayFunc;
}

void USBD_Delay(uint32_t ms)
{
    if (DelayFunc != NULL)
    {
        DelayFunc(ms);
    }
}

/**
 * @brief This function handles wakeup of the USB Peripheral in OTG mode
 * 
 */
void OTG_FS_WKUP_IRQHandler(void)
{
}

void OTG_FS_IRQHandler(void)
{
}
